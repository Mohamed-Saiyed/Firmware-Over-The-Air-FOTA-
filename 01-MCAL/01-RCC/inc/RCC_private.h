/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 30 August 2020 	    					 */		
/* Version  : V01										 */	
/*********************************************************/

#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H

#define RCC_BASE  	 (0x40021000)

#define RCC       	 ((RCC_Typedef *) RCC_BASE)

 
#define FLASH_ACR	 				*((volatile uint32_t *)0x40022000)

/*Flash Latency for high speed clocks*/
#define FLASH_LATENCY		   		(0x7 << 0)
#define FLASH_LATENCY_WS_0			(0x0 << 0)
#define FLASH_LATENCY_WS_1			(0x1 << 0)
#define FLASH_LATENCY_WS_2			(0x2 << 0)


#define RCC_CR_HSION_POS			(0)
#define RCC_CR_HSI_ON 				(0x1UL << RCC_CR_HSION_POS )
#define RCC_CR_HSIRDY_POS			(1)
#define RCC_CR_HSIRDY				(0x1UL << RCC_CR_HSIRDY_POS )
#define RCC_CR_HSEON_POS			(16)
#define RCC_CR_HSE_ON				(0x1UL << RCC_CR_HSEON_POS )
#define RCC_CR_HSERDY_POS			(17)
#define RCC_CR_HSERDY				(0x1UL << RCC_CR_HSERDY_POS )
#define RCC_CR_HSEBYP_POS			(18)
#define RCC_CR_HSEBYP				(0x1UL << RCC_CR_HSEBYP_POS )
#define RCC_CR_PLLON_POS			(24)
#define RCC_CR_PLL_ON 				(0x1UL << RCC_CR_PLLON_POS )
#define RCC_CR_PLLRDY_POS			(25)
#define RCC_CR_PLLRDY				(0x1UL << RCC_CR_PLLRDY_POS )
	
#define RCC_CFGR_SW_POS				(0)
#define RCC_CFGR_SW             	(0x3 << RCC_CFGR_SW_POS)
#define RCC_CFGR_SW_PLL				(0x2 << RCC_CFGR_SW_POS)
#define RCC_CFGR_SW_HSE				(0x1 << RCC_CFGR_SW_POS)
#define RCC_CFGR_SW_HSI				(0x0 << RCC_CFGR_SW_POS)
	
#define RCC_CFGR_SWS_POS   			(2)
#define RCC_CFGR_SWS            	(0x3 << RCC_CFGR_SWS_POS)
	
#define RCC_CFGR_HPRE_POS			(4)
#define RCC_CFGR_HPRE_DIV1			(0x0   << RCC_CFGR_HPRE_POS)
#define RCC_CFGR_HPRE_DIV2			(0x8UL << RCC_CFGR_HPRE_POS)
#define RCC_CFGR_HPRE_DIV8			(0x9UL << RCC_CFGR_HPRE_POS)
#define RCC_CFGR_HPRE_DIV16			(0xAUL << RCC_CFGR_HPRE_POS)

#define RCC_CFGR_PPRE1_POS			(8)
#define RCC_CFGR_PPRE1_DIV1			(0x0   << RCC_CFGR_PPRE1_POS)
#define RCC_CFGR_PPRE1_DIV2			(0x4UL << RCC_CFGR_PPRE1_POS)
#define RCC_CFGR_PPRE1_DIV4			(0x5UL << RCC_CFGR_PPRE1_POS)
#define RCC_CFGR_PPRE1_DIV8	    	(0x6UL << RCC_CFGR_PPRE1_POS)
#define RCC_CFGR_PPRE1_DIV16		(0x7UL << RCC_CFGR_PPRE1_POS)

#define RCC_CFGR_PPRE2_POS		  	(11)
#define RCC_CFGR_PPRE2_DIV1		  	(0x0   << RCC_CFGR_PPRE2_POS)
#define RCC_CFGR_PPRE2_DIV2		  	(0x4UL << RCC_CFGR_PPRE2_POS)
#define RCC_CFGR_PPRE2_DIV4		  	(0x5UL << RCC_CFGR_PPRE2_POS)
#define RCC_CFGR_PPRE2_DIV8		  	(0x6UL << RCC_CFGR_PPRE2_POS)
#define RCC_CFGR_PPRE2_DIV16	  	(0x7UL << RCC_CFGR_PPRE2_POS)

#define RCC_CFGR_PLLSRC_POS			(16)
#define RCC_CFGR_PLLSRC_HSI_DIV2	(0x0 << RCC_CFGR_PLLSRC_POS)
#define RCC_CFGR_PLLSRC_HSE			(0x1UL << RCC_CFGR_PLLSRC_POS)

#define RCC_CFGR_PLLXTPRE_POS		(17)
#define RCC_CFGR_PLLXTPRE_HSE_DIV2	(0x1UL<< RCC_CFGR_PLLXTPRE_POS)
#define RCC_CFGR_PLLXTPRE_HSE		(0x0 << RCC_CFGR_PLLXTPRE_POS)

