/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 17 ‎September 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/

#include "Std_types.h"
#include "BIT_MATH.h"

#include "NVIC_interface.h"
#include "NVIC_private.h"
#include "NVIC_config.h"

ErrorStatus NVIC_EnableInterrupt(IRQn_Type IRQn)
{
	/*Temp variable to store the return Function status */
	uint8_t State = 0 ;
	/*calculate the area index value followin MISRA Rules*/
	uint8_t Arr_index = 0 ;
	/*Check IRQ number if it is less than zero*/
	if(IRQn >= 0)
	{
		/*(IRQn >> 5) == (IRQn / 32) Means: every 31(Because ISER is 32-bit wide) IRQ numbers go to the higher rigsters*/
		
		Arr_index = ((uint8_t)(IRQn) >> 5);
		
		/*Masking (IRQn & 0x1FUL) makes IRQn that is higher than 31 matches ISER Bit postion (Because ISER is 32-bit wide)
		 When it reachs 32 it starts count from zero again*/
		NVIC->ISER[Arr_index] |= (1 << (((uint32_t)IRQn) & 0x1FUL));
		State = E_OK ;
	}
	else
	{
		State = E_NOK ;
	}
	
  return State ;
}	

ErrorStatus NVIC_DisableInterrupt(IRQn_Type IRQn)
{
	/*Temp variable to store the return Function status */
	uint8_t State = 0 ;
	
	/*calculate the area index value followin MISRA Rules*/
	uint8_t Arr_index = 0 ;
	
	/*Check IRQ number if it is less than zero*/
	if(IRQn >= 0)
	{
		/*(IRQn >> 5) == (IRQn / 32) Means: every 31(Because ICER is 32-bit wide) IRQ numbers go to the higher rigsters*/
		Arr_index = (((uint8_t)IRQn) >> 5);
		
		/*Masking (IRQn & 0x1FUL) makes IRQn that is higher than 31 matches ICER Bit postion (Because ICER is 32-bit wide)
		 When it reachs 32 it starts count from zero again*/
		NVIC->ICER[Arr_index] |= (1 << (((uint32_t)IRQn) & 0x1FUL));
		State = E_OK ;
	}
	else
	{
		State = E_NOK ;
	}
	
  return State ;
}	

ErrorStatus NVIC_SetPendingFlag(IRQn_Type IRQn)
{
	/*Temp variable to store the return Function status */
	uint8_t State = 0 ;
	
	/*calculate the area index value followin MISRA Rules*/
	uint8_t Arr_index = 0 ;
	
	/*Check IRQ number if it is less than zero*/
	if(IRQn >= 0)
	{
		/*(IRQn >> 5) == (IRQn / 32) Means: every 31(Because ISPR is 32-bit wide) IRQ numbers go to the higher rigsters*/
		 Arr_index = (((uint8_t)IRQn) >> 5);
		/*Masking (IRQn & 0x1FUL) makes IRQn that is higher than 31 matches ISPR Bit postion (Because ISPR is 32-bit wide)
		 When it reachs 32 it starts count from zero again*/
		NVIC->ISPR[Arr_index] |= (1 << (((uint32_t)IRQn) & 0x1FUL));
		State = E_OK ;
	}
	else
	{
		State = E_NOK ;
	}
	
  return State ;
}	

ErrorStatus NVIC_ClearPendingFlag(IRQn_Type IRQn)
{
	/*Temp variable to store the return Function status */
	uint8_t State = 0 ;
	
	/*calculate the area index value followin MISRA Rules*/
	uint8_t Arr_index = 0 ;
	
	/*Check IRQ number if it is less than zero*/
	if(IRQn >= 0)
	{
		/*(IRQn >> 5) == (IRQn / 32) Means: every 31(Because ICPR is 32-bit wide) IRQ numbers go to the higher rigsters*/
		 Arr_index = (((uint8_t)IRQn) >> 5);
		 
		/*Masking (IRQn & 0x1FUL) makes IRQn that is higher than 31 matches ICPR Bit postion (Because ICPR is 32-bit wide)
		 When it reachs 32 it starts count from zero again*/
		NVIC->ICPR[Arr_index] |= (1 << (((uint32_t)IRQn) & 0x1FUL));
		State = E_OK ;
	}
	else
	{
		State = E_NOK ;
	}
	
  return State ;
}	

ErrorStatus NVIC_GetActiveFlag(IRQn_Type IRQn , uint8_t *Buffer)
{
	/*Temp variable to store the return Function status */
	uint8_t State = 0 ;
	
	/*calculate the area index value followin MISRA Rules*/
	uint8_t Arr_index = 0 ;
	
	/*Check IRQ number if it is less than zero*/
	if(IRQn >= 0)
	{
		/*(IRQn >> 5) == (IRQn / 32) Means: every 31(Because IABR is 32-bit wide) IRQ numbers go to the higher rigsters*/
		 Arr_index = (((uint8_t)IRQn) >> 5) ;
		 
		/*Masking (IRQn & 0x1FUL) makes IRQn that is higher than 31 matches IABR Bit postion (Because IABR is 32-bit wide)
		 When it reachs 32 it starts count from zero again*/
		*Buffer = GET_BIT(NVIC->IABR[Arr_index] , (((uint32_t)IRQn) & 0x1FUL));
		State = E_OK ;
	}
	else
	{
		State = E_NOK ;
	}
	
  return State ;
}	

ErrorStatus NVIC_SetPriorityGrouping(NVIC_PriorityGroup PriorityGroup)
{
	/*Temp variable to store the return Function status */
	uint8_t State = 0 ;
	
	/*Temp variable to store SCB_AIRCR value*/
	uint32_t register_val = 0 ;

	register_val = SCB_AIRCR ; /* read old register configuration */
	
	register_val &=~ ( SCB_VECT_KEY_MSK | SCB_PRIGROUP_MSK);/*Clear bits that is going to be configured*/
	
	/*Check IRQ number if it is less than 7*/
	if(PriorityGroup <= 7)
	{
		/* insert SCB_AIRCR Key and insert new PriorityGroup */
		register_val |= (register_val | (SCB_VECT_KEY << SCB_VECT_KEY_POS) | ((uint32_t)PriorityGroup << SCB_PRIGROUP_POS));
		/* Store the new value to SCB_AIRCR register */
		SCB_AIRCR = register_val ;
		State = E_OK ;
	}
	else
	{
		State = E_NOK ;
	}
	
  return State ;
}

ErrorStatus NVIC_SetPriority(IRQn_Type IRQn , uint8_t Priority)
{
	/*Temp variable to store the return Function status */
	uint8_t State = 0 ;
	
	/*Check IRQ number if it is less than zero*/
	if(IRQn >= 0)
	{
		/*each interrypet has its own ICPR 8-bit wide rigster*/
		NVIC->IPR[IRQn] |= (uint8_t)(((uint32_t)Priority << (8 - NVIC_PRIORITY_BITS)) & 0xFFUL);/*Stm32 just uses the 4MSP bits for Priority */
		State = E_OK ;
	}
	else
	{
		State = E_NOK ;
	}
	
  return State ;
}

