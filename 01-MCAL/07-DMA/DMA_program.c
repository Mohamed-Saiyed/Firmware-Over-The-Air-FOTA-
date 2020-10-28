/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 3 October 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/

#include "Std_types.h"
#include "BIT_MATH.h"


#include "DMA_interface.h"
#include "DMA_Private.h"
#include "DMA_cnofig.h"

void SetDMADireciton(DMA_Config *Config);

static volatile uint8_t DMA_Channel1_InitFlag = FALSE ;
static volatile uint8_t DMA_Channel2_InitFlag = FALSE ;
static volatile uint8_t DMA_Channel3_InitFlag = FALSE ;
static volatile uint8_t DMA_Channel4_InitFlag = FALSE ;
static volatile uint8_t DMA_Channel5_InitFlag = FALSE ;
static volatile uint8_t DMA_Channel6_InitFlag = FALSE ;
static volatile uint8_t DMA_Channel7_InitFlag = FALSE ;


static void (*DMA1_Channel1_HalfTransfereCallBck)     (void) ;
static void (*DMA1_Channel2_HalfTransfereCallBck)     (void) ;
static void (*DMA1_Channel3_HalfTransfereCallBck)     (void) ;
static void (*DMA1_Channel4_HalfTransfereCallBck)     (void) ;
static void (*DMA1_Channel5_HalfTransfereCallBck)     (void) ;
static void (*DMA1_Channel6_HalfTransfereCallBck)     (void) ;
static void (*DMA1_Channel7_HalfTransfereCallBck)     (void) ;
												      
static void (*DMA1_Channel1_TransferErrorCallBck)     (void) ;
static void (*DMA1_Channel2_TransferErrorCallBck)     (void) ;
static void (*DMA1_Channel3_TransferErrorCallBck)     (void) ;
static void (*DMA1_Channel4_TransferErrorCallBck)     (void) ;
static void (*DMA1_Channel5_TransferErrorCallBck)     (void) ;
static void (*DMA1_Channel6_TransferErrorCallBck)     (void) ;
static void (*DMA1_Channel7_TransferErrorCallBck)     (void) ;

static void (*DMA1_Channel1_TransfereCompleteCallBck) (void) ;
static void (*DMA1_Channel2_TransfereCompleteCallBck) (void) ;
static void (*DMA1_Channel3_TransfereCompleteCallBck) (void) ;
static void (*DMA1_Channel4_TransfereCompleteCallBck) (void) ;
static void (*DMA1_Channel5_TransfereCompleteCallBck) (void) ;
static void (*DMA1_Channel6_TransfereCompleteCallBck) (void) ;
static void (*DMA1_Channel7_TransfereCompleteCallBck) (void) ;


ErrorStatus DMA_Channel_Init(DMA_Config *Config)
{
   /*temp variable to store function status */
   ErrorStatus Status = E_OK ;
	/*check fot null pointers*/
	if((Config == NULL) || (Config->DMA_Channel == NULL))
	{
		Status = DMA_ERROR_ID + NULL_PTR	;
	}
	/*check for multiple initialization*/
	else if(CheckInitFlag(Config->DMA_Channel) == TRUE)
	{
		Status = DMA_ERROR_ID + MULTIPLE_INITIALIZATION ;
	}
	else
	{
		/*make sure that dma is off before any initialization*/
		CLR_BIT(Config->DMA_Channel->CCR , 0 )                              ;
		/*Set DMA mode if its normal or circular*/
		Config->DMA_Channel->CCR |= ((uint32_t)Config->Mode                << 	5  );
		/*set DMA channel Priority*/
		Config->DMA_Channel->CCR |= ((uint32_t)Config->Priority            << 	12 );
		/*Set DMA memory element size */
		Config->DMA_Channel->CCR |= ((uint32_t)Config->MemoryDataSize      << 	10 );
		/*set DMA Peripheral elment size*/
		Config->DMA_Channel->CCR |= ((uint32_t)Config->PeripheralDataSize  << 	8  );
		/*do memory address incerment initialization*/
		Config->DMA_Channel->CCR |= ((uint32_t)Config->MemoryIncrement     << 	7  );
		/*do Peripheral address incerment initialization*/
		Config->DMA_Channel->CCR |= ((uint32_t)Config->PeripheralIncrement << 	6  );
		/*Choose DMA Data Direction due to initialization*/
		SetDMADireciton(Config)                                            ;
		/*Set correpoinding DMA channel init flag*/
		SetInitFlag(Config->DMA_Channel);
	}
	
	return Status ;
}

