/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 13 ‎September 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/

#include "Std_types.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "GPIO_private.h"

ErrorStatus GPIO_InitPin(GPIO_Typedef *GPIOx , DIO_Pin_t Pin , DIO_Mode_t Mode)
{
	/*Temp variable to store the return value*/
	uint8_t retvalue = E_OK ;
	
	/*Check on Pin Value*/
	if(Pin <= GPIO_PIN_15)
	{
		/*Differentiate between the high control and low rigesters*/
		/*Low Control rigster CRL[0,7]*/
		if(Pin <= GPIO_PIN_7)
		{
			GPIOx->CRL &= ~((uint32_t)(0xF)  << (Pin * 4));/*Resetting the corrisponding pin Bits value*/
			GPIOx->CRL |=  ((uint32_t)(Mode) << (Pin * 4));
		}
		/*High Control rigster CRL[8,15]*/
		else if(Pin <= GPIO_PIN_15)
		{
			Pin = Pin - 8 ;/*High control rigesters controls pin[8,15] and starts with bit 0*/
			GPIOx->CRH &= ~((uint32_t)(0xF)  << (Pin * 4));
			GPIOx->CRH |=  ((uint32_t)(Mode) << (Pin * 4));
		}
		else
		{
			/*Do nothing*/
		}
	}
	else
	{
		retvalue = E_NOK;
	}
	
	return retvalue;
}

ErrorStatus GPIO_WritePin(GPIO_Typedef *GPIOx, DIO_Pin_t Pin, DIO_PinStatus_t Staus)
{
	/*Temp variable to store the return value*/
	uint8_t retvalue = E_OK ;
	
	/*Check on Pin Value*/
	if(Pin <= GPIO_PIN_15)
	{
		if(Staus == GPIO_PIN_HIGH)
		{
			SET_BIT(GPIOx->ODR,Pin);
		}
		else if (Staus == GPIO_PIN_LOW)
		{
			CLR_BIT(GPIOx->ODR,Pin);
		}
		else
		{
			
		}
	}
	else
	{
		retvalue = E_NOK;
	}
	
	return retvalue;
}

ErrorStatus GPIO_ReadPin(GPIO_Typedef *GPIOx , DIO_Pin_t Pin, uint8_t *Buffer)
{
	/*Temp variable to store the return value*/
	uint8_t retvalue = E_OK ;
	
	/*Check on Pin Value*/
	if((Pin <= GPIO_PIN_15) && (Buffer != NULL))
	{
		*Buffer = GET_BIT(GPIOx->IDR,Pin);
	}
	else
	{
		retvalue = E_NOK;
	}
		
	return retvalue ;
}

ErrorStatus GPIO_TogglePin(GPIO_Typedef *GPIOx , DIO_Pin_t Pin)
{
	/*Temp variable to store the return value*/
	uint8_t retvalue = E_OK ;
	
	/*Check on Pin Value*/
	if(Pin <= GPIO_PIN_15)
	{
		TOGGLE_BIT(GPIOx->ODR,Pin);
	}
	else
	{
		retvalue = E_NOK;
	}	
	
	return retvalue;
}

ErrorStatus GPIO_LockPin(GPIO_Typedef *GPIOx , DIO_Pin_t Pin)
{
	/*Temp variable to store the return value*/
	uint8_t retvalue = 0 ;
								/*0x00010000*/
	volatile uint32_t temp = GPIO_LCKR_LCKK ; /*Storing Value of LCKK Bit in temp variable*/ 
	
	/*Check on Pin Value*/
	if(Pin <= GPIO_PIN_15)
	{
		
		/*Oring the Pin value with the LCKK Bit*/
		/*Setting the corrisponding pin bit has no effect without setting LCKK BIT*/
		SET_BIT(temp , Pin);
		/*Set LCKK Bit and corresponding pin bit*/
		GPIOx->LCKR = temp;
		/*Reset LCKR bit*/
		GPIOx->LCKR = Pin;
		/*Set LCKK Bit*/
		GPIOx->LCKR = temp;
		/*first read of the rigster is mandatory*/
		temp = GPIOx->LCKR;
		/*second read just to confirm the lock is active*/
		if(((GPIOx->LCKR) & GPIO_LCKR_LCKK))
		{
			retvalue = E_OK;
		}
		else
		{
			retvalue = E_NOK;
		}
	
	}
	else
	{
		retvalue = E_NOK;
	}
	
	return retvalue;
}
