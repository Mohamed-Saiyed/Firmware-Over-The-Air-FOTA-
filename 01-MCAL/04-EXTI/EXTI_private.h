/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 20 ‎September 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/
#ifndef EXTI_PRIVATE_H
#define EXTI_PRIVATE_H


#define EXTI_BASE	(0x40010400)

#define EXTI 		((EXTI_typedef *)EXTI_BASE)

typedef struct 
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
	
}EXTI_typedef;








#endif /*EXTI_PRIVATE_H*/
