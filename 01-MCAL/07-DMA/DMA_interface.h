/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 3 October 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/
#ifndef DMA_INTERFACE_H
#define DMA_INTERFACE_H

#include "DMA_private.h"
#include "DMA_cnofig.h"

#define DMA_PINC_ENABLE			1
#define DMA_PINC_DISABLE		0

#define DMA_MINC_ENABLE			1
#define DMA_MINC_DISABLE		0

typedef enum 
{
	DMA_PRIORITY_LOW      = 0 ,
	DMA_PRIORITY_MEDIUM   = 1 ,
	DMA_PRIORITY_HIGH     = 2 ,
	DMA_PRIORITY_VERYHIGH = 3 
	
}DMA_ChannelPriority_e;

typedef enum 
{
	DMA_MEMORYSIZE_BYTE	     = 0 ,
	DMA_MEMORYSIZE_HALFWORD	 = 1 ,
	DMA_MEMORYSIZE_WORD  	 = 2 ,
	
}DMA_MemoryDataSize_e;

typedef enum 
{
	DMA_PERIPHERALSIZE_BYTE	     = 0 ,
	DMA_PERIPHERALSIZE_HALFWORD	 = 1 ,
	DMA_PERIPHERALSIZE_WORD  	 = 2 ,
	
}DMA_PeripheralDataSize_e;

typedef enum 
{
	DMA_NORMAL_MODE   = 0 ,
	DMA_CIRCULAR_MODE = 1 ,
	
}DMA_Mode_e;


typedef enum 
{
	DMA_MEMORY_TO_MEMORY     = 0 ,
	DMA_MEMORY_TO_PERIPHERAL = 1 ,
	DMA_PERIPHERAL_TO_MEMORY = 2 
	
}DMA_Direction_e;

typedef struct 
{
	DMA_Channel_Typedef  *DMA_Channel 			;
				
	DMA_Mode_e Mode 				  			;
				
	DMA_ChannelPriority_e Priority    			;
	
	DMA_MemoryDataSize_e  MemoryDataSize        ; 
	
	DMA_PeripheralDataSize_e PeripheralDataSize ;
	
	uint8_t MemoryIncrement						;
	
	uint8_t PeripheralIncrement					;
	
	DMA_Direction_e  Direction					;
	
	#if(DMA_TRANSFER_ERROR_CALLBACK	  == DMA_TRANSFER_ERROR_CALLBACK_ENABLE)
		void (*DMA_TransferErrorCallBack)    (void) ;
	#endif
	
	#if(DMA_HALF_TRANSFER_CALLBACK    == DMA_HALF_TRANSFER_CALLBACK_ENABLE)
		void (*DMA_HalfTransferCallBack)     (void) ;
	#endif
	
	#if(DMA_TRANSFER_COMPLETE_CALBACK == DMA_TRANSFER_COMPLETE_CALBACK_ENABLE)
		void (*DMA_TransferCompleteCallBack) (void) ;
	#endif
	
}DMA_Config;


ErrorStatus DMA_Channel_Init(DMA_Config *Config);
void DMA_Channel_Start(DMA_Config *Config , uint32_t SourceAddress , uint32_t DestinationAddress , uint16_t DataLength);
void DMA_Channel1_SetCallBack(DMA_Config *Config);


#endif /*DMA_INTERFACE_H*/
