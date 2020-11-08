/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 4 November 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/

#include "Std_types.h"
#include "BIT_MATH.h"


#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "AFIO_interface.h"


#include "I2C_interface.h"
#include "I2C_private.h"
#include "I2C_config.h"


static void SetI2cClock(I2c_ConfigType *Config);
static void SetI2cPins(I2c_ConfigType *Config);
static void _I2C_Clear_Addr_Flag(I2C_Typedef *I2Cx);
static uint8_t I2C_InitFlag[2] = {FALSE} ;

ErrorStatus I2C_Init(I2c_ConfigType *Config)
{
	/*Local temp variable to store function status*/
	ErrorStatus State = E_OK;
	/*Check for init Flag*/
	if(I2C_InitFlag[Config->ID] == TRUE)
	{
		State = MULTIPLE_INITIALIZATION ;
	}
	/*Check For Null Pointers*/
	else if((Config == NULL) || (Config->I2Cx == NULL )) 
	{
		State = NULL_PTR ;
	}
	else
	{
		/*First Make sure that I2C peripheral is disabled beofor initialization*/
		CLR_BIT(Config->I2Cx->CR1 , 0);
		/*set the NoClockStertching mode*/
		switch(Config->ClockStretching)
		{
			case ENABLE : CLR_BIT(Config->I2Cx->CR1 , 7); break;
			case DISABLE: SET_BIT(Config->I2Cx->CR1 , 7); break;
			default:      CLR_BIT(Config->I2Cx->CR1 , 7); break;
		}
		
		/*Set perrpheirla frquency*/
		Config->I2Cx->CR2 |= (Config->I2C_PeripheralFreq << 0) ;
		
		/*Set I2c Slave Addressing Mode*/
		switch(Config->AddressingMode)
		{
			case I2C_ADDRESS_MODE_7BIT : CLR_BIT(Config->I2Cx->OAR1 , 15); break;
			case I2C_ADDRESS_MODE_10BIT: SET_BIT(Config->I2Cx->OAR1 , 15); break;
			default:     				 CLR_BIT(Config->I2Cx->OAR1 , 15); break;
		}
		
		/*Set I2C Mode (Standerd mode or Fast Mode)*/
		switch(Config->Mode)
		{
			case I2C_MODE_STANDARD : CLR_BIT(Config->I2Cx->CCR , 15); break;
			case I2C_MODE_FAST     : SET_BIT(Config->I2Cx->CCR , 15); break;
			default:     	         CLR_BIT(Config->I2Cx->CCR , 15); break;
		}
		
		/*if the choosen mode is fast mode then set the duty cycle*/
		if(Config->Mode == I2C_MODE_FAST)
		{
			switch((uint8_t)Config->DutyCycle)
			{
				case I2C_DUTYCYCLE_2   : CLR_BIT(Config->I2Cx->CCR , 14); break;
				case I2C_DUTYCYCLE_16_9: SET_BIT(Config->I2Cx->CCR , 14); break;
				default:     	         CLR_BIT(Config->I2Cx->CCR , 14); break;
			}
		}
		else
		{
			/*Do Nothing*/
		}
		Config->I2Cx->TRISE = 0x00000009;
		/*Set I2c Clock Speed*/
		SetI2cClock(Config);
		
		/*initialize I2C SDA & SCL Pins*/
		SetI2cPins(Config);
		
		/*Set the I2c init flag*/
		I2C_InitFlag[Config->ID] = TRUE	;
	}
	
	return State ;
	
}

