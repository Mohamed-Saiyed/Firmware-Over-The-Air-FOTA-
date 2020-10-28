/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 23 ‎September 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/

#ifndef SYSTICK_PRIVATE_H
#define SYSTICK_PRIVATE_H

#define SYSTICK_BASE	(0xE000E010)

#define SysTick			((SysTick_Type *) SYSTICK_BASE )

#define AHP_CLK_DIV8	0
#define AHP_CLK     	1

/*SysTick interval modes*/

#define SYSTICK_INTERVAL_SINGLE 	5
#define SYSTICK_INTERVAL_PERIODIC	6


typedef struct
{
	volatile uint32_t CTRL ;
	volatile uint32_t LOAD ;
	volatile uint32_t VAL  ;
	volatile uint32_t CALIB;
	
}SysTick_Type;

#endif /*SYSTICK_PRIVATE_H*/
