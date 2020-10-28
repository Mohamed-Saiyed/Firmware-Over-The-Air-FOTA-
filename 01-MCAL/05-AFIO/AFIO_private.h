/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 20 ‎September 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/
#ifndef AFIO_PRIVATE_H
#define AFIO_PRIVATE_H


#define AFIO_BASE		(0x40010000)

#define AFIO			((AFIO_typedef *)AFIO_BASE)

typedef struct
{
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR[4];
	volatile uint32_t MAPR2;
		
}AFIO_typedef;




#endif /*AFIO_PRIVATE_H*/	
