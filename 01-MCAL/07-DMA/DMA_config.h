/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 3 October 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/
#ifndef DMA_CONFIG_H
#define DMA_CONFIG_H



/*Options:
			DMA_TRANSFER_ERROR_CALLBACK_ENABLE	
			DMA_TRANSFER_ERROR_CALLBACK_DISABLE	*/	
#define DMA_TRANSFER_ERROR_CALLBACK		DMA_TRANSFER_ERROR_CALLBACK_DISABLE

/*Options:
			DMA_HALF_TRANSFER_CALLBACK_ENABLE	
			DMA_HALF_TRANSFER_CALLBACK_DISABLE		*/
#define DMA_HALF_TRANSFER_CALLBACK		DMA_HALF_TRANSFER_CALLBACK_DISABLE

/*Options:
			DMA_TRANSFER_COMPLETE_CALBACK_ENABLE	
			DMA_TRANSFER_COMPLETE_CALBACK_DISABLE	*/
#define DMA_TRANSFER_COMPLETE_CALBACK	DMA_TRANSFER_COMPLETE_CALBACK_ENABLE
	


#define DMA_ERROR_ID  	-200


#endif /*DMA_CONFIG_H*/
