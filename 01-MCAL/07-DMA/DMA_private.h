/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 3 October 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/
#ifndef DMA_PRIVATE_H
#define DMA_PRIVATE_H



#define DMA1_BASE			 (0x40020000)

#define DMA1       			 ((DMA_Typedef *) DMA1_BASE)

#define DMA1_NUM_OF_CHANNELS		7

#define DMA1_CHANNEL1_BASE	 (DMA1_BASE + 0x08)	
#define DMA1_CHANNEL2_BASE   (DMA1_BASE + 0x1C)
#define DMA1_CHANNEL3_BASE   (DMA1_BASE + 0x30)
#define DMA1_CHANNEL4_BASE   (DMA1_BASE + 0x44)
#define DMA1_CHANNEL5_BASE   (DMA1_BASE + 0x58)
#define DMA1_CHANNEL6_BASE   (DMA1_BASE + 0x6C)
#define DMA1_CHANNEL7_BASE   (DMA1_BASE + 0x80)


#define DMA1_CHANNEL1       ((DMA_Channel_Typedef *)	DMA1_CHANNEL1_BASE)	
#define DMA1_CHANNEL2		((DMA_Channel_Typedef *)	DMA1_CHANNEL2_BASE)
#define DMA1_CHANNEL3		((DMA_Channel_Typedef *)	DMA1_CHANNEL3_BASE)
#define DMA1_CHANNEL4		((DMA_Channel_Typedef *)	DMA1_CHANNEL4_BASE)
#define DMA1_CHANNEL5       ((DMA_Channel_Typedef *)	DMA1_CHANNEL5_BASE)
#define DMA1_CHANNEL6       ((DMA_Channel_Typedef *)	DMA1_CHANNEL6_BASE)
#define DMA1_CHANNEL7       ((DMA_Channel_Typedef *)	DMA1_CHANNEL7_BASE)


#define DMA_TRANSFER_ERROR_CALLBACK_ENABLE		0
#define DMA_TRANSFER_ERROR_CALLBACK_DISABLE		1

#define DMA_HALF_TRANSFER_CALLBACK_ENABLE		0
#define DMA_HALF_TRANSFER_CALLBACK_DISABLE		1

#define DMA_TRANSFER_COMPLETE_CALBACK_ENABLE	0
#define DMA_TRANSFER_COMPLETE_CALBACK_DISABLE	1

typedef struct 
{
	volatile uint32_t CCR  	;
	volatile uint32_t CNDTR	;
	volatile uint32_t CPAR 	;
	volatile uint32_t CMAR 	;
		uint32_t Reserved   ;
	
}DMA_Channel_Typedef;

typedef struct
{
	volatile uint32_t ISR ;
	volatile uint32_t IFCR;
	
}DMA_Typedef;

void SetInitFlag(DMA_Channel_Typedef *DMA_Channel);
uint8_t CheckInitFlag(DMA_Channel_Typedef *DMA_Channel);


#endif /*DMA_PRIVATE_H*/
