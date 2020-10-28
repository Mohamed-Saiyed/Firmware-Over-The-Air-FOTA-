/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 11 October 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/
#include "Std_types.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "SysTick_interface.h"

#include "STP_interface.h"
#include "STP_private.h"
#include "STP_config.h"

static uint8_t STP_InitFlag = FALSE ;

ErrorStatus STP_Init(void)
{
	ErrorStatus Status = E_OK ;
	
	if(STP_InitFlag == TRUE)
	{
		Status = MULTIPLE_INITIALIZATION ;
	}
	else
	{
		GPIO_InitPin(STP_SERIAL_DATA_PIN , GPIO_OUTPUT_PP_SPEED_2MHz);
		GPIO_InitPin(STP_SHIFT_COLCK_PIN , GPIO_OUTPUT_PP_SPEED_2MHz);
		GPIO_InitPin(STP_STORE_COLCK_PIN , GPIO_OUTPUT_PP_SPEED_2MHz);
		
		STP_InitFlag = TRUE ;
	}
	
	return Status ;
}

void STP_SendSynchronous(uint8_t Data)
{
	if(STP_InitFlag == FALSE)
	{
		/**/
	}
	else
	{
		int8_t  Local_Counter = 7 * NUM_OF_ICs ;
		uint8_t Local_Data_Bit	;
		for(; Local_Counter >= 0 ; Local_Counter--)
		{
			Local_Data_Bit = GET_BIT(Data , Local_Counter);
			
			GPIO_WritePin(STP_SERIAL_DATA_PIN , Local_Data_Bit);
			
			GPIO_WritePin(STP_SHIFT_COLCK_PIN , GPIO_PIN_HIGH);
			SysTick_SetBusyWait(1);
			GPIO_WritePin(STP_SHIFT_COLCK_PIN , GPIO_PIN_LOW);
			SysTick_SetBusyWait(1);
			
		}
		
		GPIO_WritePin(STP_STORE_COLCK_PIN , GPIO_PIN_HIGH);
		SysTick_SetBusyWait(1);
		GPIO_WritePin(STP_STORE_COLCK_PIN , GPIO_PIN_LOW);
		SysTick_SetBusyWait(1);
			
	}
}