void DMA_Channel_Start(DMA_Config *Config , uint32_t SourceAddress , uint32_t DestinationAddress , uint16_t DataLength)
{
	/*Do Nothing If the DMA channel is not initialized*/
	if(CheckInitFlag(Config->DMA_Channel) == FALSE)
	{
		/*Do Nothing*/
	}
	else
	{
		/*configure DMA Lenght of the data */
		Config->DMA_Channel->CNDTR = DataLength ;
		
		if(Config->Direction == DMA_MEMORY_TO_PERIPHERAL)
		{
			Config->DMA_Channel->CMAR  = SourceAddress ;
			
			Config->DMA_Channel->CPAR  = DestinationAddress ;
		}
		else
		{
		   Config->DMA_Channel->CMAR  = DestinationAddress ;
		   
		   Config->DMA_Channel->CPAR  = SourceAddress ;
			
		}
		/*Enable DMA channel after finishing initialization*/
		SET_BIT(Config->DMA_Channel->CCR , 0) ;
		
	}
}

void DMA_Channel_Start_IT(DMA_Config *Config , uint32_t SourceAddress , uint32_t DestinationAddress , uint16_t DataLength)
{
	/*Do Nothing If the DMA channel is not initialized*/
	if(CheckInitFlag(Config->DMA_Channel) == FALSE)
	{
		/*Do Nothing*/
	}
	else
	{
		Config->DMA_Channel->CNDTR = DataLength ;
		
		if(Config->Direction == DMA_MEMORY_TO_PERIPHERAL)
		{
			Config->DMA_Channel->CMAR  = SourceAddress ;
			
			Config->DMA_Channel->CPAR  = DestinationAddress ;
		}
		else
		{
		   Config->DMA_Channel->CMAR  = DestinationAddress ;
		   
		   Config->DMA_Channel->CPAR  = SourceAddress ;
			
		}
		/*Enable DMA channel after finishing initialization*/
		SET_BIT(Config->DMA_Channel->CCR , 0) ;
		
	#if(DMA_TRANSFER_ERROR_CALLBACK	  == DMA_TRANSFER_ERROR_CALLBACK_ENABLE)
		/*Enable DMA Transfere error interrupt*/
		SET_BIT(Config->DMA_Channel->CCR , 3) ;
	#endif
	
	#if(DMA_HALF_TRANSFER_CALLBACK    == DMA_HALF_TRANSFER_CALLBACK_ENABLE)
		/*Enable DMA Half Transfere interrupt*/
		SET_BIT(Config->DMA_Channel->CCR , 2) ;	
	#endif
	
	#if(DMA_TRANSFER_COMPLETE_CALBACK == DMA_TRANSFER_COMPLETE_CALBACK_ENABLE)
		/*Enable DMA Transfere Complete interrupt*/
		SET_BIT(Config->DMA_Channel->CCR , 1) ;	
	#endif
	
		
		
	}
}

/*private function to set DMA channel init flag*/
void SetInitFlag(DMA_Channel_Typedef *DMA_Channel)
{

		if     (DMA_Channel == DMA1_CHANNEL1)       DMA_Channel1_InitFlag = TRUE ; 
		else if(DMA_Channel == DMA1_CHANNEL2) 	    DMA_Channel2_InitFlag = TRUE ;  
		else if(DMA_Channel == DMA1_CHANNEL3)		DMA_Channel3_InitFlag = TRUE ; 
		else if(DMA_Channel == DMA1_CHANNEL4)		DMA_Channel4_InitFlag = TRUE ;
		else if(DMA_Channel == DMA1_CHANNEL5)		DMA_Channel5_InitFlag = TRUE ;
		else if(DMA_Channel == DMA1_CHANNEL6)		DMA_Channel6_InitFlag = TRUE ;
		else if(DMA_Channel == DMA1_CHANNEL7)		DMA_Channel7_InitFlag = TRUE ;
	    else{}
	
}

