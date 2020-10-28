/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 30 August 2020 	    					 */		
/* Version  : V01										 */	
/*********************************************************/

#include "Std_types.h"
#include "BIT_MATH.h"


#include "RCC_interface.h"
#include "RCC_private.h"
#include "RCC_Config.h"

ErrorStatus RCC_SysClockInit(void)
{
	/*Temp variable to store the return value*/
	uint8_t retvalue = 0 ;
	
	#if(RCC_CLOCK_TYPE == RCC_HSE_CRYSTAL)
		
		/*Turn on HEI clock*/
		RCC->CR = RCC_CR_HSE_ON;
		
		/*wait till HSE is ready*/
		while(BIT_IS_CLEAR(RCC->CR ,RCC_CR_HSERDY_POS));
			
		/*Make HSE as a system clock*/	
		RCC->CFGR |= RCC_CFGR_SW_HSE;
		
	    /*Double check if t HSE is set as system clock source*/	
	    if((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) == (uint32_t)0x04)
		{			
			retvalue =  E_OK;
		}
		else
		{
			retvalue =  E_NOK;
		}
		
	#elif(RCC_CLOCK_TYPE == RCC_HSE_RC)
		
		/*Turn on HSE clock with By pass option to turn on RC circuit*/
		RCC->CR = RCC_CR_HSE_ON | RCC_CR_HSEBYP;
		
		/*wait till HSE is ready*/
		while(BIT_IS_CLEAR(RCC->CR ,RCC_CR_HSERDY_POS);
		/*Make HSE as a system clock*/
		RCC->CFGR |= RCC_CFGR_SW_HSE;
		
		/*Double check if t HSE is set as system clock source*/	
	    if((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) == (uint32_t)0x04)
		{			
			retvalue =  E_OK;
		}
		else
		{
			retvalue =  E_NOK;
		}
		
	#elif(RCC_CLOCK_TYPE == RCC_HSI)
		
		 /*turn on HSI clock*/
		RCC->CR = RCC_CR_HSI_ON;
		
	    /*wait till HSE is ready*/
		while(BIT_IS_CLEAR(RCC->CR ,RCC_CR_HSIRDY_POS))
			
		/*Make HSI as a system clock*/	
		RCC->CFGR |= RCC_CFGR_SW_HSI;
	
		/*Double check if t HSI is set as system clock source*/		
	    if((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) == (uint32_t)0x00)
		{
		    retvalue =  E_OK;
		}
		else
		{
			retvalue =  E_NOK;
		}
		
	#elif (RCC_CLOCK_TYPE == RCC_PLL)
		#if (RCC_PLL_INPUT == RCC_PLL_INPUT_HSI_DIV2)
			
			/*turn on HSI clock*/
			RCC->CR = RCC_CR_HSI_ON;
			/*wait till HSE is ready*/
			while(BIT_IS_CLEAR(RCC->CR , RCC_CR_HSIRDY_POS));
			
			/*Enable flash prefetch buffer*/
			FLASH_ACR |= (1 << 4);
			/*Reset flash latency bits position*/
			FLASH_ACR &= ~ FLASH_LATENCY;
			/*set the flash latency wait states configured in config file*/
			FLASH_ACR |=  RCC_FLASH_LATENCY;
			
			/*set AHB bus Prescaler */ /*set APB1 bus Prescaler */
			/*set APB2 bus Prescaler */ /*configured in config file*/
			RCC->CFGR |= RCC_AHB_DIV | RCC_APB1_DIV | RCC_APB2_DIV ; 
			
			/*Resetting PLL Input clock source bits && PLL HSE Prescaler bits &&PLL Multiplication factor bits*/
			RCC->CFGR &= ~(RCC_CFGR_PLLSRC| RCC_CFGR_PLLXTPRE| RCC_CFGR_PLLMULL);
			/*Set the PLL Multiplication Factor and make (HSI clock)/2 as PLL Input clock source*/
			RCC->CFGR |= RCC_PLL_MULL_VAL | RCC_CFGR_PLLSRC_HSI_DIV2;
			
		#elif (RCC_PLL_INPUT == RCC_PLL_INPUT_HSE_DIV2)
			/*turn on HSE clock*/
			RCC->CR = RCC_CR_HSE_ON;
			/*wait till HSE is ready*/
			while(BIT_IS_CLEAR(RCC->CR , RCC_CR_HSERDY_POS));
			
			/*Enable flash prefetch buffer*/
			FLASH_ACR |= (1 << 4);
			/*Reset flash latency bits position*/
			FLASH_ACR &= ~ FLASH_LATENCY;
			/*set the flash latency wait states configured in config file*/
			FLASH_ACR |=  RCC_FLASH_LATENCY;
			
			/*set AHB bus Prescaler */ /*set APB1 bus Prescaler */
			/*set APB2 bus Prescaler */ /*configured in config file*/
			RCC->CFGR |= RCC_APB1_DIV | RCC_APB1_DIV | RCC_APB2_DIV ; 
			
			/*Resetting PLL Input clock source bits && PLL HSE Prescaler bits &&PLL Multiplication factor bits*/
			RCC->CFGR &= ~(RCC_CFGR_PLLSRC| RCC_CFGR_PLLXTPRE| RCC_CFGR_PLLMULL);
			/*Set the PLL Multiplication Factor and make (HSE clock)/2 as PLL Input clock source*/
			RCC->CFGR |= RCC_PLL_MULL_VAL | RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLXTPRE_HSE_DIV2;
			
		#elif (RCC_PLL_INPUT == RCC_PLL_INPUT_HSE)
			
			/*turn on HSE clock*/
			RCC->CR = RCC_CR_HSE_ON;
			/*wait till HSE is ready*/
			while(BIT_IS_CLEAR(RCC->CR , RCC_CR_HSERDY_POS));
			
			/*Enable flash prefetch buffer*/
			FLASH_ACR |= (1 << 4);
			/*Reset flash latency bits position*/
			FLASH_ACR &= ~FLASH_LATENCY;
			/*set the flash latency wait states configured in config file*/
			FLASH_ACR |=  RCC_FLASH_LATENCY;
			
			/*set AHB bus Prescaler */ /*set APB1 bus Prescaler */
			/*set APB2 bus Prescaler */ /*configured in config file*/
			RCC->CFGR |= RCC_APB1_DIV | RCC_APB1_DIV | RCC_APB2_DIV ; 
			
			/*Resetting PLL Input clock source bits && PLL HSE Prescaler bits &&PLL Multiplication factor bits*/
			RCC->CFGR &= ~(RCC_CFGR_PLLSRC| RCC_CFGR_PLLXTPRE| RCC_CFGR_PLLMULL);
			/*Set the PLL Multiplication Factor and make (HSE clock)/2 as PLL Input clock source*/
			RCC->CFGR |= RCC_PLL_MULL_VAL | RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLXTPRE_HSE;
			
		#else
			#error "You choosed a wrong PLL input clock"
		#endif
		
		/*/*turn on PLL Engine*/
		RCC->CR |= RCC_CR_PLL_ON;
		/*wait till PLL Engine is ready*/
		while(BIT_IS_CLEAR(RCC->CR , RCC_CR_PLLRDY_POS));
		
		/*Resetting System Clock source bits*/
		RCC->CFGR &= ~RCC_CFGR_SW;
		/*make PLL Engine as system clock source*/
		RCC->CFGR |= RCC_CFGR_SW_PLL;
		
		/*Double check if t PLL Engine is set as system clock source*/
		if((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) == (uint32_t)0x08)
		{
			retvalue = E_OK ;
		}
		else
		{
			retvalue = E_NOK ;
		}
		
	#else
		#error "You choosed a wrong system clock"
	#endif
	
	return retvalue ;
}

ErrorStatus RCC_EnableClock(PerId Peripheral_Id)
{
	/*Temp variable to store the return value*/
	uint8_t retvalue = E_OK ;
	
	/*AHB BUS Peripheral_Id starts from 0 to 31*/
	if(Peripheral_Id <= 31)
	{
		SET_BIT(RCC->AHBENR , Peripheral_Id);
	}
	/*APB2 BUS Peripheral_Id starts from 32 to 63 (AHB BUS Peripheral_Id + 32)*/
	else if(Peripheral_Id <= 63)
	{
		/*Peripheral Clock Enable/Disable bit in APB2ENR REG  = Peripheral_Id - 32*/
		Peripheral_Id = Peripheral_Id - 32 ;
		SET_BIT(RCC->APB2ENR, Peripheral_Id);
	}
	/*APB2 BUS Peripheral_Id starts from 64 to 95 (AHB BUS Peripheral_Id + 64)*/
	else if(Peripheral_Id <= 95)
	{
		/*Peripheral Clock Enable/Disable bit in APB1ENR REG  = Peripheral_Id - 64*/
		Peripheral_Id = Peripheral_Id - 64 ;
		SET_BIT(RCC->APB1ENR, Peripheral_Id);		
	}
	else
	{
		/*return Error*/
		retvalue = E_NOK; 
	}
	
	return retvalue ;
}

ErrorStatus RCC_DisableClock(PerId Peripheral_Id)
{
	/*Temp variable to store the return value*/
	uint8_t retvalue = E_OK ;
	
	/*AHB BUS Peripheral_Id starts from 0 to 31*/
	if(Peripheral_Id <= 31)
	{
		CLR_BIT(RCC->AHBENR , Peripheral_Id);
	}
	/*APB2 BUS Peripheral_Id starts from 32 to 63 (AHB BUS Peripheral_Id + 32)*/
	else if(Peripheral_Id <= 63)
	{
		/*Peripheral Clock Enable/Disable bit in APB2ENR REG  = Peripheral_Id - 32*/
		Peripheral_Id = Peripheral_Id - 32 ;
		CLR_BIT(RCC->APB2ENR, Peripheral_Id);
	}
	/*APB2 BUS Peripheral_Id starts from 64 to 95 (AHB BUS Peripheral_Id + 64)*/
	else if(Peripheral_Id <= 95)
	{
		/*Peripheral Clock Enable/Disable bit in APB1ENR REG  = Peripheral_Id - 64*/
		Peripheral_Id = Peripheral_Id - 64 ;/**/
		CLR_BIT(RCC->APB1ENR, Peripheral_Id);		
	}
	else
	{
		/*return Error*/
		retvalue = E_NOK; 
	}
	
	return retvalue ;
}
