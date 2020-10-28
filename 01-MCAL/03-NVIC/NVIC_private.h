/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 17 ‎September 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/

#ifndef NVIC_PRIVATE_H
#define NVIC_PRIVATE_H


#define NVIC_BASE	    	(0xE000E100)
#define NVIC				((NVIC_Typedef *)NVIC_BASE)


#define NVIC_PRIORITY_BITS	4 		
					
#define SCB_AIRCR			*((volatile uint32_t *)0xE000ED0C)

#define SCB_VECT_KEY		((uint32_t)0x5FA)		
#define SCB_VECT_KEY_POS	(16)

#define SCB_PRIGROUP_POS    (8)

#define SCB_VECT_KEY_MSK 	(((uint32_t)0xFFFF) << SCB_VECT_KEY_POS)
#define SCB_PRIGROUP_MSK    (((uint32_t)0x07)  << SCB_PRIGROUP_POS)


typedef struct
{
	volatile uint32_t ISER[8U]  ;
		uint32_t Reserved0[24U] ;
	volatile uint32_t ICER[8U]  ;
		uint32_t Reserved1[24U] ;
	volatile uint32_t ISPR[8U]  ;
		uint32_t Reserved2[24U] ;
	volatile uint32_t ICPR[8U]  ;	
		uint32_t Reserved3[24U] ;
	volatile uint32_t IABR[8U]  ;	
		uint32_t Reserved4[56U] ;
	volatile uint8_t IPR[240U]  ;	
		uint32_t Reserved5[644U];
	volatile uint8_t STIR[240U] ;	
	
}NVIC_Typedef;

#endif /*NVIC_PRIVATE_H*/