/*private function to return the state of DMA channel init flag*/
uint8_t CheckInitFlag(DMA_Channel_Typedef *DMA_Channel)
{
	uint8_t DMA_InitFlagStatus = FALSE ;

		if     (DMA_Channel == DMA1_CHANNEL1) 	DMA_InitFlagStatus = DMA_Channel1_InitFlag ;
		else if(DMA_Channel == DMA1_CHANNEL2) 	DMA_InitFlagStatus = DMA_Channel2_InitFlag ;
		else if(DMA_Channel == DMA1_CHANNEL3) 	DMA_InitFlagStatus = DMA_Channel3_InitFlag ;
		else if(DMA_Channel == DMA1_CHANNEL4) 	DMA_InitFlagStatus = DMA_Channel4_InitFlag ;
		else if(DMA_Channel == DMA1_CHANNEL5) 	DMA_InitFlagStatus = DMA_Channel5_InitFlag ;
		else if(DMA_Channel == DMA1_CHANNEL6) 	DMA_InitFlagStatus = DMA_Channel6_InitFlag ;
		else if(DMA_Channel == DMA1_CHANNEL7) 	DMA_InitFlagStatus = DMA_Channel7_InitFlag ;
		else{}								     
	
	
	return DMA_InitFlagStatus ;
}


void SetDMADireciton(DMA_Config *Config)
{
	switch(Config->Direction)
	{
		case DMA_MEMORY_TO_MEMORY:     SET_BIT(Config->DMA_Channel->CCR , 14) ; break;     
		case DMA_MEMORY_TO_PERIPHERAL: SET_BIT(Config->DMA_Channel->CCR ,  4) ; break;
		case DMA_PERIPHERAL_TO_MEMORY: CLR_BIT(Config->DMA_Channel->CCR , 14) ; break;
		default:															   break;
	}
	
}

void DMA_Channel1_SetCallBack(DMA_Config *Config)
{
	#if(DMA_TRANSFER_ERROR_CALLBACK	  == DMA_TRANSFER_ERROR_CALLBACK_ENABLE)
		if(Config->DMA_TransferErrorCallBack != NULL)
		{
			DMA1_Channel1_TransferErrorCallBck = Config->DMA_TransferErrorCallBack ;
		}
		else
		{
		
		}
		
	#endif
	
	#if(DMA_HALF_TRANSFER_CALLBACK    == DMA_HALF_TRANSFER_CALLBACK_ENABLE)
		if(Config->DMA_HalfTransferCallBack != NULL)
		{
			DMA1_Channel1_HalfTransfereCallBck = Config->DMA_HalfTransferCallBack ;
		}
		else
		{
		
		}
		
	#endif
	
	#if(DMA_TRANSFER_COMPLETE_CALBACK == DMA_TRANSFER_COMPLETE_CALBACK_ENABLE)
		if(Config->DMA_TransferCompleteCallBack != NULL)
		{
			DMA1_Channel1_TransfereCompleteCallBck = Config->DMA_TransferCompleteCallBack ;
		}
		else
		{
		
		}
		
	#endif
	
	
}

void DMA_Channel2_SetCallBack(DMA_Config *Config)
{
	#if(DMA_TRANSFER_ERROR_CALLBACK	  == DMA_TRANSFER_ERROR_CALLBACK_ENABLE)
		if(Config->DMA_TransferErrorCallBack != NULL)
		{
			DMA1_Channel2_TransferErrorCallBck = Config->DMA_TransferErrorCallBack ;
		}
		else
		{
		
		}
		
	#endif
	
	#if(DMA_HALF_TRANSFER_CALLBACK    == DMA_HALF_TRANSFER_CALLBACK_ENABLE)
		if(Config->DMA_HalfTransferCallBack != NULL)
		{
			DMA1_Channel2_HalfTransfereCallBck = Config->DMA_HalfTransferCallBack ;
		}
		else
		{
		
		}
		
	#endif
	
	#if(DMA_TRANSFER_COMPLETE_CALBACK == DMA_TRANSFER_COMPLETE_CALBACK_ENABLE)
		if(Config->DMA_TransferCompleteCallBack != NULL)
		{
			DMA1_Channel2_TransfereCompleteCallBck = Config->DMA_TransferCompleteCallBack ;
		}
		else
		{
		
		}
		
	#endif
	
	
}

