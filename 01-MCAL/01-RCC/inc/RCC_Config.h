/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 30 August 2020 	    					 */		
/* Version  : V01										 */	
/*********************************************************/

#ifndef RCC_CONFIG_H
#define RCC_CONFIG_H

#define RCC_SYS_CLOCK	8000000

/*Options:
         RCC_HSE_CRYSTAL
		 RCC_HSE_RC
		 RCC_HSI
		 RCC_PLL           */
#define RCC_CLOCK_TYPE		RCC_PLL
	 
#if (RCC_CLOCK_TYPE == RCC_PLL)
	
/*Options:
		 RCC_PLL_INPUT_HSI_DIV2
		 RCC_PLL_INPUT_HSE_DIV2
		 RCC_PLL_INPUT_HSE      */
	#define RCC_PLL_INPUT	 RCC_PLL_INPUT_HSE
	
/*Options:
		RCC_PLL_MULL2
		RCC_PLL_MULL3
		RCC_PLL_MULL4
		RCC_PLL_MULL5
		RCC_PLL_MULL6
		RCC_PLL_MULL7
		RCC_PLL_MULL8
		RCC_PLL_MULL9
		RCC_PLL_MULL10
		RCC_PLL_MULL11
		RCC_PLL_MULL12
		RCC_PLL_MULL13
		RCC_PLL_MULL14
		RCC_PLL_MULL15
		RCC_PLL_MULL16               */
	#define RCC_PLL_MULL_VAL	 RCC_PLL_MULL9	

/*Options:
		 RCC_CFGR_HPRE_DIV1	     
		 RCC_CFGR_HPRE_DIV2	
		 RCC_CFGR_HPRE_DIV8	
		 RCC_CFGR_HPRE_DIV16 */ 
	#define RCC_AHB_DIV		RCC_CFGR_HPRE_DIV1
	
/*Options:
		 RCC_CFGR_PPRE1_DIV1	     
		 RCC_CFGR_PPRE1_DIV2	
		 RCC_CFGR_PPRE1_DIV4	
		 RCC_CFGR_PPRE1_DIV8	
         RCC_CFGR_PPRE1_DIV16   */
	#define RCC_APB1_DIV	RCC_CFGR_PPRE1_DIV2

/*Options:
		 RCC_CFGR_PPRE2_DIV1	     
		 RCC_CFGR_PPRE2_DIV2	
		 RCC_CFGR_PPRE2_DIV4	
		 RCC_CFGR_PPRE2_DIV8	
         RCC_CFGR_PPRE2_DIV16   */
	#define RCC_APB2_DIV	RCC_CFGR_PPRE2_DIV1

/*Options:
		 FLASH_LATENCY_WS_0	  if 0 < SYSCLK ≤ 24 MHz   
		 FLASH_LATENCY_WS_1	  if 24 MHz < SYSCLK ≤ 48 MHz
		 FLASH_LATENCY_WS_2	  if 48 MHz < SYSCLK ≤ 72 MHz         */
	#define RCC_FLASH_LATENCY	FLASH_LATENCY_WS_2
	
#endif	/*RCC_PLL*/


#endif /*RCC_CONFIG_H*/