void I2C_MemWrite(I2c_ConfigType *Config , uint8_t SlaveAddress , uint16_t MemAddress ,  uint8_t *Data , uint32_t Size)
{
	/*Check if the the I2C is not initialized*/
	if(I2C_InitFlag[Config->ID] == FALSE)
	{
		/*Do Nothing*/
	}
	else
	{
		uint8_t Temp =  0 ;
		/*wait for the Busy Flag*/
		while(BIT_IS_CLEAR(Config->I2Cx->SR2 , 1));
		/*Enable The I2C peripheral if it's not enabled*/
		if(GET_BIT(Config->I2Cx->CR1 , 0) == 0)
		{
			SET_BIT(Config->I2Cx->CR1 , 0);
		}
		else
		{
			/*Do Nothing*/
		}
		/*Generate a Start Condtion*/
		SET_BIT(Config->I2Cx->CR1 , 8);
		/*wait for the SB flag*/
		while(BIT_IS_CLEAR(Config->I2Cx->SR1 , 0));
		/*Clear SB Flag*/
		Temp = Config->I2Cx->SR1  ;
		/*Send the Slave address*/
		Config->I2Cx->DR = (uint8_t)SlaveAddress;
		/*wait for the ADDR flag to be set*/
		while(BIT_IS_CLEAR(Config->I2Cx->SR1 , 1));
		/*Clear the ADDR Flag*/
		_I2C_Clear_Addr_Flag(Config->I2Cx);
		/*wait until the Transfer buffer is empty*/
		while(BIT_IS_CLEAR(Config->I2Cx->SR1 , 7));
		/*write the memory address*/
		for(uint32_t Local_Index = 0 ; Local_Index < Size ; Size++)
		{
			Config->I2Cx->DR = Data[Local_Index];
			/*wait until the Transfer buffer is empty*/
		    while(BIT_IS_CLEAR(Config->I2Cx->SR1 , 7));
			
		}
		
		/*Generate Stop Condtion*/
		SET_BIT(Config->I2Cx->CR1 , 9);
		/*wait for the ADDR flag to be set*/
		while(BIT_IS_CLEAR(Config->I2Cx->SR1 , 4));
		
	}
}

/**********************************************/
static void SetI2cClock(I2c_ConfigType *Config)
{

	uint32_t CCR_Reg = 0 ;
	
	uint32_t Pclk = ((Config->I2C_PeripheralFreq) * 1000000) ;
	
	if(Config->ClockSpeed <= 100000)
	{	
		CCR_Reg = (Pclk / (Config->ClockSpeed << 1));
	}
	else
	{
		if(Config->DutyCycle == I2C_DUTYCYCLE_2)
		{
		
			CCR_Reg =(Pclk / (3 * Config->ClockSpeed));
		}
		else if(Config->DutyCycle == I2C_DUTYCYCLE_16_9)
		{
		
			CCR_Reg =(Pclk / (25 * Config->ClockSpeed));
		}
		else
		{
			/*Do Nothing*/
		}
	}
	
	
	Config->I2Cx->CCR |= CCR_Reg << 0 ;
	
	
}

static void SetI2cPins(I2c_ConfigType *Config)
{
	switch(Config->ID)
	{
		case I2C1_ID:
		
		#if( I2C1_PINs_REMAP == I2C_REMAP_ENABLE)
			
			RCC_EnableClock(RCC_AFIO_ID);
			RCC_EnableClock(RCC_GPIOB_ID);
			
			AFIO_Remap(USART1_REMAP , AFIO_REMAP_NONE);
			
			GPIO_InitPin(GPIOB , I2C1_SDA_PIN , AF_OUTPUT_OD_SPEED_50MHz);
			GPIO_InitPin(GPIOB , I2C1_SCL_PIN , AF_OUTPUT_OD_SPEED_50MHz);
				
		#else
			RCC_EnableClock(RCC_GPIOB_ID);
			
			GPIO_InitPin(GPIOB , I2C1_SDA_PIN_RM , AF_OUTPUT_OD_SPEED_50MHz);
			GPIO_InitPin(GPIOB , I2C1_SCL_PIN_RM , AF_OUTPUT_OD_SPEED_50MHz);
			
		#endif
		
		break ;
		case I2C2_ID: 
		
			RCC_EnableClock(RCC_GPIOB_ID);
			
			GPIO_InitPin(GPIOB , I2C2_SDA_PIN , AF_OUTPUT_OD_SPEED_50MHz);
			GPIO_InitPin(GPIOB , I2C2_SCL_PIN , AF_OUTPUT_OD_SPEED_50MHz);
				
					
		break ;
		default:
		break ;
	}
		
		
}

static void _I2C_Clear_Addr_Flag(I2C_Typedef *I2Cx)
{
   uint32_t val =  0;
	
	 val = I2Cx->SR1;
	 val = I2Cx->SR2;
	
}