void DMA_Channel3_SetCallBack(DMA_Config *Config)
{
	#if(DMA_TRANSFER_ERROR_CALLBACK	  == DMA_TRANSFER_ERROR_CALLBACK_ENABLE)
		if(Config->DMA_TransferErrorCallBack != NULL)
		{
			DMA1_Channel3_TransferErrorCallBck = Config->DMA_TransferErrorCallBack ;
		}
		else
		{
		
		}
		
	#endif
	
	#if(DMA_HALF_TRANSFER_CALLBACK    == DMA_HALF_TRANSFER_CALLBACK_ENABLE)
		if(Config->DMA_HalfTransferCallBack != NULL)
		{
			DMA1_Channel3_HalfTransfereCallBck = Config->DMA_HalfTransferCallBack ;
		}
		else
		{
		
		}
		
	#endif
	
	#if(DMA_TRANSFER_COMPLETE_CALBACK == DMA_TRANSFER_COMPLETE_CALBACK_ENABLE)
		if(Config->DMA_TransferCompleteCallBack != NULL)
		{
			DMA1_Channel3_TransfereCompleteCallBck = Config->DMA_TransferCompleteCallBack ;
		}
		else
		{
		
		}
		
	#endif
	
	
}

void DMA_Channel4_SetCallBack(DMA_Config *Config)
{
	#if(DMA_TRANSFER_ERROR_CALLBACK	  == DMA_TRANSFER_ERROR_CALLBACK_ENABLE)
		if(Config->DMA_TransferErrorCallBack != NULL)
		{
			DMA1_Channel4_TransferErrorCallBck = Config->DMA_TransferErrorCallBack ;
		}
		else
		{
		
		}
		
	#endif
	
	#if(DMA_HALF_TRANSFER_CALLBACK    == DMA_HALF_TRANSFER_CALLBACK_ENABLE)
		if(Config->DMA_HalfTransferCallBack != NULL)
		{
			DMA1_Channel4_HalfTransfereCallBck = Config->DMA_HalfTransferCallBack ;
		}
		else
		{
		
		}
		
	#endif
	
	#if(DMA_TRANSFER_COMPLETE_CALBACK == DMA_TRANSFER_COMPLETE_CALBACK_ENABLE)
		if(Config->DMA_TransferCompleteCallBack != NULL)
		{
			DMA1_Channel4_TransfereCompleteCallBck = Config->DMA_TransferCompleteCallBack ;
		}
		else
		{
		
		}
		
	#endif
	
	
}

void DMA_Channel5_SetCallBack(DMA_Config *Config)
{
	#if(DMA_TRANSFER_ERROR_CALLBACK	  == DMA_TRANSFER_ERROR_CALLBACK_ENABLE)
		if(Config->DMA_TransferErrorCallBack != NULL)
		{
			DMA1_Channel5_TransferErrorCallBck = Config->DMA_TransferErrorCallBack ;
		}
		else
		{
		
		}
		
	#endif
	
	#if(DMA_HALF_TRANSFER_CALLBACK    == DMA_HALF_TRANSFER_CALLBACK_ENABLE)
		if(Config->DMA_HalfTransferCallBack != NULL)
		{
			DMA1_Channel5_HalfTransfereCallBck = Config->DMA_HalfTransferCallBack ;
		}
		else
		{
		
		}
		
	#endif
	
	#if(DMA_TRANSFER_COMPLETE_CALBACK == DMA_TRANSFER_COMPLETE_CALBACK_ENABLE)
		if(Config->DMA_TransferCompleteCallBack != NULL)
		{
			DMA1_Channel5_TransfereCompleteCallBck = Config->DMA_TransferCompleteCallBack ;
		}
		else
		{
		
		}
		
	#endif
	
	
}

void DMA_Channel6_SetCallBack(DMA_Config *Config)
{
	#if(DMA_TRANSFER_ERROR_CALLBACK	  == DMA_TRANSFER_ERROR_CALLBACK_ENABLE)
		if(Config->DMA_TransferErrorCallBack != NULL)
		{
			DMA1_Channel6_TransferErrorCallBck = Config->DMA_TransferErrorCallBack ;
		}
		else
		{
		
		}
		
	#endif
	
	#if(DMA_HALF_TRANSFER_CALLBACK    == DMA_HALF_TRANSFER_CALLBACK_ENABLE)
		if(Config->DMA_HalfTransferCallBack != NULL)
		{
			DMA1_Channel6_HalfTransfereCallBck = Config->DMA_HalfTransferCallBack ;
		}
		else
		{
		
		}
		
	#endif
	
	#if(DMA_TRANSFER_COMPLETE_CALBACK == DMA_TRANSFER_COMPLETE_CALBACK_ENABLE)
		if(Config->DMA_TransferCompleteCallBack != NULL)
		{
			DMA1_Channel6_TransfereCompleteCallBck = Config->DMA_TransferCompleteCallBack ;
		}
		else
		{
		
		}
		
	#endif
	
	
}

