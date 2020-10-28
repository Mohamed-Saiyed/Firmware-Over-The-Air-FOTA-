/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 13 ‎September 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/

#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H

#define GPIOA_BASE	 (0x40010800)
#define GPIOB_BASE   (0x40010C00)
#define GPIOC_BASE   (0x40011000)

#define GPIO_PORT_A		((GPIO_Typedef *) GPIOA_BASE)
#define GPIO_PORT_B		((GPIO_Typedef *) GPIOB_BASE)
#define GPIO_PORT_C		((GPIO_Typedef *) GPIOC_BASE)

#define GPIO_LCKR_LCKK_POS		(16)
#define GPIO_LCKR_LCKK			((0x1UL) << GPIO_LCKR_LCKK_POS)

typedef struct
{
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;
	
}GPIO_Typedef;




#endif /*GPIO_PRIVATE_H*/
