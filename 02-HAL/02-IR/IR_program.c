/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 28 ‎September 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/

#include "Std_types.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "SysTick_interface.h"
#include "EXTI_interface.h"

#include "IR_interface.h"
#include "IR_Private.h"
#include "IR_config.h"

typedef enum 
{
	IR_IDLE               = 0 ,
	IR_RECEIVING   		  = 1 ,
	IR_RECEIVING_COMPLETE = 2 ,
	IR_CHECK_FRAME 		  = 3 ,
	IR_ERROR        	  = 4 ,
	IR_FINISHED     	  = 5
	
}IR_Status_e;

typedef struct 
{
	IR_Config   *config   ;
	IR_Status_e IR_Status ;
	
}IR_Control_s;


static IR_Control_s IR_Control ; 
static volatile uint8_t  IR_StartFlag = FALSE ;
static volatile uint8_t  IR_InitFlag = FALSE ;
static volatile uint8_t  BufferCounter = 0 ;
static volatile uint8_t  Data = 0 ;
static volatile uint16_t IR_DataBuffer[IR_BUFFER_SIZE] ;
/*global temp variable to store the received address to be compared with device address*/
static volatile uint8_t  IR_AddressCheck = 0 ;

ErrorStatus IR_init(IR_Config *Config)
{
	/*Temp varibale to store function status*/
	ErrorStatus FunctionStatus = E_OK ;
	/*check for null pointer*/
	if(Config == NULL)
	{
		FunctionStatus = IR_ERROR_ID + NULL_PTR ;
	}
	/*check for multiple initialization*/
	else if(IR_InitFlag == TRUE)
	{
		FunctionStatus = IR_ERROR_ID + MULTIPLE_INITIALIZATION ;
	}
	else
	{
		/*copy user configurations to IR_COntrol structure*/
		IR_Control.config = Config ;
		/*initialze IR receiver output pin as input floating for interrupt*/
		GPIO_InitPin(IR_Control.config->GPIOx ,IR_Control.config->IR_ReceiverOutputPin,GPIO_INPUT_FLOATING);
		/*Set exti call back function*/
		switch(IR_Control.config->IR_ReceiverOutputPin)
		{
			case GPIO_PIN_0 : EXTI0_SetCallBack(IR_CallBack);  break;
			case GPIO_PIN_1 : EXTI1_SetCallBack(IR_CallBack);  break;
			case GPIO_PIN_2 : EXTI2_SetCallBack(IR_CallBack);  break;
			case GPIO_PIN_3 : EXTI3_SetCallBack(IR_CallBack);  break;
			case GPIO_PIN_4 : EXTI4_SetCallBack(IR_CallBack);  break;
			case GPIO_PIN_5 : EXTI5_SetCallBack(IR_CallBack);  break;
			case GPIO_PIN_6 : EXTI6_SetCallBack(IR_CallBack);  break;
			case GPIO_PIN_7 : EXTI7_SetCallBack(IR_CallBack);  break;
			case GPIO_PIN_8 : EXTI8_SetCallBack(IR_CallBack);  break;
			case GPIO_PIN_9 : EXTI9_SetCallBack(IR_CallBack);  break;
			case GPIO_PIN_10: EXTI10_SetCallBack(IR_CallBack); break;
			case GPIO_PIN_11: EXTI11_SetCallBack(IR_CallBack); break;
			case GPIO_PIN_12: EXTI12_SetCallBack(IR_CallBack); break;
			case GPIO_PIN_13: EXTI13_SetCallBack(IR_CallBack); break;
			case GPIO_PIN_14: EXTI14_SetCallBack(IR_CallBack); break;
			case GPIO_PIN_15: EXTI15_SetCallBack(IR_CallBack); break;
			default: break ;		
		}
		/*IR initialization is done*/
		IR_InitFlag = TRUE ;
	}
	
	return FunctionStatus ; 
	
}