void DMA_Channel7_SetCallBack(DMA_Config *Config)
{
	#if(DMA_TRANSFER_ERROR_CALLBACK	  == DMA_TRANSFER_ERROR_CALLBACK_ENABLE)
		if(Config->DMA_TransferErrorCallBack != NULL)
		{
			DMA1_Channel7_TransferErrorCallBck = Config->DMA_TransferErrorCallBack ;
		}
		else
		{
		
		}
		
	#endif
	
	#if(DMA_HALF_TRANSFER_CALLBACK    == DMA_HALF_TRANSFER_CALLBACK_ENABLE)
		if(Config->DMA_HalfTransferCallBack != NULL)
		{
			DMA1_Channel7_HalfTransfereCallBck = Config->DMA_HalfTransferCallBack ;
		}
		else
		{
		
		}
		
	#endif
	
	#if(DMA_TRANSFER_COMPLETE_CALBACK == DMA_TRANSFER_COMPLETE_CALBACK_ENABLE)
		if(Config->DMA_TransferCompleteCallBack != NULL)
		{
			DMA1_Channel7_TransfereCompleteCallBck = Config->DMA_TransferCompleteCallBack ;
		}
		else
		{
		
		}
		
	#endif
	
	
}

void DMA1_Channel1_IRQHandler(void)
{
	/*Check for transfere complete interrupt flag*/
	if(BIT_IS_SET(DMA1->ISR , 1) != 0)
	{
		/*clear the transfere complete interrupt flag*/
		DMA1->IFCR = ( 1 << 1 );
		/*check if the transfer complete call back doesn't point to NULL*/
		if(DMA1_Channel1_TransfereCompleteCallBck != NULL)
		{
			/*Call the call back function*/
			DMA1_Channel1_TransfereCompleteCallBck();
		}
		else
		{
			/*Do Nothing*/
		}
	}
	/*Check for half transfere interruptflag*/
	else if(BIT_IS_SET(DMA1->ISR , 2) !=0)
	{
		/*clear the half transfere interrupt flag*/
		DMA1->IFCR = ( 1 << 2 ) ;
		/*check if the half transfer call back doesn't point to NULL*/
		if(DMA1_Channel1_HalfTransfereCallBck != NULL)
		{
			DMA1_Channel1_HalfTransfereCallBck();
		}
		else
		{
			/*Do Nothing*/
		}
	}
    /*Check for transfere error interruptflag*/	
	else if(BIT_IS_SET(DMA1->ISR , 3) !=0)
	{
		/*clear the transfere error interrupt flag*/
		DMA1->IFCR = ( 1 << 3 );
		/*check if the half transfer call back doesn't point to NULL*/
		if(DMA1_Channel1_TransferErrorCallBck != NULL)
		{
			DMA1_Channel1_TransferErrorCallBck();
		}
		else
		{
			/*Do Nothing*/
		}
	}
	else
	{
		/*Do Nothing*/
	}
	
}	