#define  RCC_CFGR_PLLMULL_POS		(18)
#define  RCC_CFGR_PLLMULL           (0x15UL << RCC_CFGR_PLLMULL_POS)	
#define  RCC_CFGR_PLLMULL2  		(0x0UL << RCC_CFGR_PLLMULL_POS)		
#define  RCC_CFGR_PLLMULL3  		(0x1UL << RCC_CFGR_PLLMULL_POS)
#define  RCC_CFGR_PLLMULL4   		(0x2UL << RCC_CFGR_PLLMULL_POS)
#define  RCC_CFGR_PLLMULL5          (0x3UL << RCC_CFGR_PLLMULL_POS)
#define  RCC_CFGR_PLLMULL6          (0x4UL << RCC_CFGR_PLLMULL_POS)
#define  RCC_CFGR_PLLMULL7          (0x5UL << RCC_CFGR_PLLMULL_POS)
#define  RCC_CFGR_PLLMULL8          (0x6UL << RCC_CFGR_PLLMULL_POS)
#define  RCC_CFGR_PLLMULL9          (0x7UL << RCC_CFGR_PLLMULL_POS)
#define  RCC_CFGR_PLLMULL10         (0x8UL << RCC_CFGR_PLLMULL_POS)
#define  RCC_CFGR_PLLMULL11         (0x9UL << RCC_CFGR_PLLMULL_POS)
#define  RCC_CFGR_PLLMULL12         (0x10UL << RCC_CFGR_PLLMULL_POS)
#define  RCC_CFGR_PLLMULL13         (0x11UL << RCC_CFGR_PLLMULL_POS)
#define  RCC_CFGR_PLLMULL14         (0x12UL << RCC_CFGR_PLLMULL_POS)
#define  RCC_CFGR_PLLMULL15         (0x13UL << RCC_CFGR_PLLMULL_POS)
#define  RCC_CFGR_PLLMULL16         (0x14UL << RCC_CFGR_PLLMULL_POS)

#define RCC_CFGR_PLLSRC             RCC_CFGR_PLLSRC_HSE  
#define RCC_CFGR_PLLXTPRE           RCC_CFGR_PLLXTPRE_HSE_DIV2 


/*RCC System clock options*/
#define RCC_HSE_CRYSTAL				0
#define RCC_HSE_RC					1
#define RCC_HSI						2
#define RCC_PLL        				3


/*PLL Input clock source*/
#define RCC_PLL_INPUT_HSI_DIV2		0
#define RCC_PLL_INPUT_HSE_DIV2		1
#define RCC_PLL_INPUT_HSE     		2


/*AHP Bus Division factor options*/
#define RCC_PLL_AHB_DIV1		RCC_CFGR_HPRE_DIV1	
#define RCC_PLL_AHB_DIV2		RCC_CFGR_HPRE_DIV2	
#define RCC_PLL_AHB_DIV8		RCC_CFGR_HPRE_DIV8	
#define RCC_PLL_AHB_DIV16		RCC_CFGR_HPRE_DIV16	

/*APB1 Bus Division factor options*/
#define RCC_PLL_APB1_DIV1		RCC_CFGR_PPRE1_DIV1	
#define RCC_PLL_APB1_DIV2		RCC_CFGR_PPRE1_DIV2	
#define RCC_PLL_APB1_DIV4		RCC_CFGR_PPRE1_DIV4	
#define RCC_PLL_APB1_DIV8		RCC_CFGR_PPRE1_DIV8	
#define RCC_PLL_APB1_DIV16	    RCC_CFGR_PPRE1_DIV16

/*APB2 Bus Division factor options*/
#define RCC_PLL_APB2_DIV1		RCC_CFGR_PPRE2_DIV1	
#define RCC_PLL_APB2_DIV2		RCC_CFGR_PPRE2_DIV2	
#define RCC_PLL_APB2_DIV4		RCC_CFGR_PPRE2_DIV4	
#define RCC_PLL_APB2_DIV8		RCC_CFGR_PPRE2_DIV8	
#define RCC_PLL_APB2_DIV16	    RCC_CFGR_PPRE2_DIV16

/*PLL Multiplexing value*/
#define RCC_PLL_MULL2		RCC_CFGR_PLLMULL2 
#define RCC_PLL_MULL3       RCC_CFGR_PLLMULL3 
#define RCC_PLL_MULL4       RCC_CFGR_PLLMULL4 
#define RCC_PLL_MULL5       RCC_CFGR_PLLMULL5 
#define RCC_PLL_MULL6       RCC_CFGR_PLLMULL6 
#define RCC_PLL_MULL7       RCC_CFGR_PLLMULL7 
#define RCC_PLL_MULL8       RCC_CFGR_PLLMULL8 
#define RCC_PLL_MULL9       RCC_CFGR_PLLMULL9 
#define RCC_PLL_MULL10      RCC_CFGR_PLLMULL10
#define RCC_PLL_MULL11      RCC_CFGR_PLLMULL11
#define RCC_PLL_MULL12      RCC_CFGR_PLLMULL12
#define RCC_PLL_MULL13      RCC_CFGR_PLLMULL13
#define RCC_PLL_MULL14      RCC_CFGR_PLLMULL14
#define RCC_PLL_MULL15      RCC_CFGR_PLLMULL15
#define RCC_PLL_MULL16      RCC_CFGR_PLLMULL16


typedef struct
{
	volatile uint32_t CR 	   ;
	volatile uint32_t CFGR     ;
	volatile uint32_t CIR	   ;
	volatile uint32_t APB2RSTR ;
	volatile uint32_t APB1RSTR ;
	volatile uint32_t AHBENR   ;
	volatile uint32_t APB2ENR  ;
	volatile uint32_t APB1ENR  ;
	volatile uint32_t BDCR	   ;
	volatile uint32_t CSR      ;
	volatile uint32_t AHBSTR   ;
	volatile uint32_t CFGR2	   ;
	
}RCC_Typedef;


#endif /*RCC_PRIVATE_H*/