void IR_Dispatcher(void)
{
    if(IR_InitFlag == FALSE)
	{
		/*Do nothing when IR is not initilized*/
	}
	else
	{
		/*switch on IR state*/
		switch(IR_Control.IR_Status)
		{
			case IR_IDLE:
			
			/*Do Nothing*/
			
			break ;
			case IR_RECEIVING:
				if(BufferCounter >= IR_FRAME_SIZE)
				{
					/*complete the receiving when receiving a full IR frame*/
					IR_Control.IR_Status = IR_RECEIVING_COMPLETE ;
				}
				else
				{
					
				}
			break ;
			case IR_RECEIVING_COMPLETE:
					/*reset buffercounter to put the next IR frame*/
					BufferCounter = 0 ;
					IR_Control.IR_Status = IR_CHECK_FRAME ;
					
			break;
			case IR_CHECK_FRAME:
			    /*Check first for the start bit*/
				if((IR_DataBuffer[0] >= 10000) && (IR_DataBuffer[0] <= 14000))
				{
					/*then get the device address which is after the start bit and the start from index one*/
					for(uint8_t local_index = 1 ; local_index < IR_ADDRESS_BITS + 1 ;  local_index++)
					{
						/*check for 1*/
						if((IR_DataBuffer[local_index] >= 2000) && (IR_DataBuffer[local_index] <= 2300))
						{
							SET_BIT(IR_AddressCheck , local_index );
						}
						else
						{
							/*check for 0*/
							CLR_BIT(IR_AddressCheck , local_index );
						}
					}
					/*check for the Device adderss and if its compatible with your device*/
					if(IR_AddressCheck == IR_ADDRESS)
					{
						IR_Control.IR_Status = IR_FINISHED ;
					}
					else
					{
						IR_Control.IR_Status = IR_ERROR ;
					}
				}
				else
				{
					/*in case of not receiving a start bit consider it as an frame error*/
					IR_Control.IR_Status = IR_ERROR ;
				}
			break ;
			case IR_FINISHED:
				/*get the data from IR frame bit by bit and store it in a global variable*/
				for(uint8_t local_index1 = 0 ; local_index1 < IR_DATA_BITS ; local_index1++)
				{
					/*the data in the ir frame start from the 17th index */
					/*check if the buffer index means 1*/
					if((IR_DataBuffer[17+local_index1] >= 2000) && (IR_DataBuffer[17+local_index1] <= 2300))
					{
						/*set the corresponding bit in the global data variable*/
						SET_BIT(Data , local_index1 );
					}
					else
					{
						/*if the buffer index means 0 then clear the corresponding bit in the global data variable*/
						CLR_BIT(Data , local_index1 );
					}
				}
			
				/*store the global data variable in the user data variable*/
				*(IR_Control.config->Data) = Data ;
				/*call the user callback funciton and send the status to the user(IR_FINISHED)*/
				IR_Control.config->IR_CBF((uint8_t)IR_Control.IR_Status);
				/*Confirm that the buffer counter is reseted*/
				BufferCounter    = 0     ;
				/*reset the IR start bit flag*/
				IR_StartFlag     = FALSE ;
				/*reset the data buffer to sore another IR frame*/
				IR_ResetDataBuffer();
				/*go to idle state*/
				IR_Control.IR_Status = IR_IDLE ;
			break;			
			case IR_ERROR:
			/*call the user callback funciton to Notify the user that there is an error*/
			IR_Control.config->IR_CBF((uint8_t)IR_Control.IR_Status);
			/*Confirm that the buffer counter is reseted*/
			BufferCounter    = 0     ;
			/*reset the IR start bit flag*/
			IR_StartFlag     = FALSE ;
			/*reset the data buffer to sore another IR frame*/
			IR_ResetDataBuffer();
			/*go to idle state*/
			IR_Control.IR_Status = IR_IDLE ;
			break;
		}
		
	}
	
	
}

void IR_CallBack(void)
{
   if(IR_Control.IR_Status == IR_IDLE )
   {
	   /*start receiving the IR frame*/
	   IR_Control.IR_Status = IR_RECEIVING ;
   }
   else
   {
	   
   }
   if(IR_StartFlag == FALSE)
   {
	   /*set systick call back that runs after the specifed time elapsed*/
	   SysTick_SetCallBack(IR_SysTickCallBack);
	   /*First receive the start bit then start the timer*/
	   SysTick_Start(MAX_TIME_FOR_RECEIVING_FRAME);
	   /*make the start bit flag as true to notify receiving the start bit*/
       IR_StartFlag = TRUE ;
   }
   else
   {   
	   /*store the time ticks that each bit took in the IR data buffer*/
	   IR_DataBuffer[BufferCounter] = (uint16_t)SysTick_GetElapsedTime() ;
	   /*start timer to count from zero again to check the time ticks for the next bit*/
	   SysTick_Start(MAX_TIME_FOR_RECEIVING_FRAME);
	   /*incerment the buffer counter*/
	   BufferCounter++;
   
   }
		      
  
}

/*after the max time for receiving the IR frame elapsed
reset every thing and go to the idle state*/
void IR_SysTickCallBack(void)
{
	BufferCounter    = 0     ;
	IR_StartFlag     = FALSE ;
	IR_ResetDataBuffer();
	IR_Control.IR_Status = IR_IDLE ;
}

/*private funciton to reset the IR frame Date Buffer*/
void IR_ResetDataBuffer(void)
{
	for(uint16_t local_index1 = 0 ; local_index1 < IR_BUFFER_SIZE ; local_index1++)
	{
		IR_DataBuffer[local_index1] = 0     ;
	}
}