void DMA1_Channel2_IRQHandler(void)
{
	/*Check for transfere complete interrupt flag*/
	if(BIT_IS_SET(DMA1->ISR , 5) != 0)
	{
		/*clear the transfere complete interrupt flag*/
		DMA1->IFCR = ( 1 << 5 );
		/*check if the transfer complete call back doesn't point to NULL*/
		if(DMA1_Channel2_TransfereCompleteCallBck != NULL)
		{
			/*Call the call back function*/
			DMA1_Channel2_TransfereCompleteCallBck();
		}
		else
		{
			/*Do Nothing*/
		}
	}
	/*Check for half transfere interruptflag*/
	else if(BIT_IS_SET(DMA1->ISR , 6) !=0)
	{
		/*clear the half transfere interrupt flag*/
		DMA1->IFCR = ( 1 << 6 ) ;
		/*check if the half transfer call back doesn't point to NULL*/
		if(DMA1_Channel2_HalfTransfereCallBck != NULL)
		{
			DMA1_Channel2_HalfTransfereCallBck();
		}
		else
		{
			/*Do Nothing*/
		}
	}
    /*Check for transfere error interruptflag*/	
	else if(BIT_IS_SET(DMA1->ISR , 7) !=0)
	{
		/*clear the transfere error interrupt flag*/
		DMA1->IFCR = ( 1 << 7 );
		/*check if the half transfer call back doesn't point to NULL*/
		if(DMA1_Channel2_TransferErrorCallBck != NULL)
		{
			DMA1_Channel2_TransferErrorCallBck();
		}
		else
		{
			/*Do Nothing*/
		}
	}
	else
	{
		/*Do Nothing*/
	}
}
void DMA1_Channel3_IRQHandler(void)
{
	/*Check for transfere complete interrupt flag*/
	if(BIT_IS_SET(DMA1->ISR , 9) != 0)
	{
		/*clear the transfere complete interrupt flag*/
		DMA1->IFCR = ( 1 < 9 );
		/*check if the transfer complete call back doesn't point to NULL*/
		if(DMA1_Channel3_TransfereCompleteCallBck != NULL)
		{
			/*Call the call back function*/
			DMA1_Channel3_TransfereCompleteCallBck();
		}
		else
		{
			/*Do Nothing*/
		}
	}
	/*Check for half transfere interruptflag*/
	else if(BIT_IS_SET(DMA1->ISR , 10) !=0)
	{
		/*clear the half transfere interrupt flag*/
		DMA1->IFCR = ( 1 << 10 ) ;
		/*check if the half transfer call back doesn't point to NULL*/
		if(DMA1_Channel3_HalfTransfereCallBck != NULL)
		{
			DMA1_Channel3_HalfTransfereCallBck();
		}
		else
		{
			/*Do Nothing*/
		}
	}
    /*Check for transfere error interruptflag*/	
	else if(BIT_IS_SET(DMA1->ISR , 11) !=0)
	{
		/*clear the transfere error interrupt flag*/
		DMA1->IFCR = ( 1 << 11 );
		/*check if the half transfer call back doesn't point to NULL*/
		if(DMA1_Channel3_TransferErrorCallBck != NULL)
		{
			DMA1_Channel3_TransferErrorCallBck();
		}
		else
		{
			/*Do Nothing*/
		}
	}
	else
	{
		/*Do Nothing*/
	}
}
void DMA1_Channel4_IRQHandler(void)
{
	/*Check for transfere complete interrupt flag*/
	if(BIT_IS_SET(DMA1->ISR , 13) != 0)
	{
		/*clear the transfere complete interrupt flag*/
		DMA1->IFCR = ( 1 << 13 );
		/*check if the transfer complete call back doesn't point to NULL*/
		if(DMA1_Channel4_TransfereCompleteCallBck != NULL)
		{
			/*Call the call back function*/
			DMA1_Channel4_TransfereCompleteCallBck();
		}
		else
		{
			/*Do Nothing*/
		}
	}
	/*Check for half transfere interruptflag*/
	else if(BIT_IS_SET(DMA1->ISR , 14) !=0)
	{
		/*clear the half transfere interrupt flag*/
		DMA1->IFCR = ( 1 << 14 ) ;
		/*check if the half transfer call back doesn't point to NULL*/
		if(DMA1_Channel4_HalfTransfereCallBck != NULL)
		{
			DMA1_Channel4_HalfTransfereCallBck();
		}
		else
		{
			/*Do Nothing*/
		}
	}
    /*Check for transfere error interruptflag*/	
	else if(BIT_IS_SET(DMA1->ISR , 15) !=0)
	{
		/*clear the transfere error interrupt flag*/
		DMA1->IFCR = ( 1 << 15 );
		/*check if the half transfer call back doesn't point to NULL*/
		if(DMA1_Channel4_TransferErrorCallBck != NULL)
		{
			DMA1_Channel4_TransferErrorCallBck();
		}
		else
		{
			/*Do Nothing*/
		}
	}
	else
	{
		/*Do Nothing*/
	}
}

void DMA1_Channel5_IRQHandler(void)
{
		/*Check for transfere complete interrupt flag*/
	if(BIT_IS_SET(DMA1->ISR , 17) != 0)
	{
		/*clear the transfere complete interrupt flag*/
		DMA1->IFCR = ( 1 << 17 );
		/*check if the transfer complete call back doesn't point to NULL*/
		if(DMA1_Channel5_TransfereCompleteCallBck != NULL)
		{
			/*Call the call back function*/
			DMA1_Channel5_TransfereCompleteCallBck();
		}
		else
		{
			/*Do Nothing*/
		}
	}
	/*Check for half transfere interruptflag*/
	else if(BIT_IS_SET(DMA1->ISR , 18) !=0)
	{
		/*clear the half transfere interrupt flag*/
		DMA1->IFCR = ( 1 <<	18 ) ;
		/*check if the half transfer call back doesn't point to NULL*/
		if(DMA1_Channel5_HalfTransfereCallBck != NULL)
		{
			DMA1_Channel5_HalfTransfereCallBck();
		}
		else
		{
			/*Do Nothing*/
		}
	}
    /*Check for transfere error interruptflag*/	
	else if(BIT_IS_SET(DMA1->ISR , 19) !=0)
	{
		/*clear the transfere error interrupt flag*/
		DMA1->IFCR = ( 1 << 19 );
		/*check if the half transfer call back doesn't point to NULL*/
		if(DMA1_Channel5_TransferErrorCallBck != NULL)
		{
			DMA1_Channel5_TransferErrorCallBck();
		}
		else
		{
			/*Do Nothing*/
		}
	}
	else
	{
		/*Do Nothing*/
	}
}
void DMA1_Channel6_IRQHandler(void)
{
	/*Check for transfere complete interrupt flag*/
	if(BIT_IS_SET(DMA1->ISR , 21) != 0)
	{
		/*clear the transfere complete interrupt flag*/
		DMA1->IFCR = ( 1 << 21 );
		/*check if the transfer complete call back doesn't point to NULL*/
		if(DMA1_Channel6_TransfereCompleteCallBck != NULL)
		{
			/*Call the call back function*/
			DMA1_Channel6_TransfereCompleteCallBck();
		}
		else
		{
			/*Do Nothing*/
		}
	}
	/*Check for half transfere interruptflag*/
	else if(BIT_IS_SET(DMA1->ISR , 22) !=0)
	{
		/*clear the half transfere interrupt flag*/
		DMA1->IFCR = ( 1 << 22 ) ;
		/*check if the half transfer call back doesn't point to NULL*/
		if(DMA1_Channel6_HalfTransfereCallBck != NULL)
		{
			DMA1_Channel6_HalfTransfereCallBck();
		}
		else
		{
			/*Do Nothing*/
		}
	}
    /*Check for transfere error interruptflag*/	
	else if(BIT_IS_SET(DMA1->ISR , 23) !=0)
	{
		/*clear the transfere error interrupt flag*/
		DMA1->IFCR = ( 1 << 23 );
		/*check if the half transfer call back doesn't point to NULL*/
		if(DMA1_Channel6_TransferErrorCallBck != NULL)
		{
			DMA1_Channel6_TransferErrorCallBck();
		}
		else
		{
			/*Do Nothing*/
		}
	}
	else
	{
		/*Do Nothing*/
	}	
}
void DMA1_Channel7_IRQHandler(void)
{
	/*Check for transfere complete interrupt flag*/
	if(BIT_IS_SET(DMA1->ISR , 25) != 0)
	{
		/*clear the transfere complete interrupt flag*/
		DMA1->IFCR = ( 1 << 25 );
		/*check if the transfer complete call back doesn't point to NULL*/
		if(DMA1_Channel7_TransfereCompleteCallBck != NULL)
		{
			/*Call the call back function*/
			DMA1_Channel7_TransfereCompleteCallBck();
		}
		else
		{
			/*Do Nothing*/
		}
	}
	/*Check for half transfere interruptflag*/
	else if(BIT_IS_SET(DMA1->ISR , 26) !=0)
	{
		/*clear the half transfere interrupt flag*/
		DMA1->IFCR = ( 1 << 26 ) ;
		/*check if the half transfer call back doesn't point to NULL*/
		if(DMA1_Channel7_HalfTransfereCallBck != NULL)
		{
			DMA1_Channel7_HalfTransfereCallBck();
		}
		else
		{
			/*Do Nothing*/
		}
	}
    /*Check for transfere error interruptflag*/	
	else if(BIT_IS_SET(DMA1->ISR , 27) !=0)
	{
		/*clear the transfere error interrupt flag*/
		DMA1->IFCR = ( 1 << 27 );
		/*check if the half transfer call back doesn't point to NULL*/
		if(DMA1_Channel7_TransferErrorCallBck != NULL)
		{
			DMA1_Channel7_TransferErrorCallBck();
		}
		else
		{
			/*Do Nothing*/
		}
	}
	else
	{
		/*Do Nothing*/
	}
}
