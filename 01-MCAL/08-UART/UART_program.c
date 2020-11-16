/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 16 October 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/
#include "Std_types.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "RCC_Config.h"
#include "RCC_interface.h"
#include "AFIO_interface.h"
#include "NVIC_interface.h"


#include "UART_interface.h"
#include "UART_private.h"
#include "UART_config.h"
 
#if (USART_USE_DISPATCHER == 1)
	static volatile uint32_t RX_BufferCounter = 0 ;
	static volatile uint32_t TX_BufferCounter = 0 ;
	static uint8_t RX_Buffer[USART_MAX_RX_BUFFER] ;
	typedef enum
	{
		UART_RX_IDLE  			    = 0,
		UART_RX_BUSY  				= 1,
		UART_RX_RECEIVE_FRAME       = 2,
		UART_RX_FINISH   			= 3,
		UART_RX_ERROR  			    = 4
	
	}Uart_RX_Status;

	typedef enum
	{
		UART_TX_IDLE  			    = 0,
		UART_TX_SENDING_BYTE  	    = 1,
		UART_TX_SENDING_BYTE_COMP   = 2,
		UART_TX_FINISH 		    	= 3,
		UART_TX_ERROR  			    = 4
	
	}Uart_TX_Status;

	typedef struct 
	{
		uint32_t Rx_BufferSize      ;
		uint32_t Tx_BufferSize      ;
		uint8_t *Tx_Buffer          ;
		uint8_t *Rx_Buffer          ;
		Uart_RX_Status RX_State     ;
		Uart_TX_Status TX_State     ;
		uint8_t  FrameSize          ;
	
	}Uart_Control_s;

	static Uart_Control_s Uart_Control;

#endif /*USART_USE_DISPATCHER*/

static uint8_t UASRT_INIT_FLAG[USART_NUM_OF_CHANNELS] = {FALSE} ;
static void (*UART_RXCallBack[3]) (void) ;
static void (*UART_TXCallBack[3]) (void) ;
static USART_Typedef *USART[3] = {USART1 ,USART2 , USART3};


ErrorStatus UART_Init(const Uart_ConfigType * Config)
{
	int8_t State = E_OK ;
	
	if(Config == NULL)
	{
		State = USART_ERROR_ID + NULL_PTR ;
	}
	else if(UASRT_INIT_FLAG[Config->Id] == TRUE)
	{
		State = USART_ERROR_ID + MULTIPLE_INITIALIZATION ;
	}
	else
	{
		CLR_BIT(Config->USARTx->CR1 , 13 ) ;
		
		Config->USARTx->CR1 |= ((uint32_t)(Config->WordLenght) << 12) ;
		
		Config->USARTx->CR2 |= ((uint32_t)(Config->StopBits) << 12)   ;
		
		if(Config->Parity == UART_PARITY_BIT_NONE)
		{
			CLR_BIT(Config->USARTx->CR1 , 10)  ;
			CLR_BIT(Config->USARTx->CR1 , 9 )  ;
			CLR_BIT(Config->USARTx->CR1 , 8 )  ;
		}
		else
		{
			switch((uint8_t)Config->Parity)
			{
				case UART_PARITY_BIT_EVEN: 
				
					SET_BIT(Config->USARTx->CR1 , 10)  ;
					CLR_BIT(Config->USARTx->CR1 , 9 )  ;
				
				break ;
				case UART_PARITY_BIT_ODD:
					
					SET_BIT(Config->USARTx->CR1 , 10)  ;
					SET_BIT(Config->USARTx->CR1 , 9 )  ;
					
				break ;
				
				default: break ;
				
			}
		}
			
    	Uart_SetBaudRate(Config);
		
		Uart_SetPins(Config->Id);
		
		switch((uint8_t)Config->Mode)
		{
			case UART_MODE_RX: SET_BIT(Config->USARTx->CR1 , 2);	 break ;
			case UART_MODE_TX: SET_BIT(Config->USARTx->CR1 , 3);	 break ;		
			case UART_MODE_TX_RX:
			
				SET_BIT(Config->USARTx->CR1 , 2);
				SET_BIT(Config->USARTx->CR1 , 3);
				
			break;
			
			default: break ;
			
		}
			
		SET_BIT(Config->USARTx->CR1 , 13 ) ;
	
		Config->USARTx->SR =  0 ;
		
		UASRT_INIT_FLAG[Config->Id] = TRUE ;
	}
	
	return State ;
}


ErrorStatus UART_TransmitSynchronous(USART_Typedef *USARTx ,uint8_t *Buffer)
{
	int8_t State = E_OK ;
	
	if(Buffer == NULL)
	{
		State = USART_ERROR_ID + NULL_PTR ;
	}
	else
	{
		uint32_t Local_Index =  0 ;
		while(Buffer[Local_Index] != '\0')
		{
		
			USARTx->DR = Buffer[Local_Index] ;
			while(GET_BIT(USARTx->SR , 6) == 0);
			Local_Index++;
		}
	}
	
	return State ;
}

ErrorStatus UART_ReceiveSynchronous(USART_Typedef *USARTx ,uint8_t *Buffer , uint32_t BufferSize , uint32_t Timeout)
{
	int8_t State = E_OK  ;
	uint32_t TimeCounter ;
	if(Buffer == NULL)
	{
		State = USART_ERROR_ID + NULL_PTR ;
	}
	else
	{
		for(uint32_t Local_Index =  0 ; Local_Index < BufferSize ; Local_Index++)
		{
			while(GET_BIT(USARTx->SR , 5) == 0)
			{
				TimeCounter++;
				
				if(TimeCounter > Timeout)
				{
					State = E_NOK ;
					break;
				}
				else
				{
					
				}
			}
			
			if(State == E_OK )
			{
				*Buffer++ = (uint8_t)USARTx->DR;
			}
			else
			{
				
			}
			
		}
		
	}
	
	return State ;
}

void UART_EnableInterrupt(USART_Typedef *USARTx , Uart_ChannelId Id , Uart_Interrupt Int)
{
	Enable_UartNvicInterrput(Id);
	switch(Int)
	{
		case RECEIVE_INTERRUPT : SET_BIT(USARTx->CR1 , 5);		break;
		case TRANSMIT_INTERRUPT: SET_BIT(USARTx->CR1 , 6);		break;
		default:
			SET_BIT(USARTx->CR1 , 5);
		    SET_BIT(USARTx->CR1 , 6);
		break;
		
	}
}

static void Enable_UartNvicInterrput(Uart_ChannelId Id)
{
	switch(Id)
		{
			case USART1_Id: 	NVIC_EnableInterrupt(USART1_IRQn);		break;
			case USART2_Id: 	NVIC_EnableInterrupt(USART2_IRQn);		break;
			case USART3_Id: 	NVIC_EnableInterrupt(USART3_IRQn);		break;
			default:													break;
		}
	
}

void UART_SetCallBack(Uart_ChannelId Id , void (*ptr) (void) , Uart_Interrupt Int)
{
  if(ptr == NULL)
	{
		/*Do Nothing*/
	}
	else
	{
		switch(Int)
		{
			case RECEIVE_INTERRUPT : 	UART_RXCallBack[Id] = ptr ;		break;
			case TRANSMIT_INTERRUPT: 	UART_TXCallBack[Id] = ptr ;		break;
			default:													break;
		}
	
	}
}

#if(USART_USE_DISPATCHER == 1)
	void Uart_RX_Dispatcher(void)
	{
		if(UASRT_INIT_FLAG[USART1_Id] == FALSE)
		{
			
		}
		else
		{
			switch(Uart_Control.RX_State)
			{
				case UART_RX_IDLE:
					/*Do Nothing*/
				break ;

				case UART_RX_BUSY:
					if(RX_BufferCounter >=Uart_Control.Rx_BufferSize)
					{
						Uart_Control.RX_State = UART_RX_FINISH ;
					}
					else
					{
						
					}
				break ;
				case UART_RX_FINISH:
				
					for(uint32_t Local_Index = 0 ; Local_Index <Uart_Control.Rx_BufferSize  ; Local_Index++)
					{ 
						Uart_Control.Rx_Buffer[Local_Index] = RX_Buffer[Local_Index];
					}
					
					RX_BufferCounter = 0                 ;
					Reset_RX_Buffer()			         ;
					Uart_Control.RX_State = UART_RX_IDLE ;
					
				break ;
				case UART_RX_ERROR:
				
					RX_BufferCounter = 0                 ;
					Reset_RX_Buffer()			         ;
					Uart_Control.RX_State = UART_RX_IDLE ;
					
				break;
				default:
				break;
			}
		}
	}


	void Uart_TX_Dispatcher(void)
	{
		if(UASRT_INIT_FLAG[USART1_Id] == FALSE)
		{
			
		}
		else
		{
			switch(Uart_Control.TX_State)
			{
				case UART_TX_IDLE:
				
					/*Do Nothing*/
				
				break ;
				case UART_TX_SENDING_BYTE:
				
					/*Do Nothing*/
					
				break ;
				case UART_TX_SENDING_BYTE_COMP:
					/*check if the last index of the buffer*/
					/*else send increment the buffer counter and send the next byte*/
						if(TX_BufferCounter > Uart_Control.Tx_BufferSize	)
						{
							TX_BufferCounter = 0 ;
							Uart_Control.TX_State = UART_TX_FINISH ;
						}
						else
						{
							USART1->DR = Uart_Control.Tx_Buffer[TX_BufferCounter];
							TX_BufferCounter++;
							Uart_Control.TX_State = UART_TX_SENDING_BYTE ;
						}
						
				break ;
				case UART_TX_FINISH:
				
					/*Call TX CBF function*/
					CLR_BIT(USART1->CR1 , 6)    	    	   ;
					Uart_Control.TX_State = UART_TX_IDLE   ;
				break ;
				case UART_TX_ERROR:
				break ;
				default:
				break;	
				
				
			}
		}
	} 


	void USART_Hndler(Uart_ChannelId Id)
	{
	 
	  if((GET_BIT(USART[Id]->SR , 5)) != 0)
		{
			if(Uart_Control.RX_State == UART_RX_IDLE)
			{
				Uart_Control.RX_State = UART_RX_BUSY ;
			}
			else
			{
				
			}
			RX_Buffer[RX_BufferCounter] = (uint8_t)USART[Id]->DR ;
			RX_BufferCounter++;
		}
		else if((GET_BIT(USART[Id]->SR , 6)) != 0)
		{
		  if(Uart_Control.TX_State == UART_TX_SENDING_BYTE)
			{
				Uart_Control.TX_State = UART_TX_SENDING_BYTE_COMP ;
				USART[Id]->SR =  0 ;
			}
			else
			{
				
			}
		}
		else 
		{
		
		
		}

	}

	ErrorStatus UART_ReceiveAsynchronous(uint8_t *Buffer , uint32_t BufferSize)
	{
		int8_t State = E_OK ;
		
		if(Buffer == NULL)
		{
			State = USART_ERROR_ID + NULL_PTR ;
		}
		else
		{		
			if(Uart_Control.RX_State == UART_RX_IDLE)
			{ 
				Uart_Control.Rx_Buffer     = Buffer     	          ;
				Uart_Control.Rx_BufferSize = BufferSize               ;
				Uart_Control.RX_State      = UART_RX_IDLE             ; 
				SET_BIT(USART1->CR1 , 5)    		    			  ;			
			}
			else
			{
				State = E_NOK ;
			}
			
			
		}
		
		return State ;

	}

	ErrorStatus UART_TransmitAsynchronous(uint8_t *Buffer , uint32_t BufferSize)
	{
		int8_t State = E_OK ;
		
		if(Buffer == NULL)
		{
			State = USART_ERROR_ID + NULL_PTR ;
		}
		else
		{		
			if(Uart_Control.TX_State == UART_TX_IDLE)
			{ 
				Uart_Control.Tx_Buffer  = Buffer     			      ;
				Uart_Control.Tx_BufferSize = BufferSize 		      ;
				Uart_Control.TX_State   = UART_TX_SENDING_BYTE        ; 
				SET_BIT(USART1->CR1 , 6)    		    			  ;			
			}
			else
			{
				State = E_NOK ;
			}
			
			
		}
		
		return State ;

	}
	void UART_Setup(void)
	{
	
		Uart_Control.RX_State    = UART_RX_IDLE ; 
		Uart_Control.TX_State    = UART_TX_IDLE ; 
		Uart_Control.FrameSize   = 2 	    	;
	
	}
	void Reset_RX_Buffer(void)
	{
		for(uint32_t Local_Index = 0 ; Local_Index <USART_MAX_RX_BUFFER ; Local_Index++)
		{
			RX_Buffer[Local_Index] = 0 ;
		}
	}

#endif /*USART_USE_DISPATCHER*/

void USART1_IRQHandler(void)
{
	#if( USART_USE_DISPATCHER == 1)
		USART_Hndler(USART1_Id);
	#else
	if((GET_BIT(USART1->SR , 5)) != 0)
	{
		if(UART_RXCallBack[USART1_Id] == NULL)
		{
			/*Do Nothing*/
		}
		else
		{
			UART_RXCallBack[USART1_Id]() ;
		}
	}
	else if((GET_BIT(USART1->SR , 6)) != 0)
	{
	  if(UART_TXCallBack[USART1_Id] == NULL)
		{
			/*Do Nothing*/
		}
		else
		{
			UART_TXCallBack[USART1_Id]() ;
		}
	}
	else
	{
	
	}
		
	#endif
	
	
}

void USART2_IRQHandler(void)
{
#if( USART_USE_DISPATCHER == 1)
		USART_Hndler(USART2_Id);
#else
	if((GET_BIT(USART2->SR , 5)) != 0)
	{
		if(UART_RXCallBack[USART2_Id] == NULL)
		{
			/*Do Nothing*/
		}
		else
		{
			UART_RXCallBack[USART2_Id]() ;
		}
	}
	else if((GET_BIT(USART2->SR , 6)) != 0)
	{
	  if(UART_TXCallBack[USART2_Id] == NULL)
		{
			/*Do Nothing*/
		}
		else
		{
			UART_TXCallBack[USART2_Id]() ;
		}
	}
	else
	{
	
	}
#endif
	
}

void USART3_IRQHandler(void)
{
#if( USART_USE_DISPATCHER == 1)
		USART_Hndler(USART3_Id);
#else
	if((GET_BIT(USART3->SR , 5)) != 0)
	{
		if(UART_RXCallBack[USART3_Id] == NULL)
		{
			/*Do Nothing*/
		}
		else
		{
			UART_RXCallBack[USART3_Id]() ;
		}
	}
	else if((GET_BIT(USART3->SR , 6)) != 0)
	{
	  if(UART_TXCallBack[USART3_Id] == NULL)
		{
			/*Do Nothing*/
		}
		else
		{
			UART_TXCallBack[USART3_Id]() ;
		}
	}
	else
	{
	
	}
#endif
	
}


/**********************************************************************************/
void Uart_SetPins(Uart_ChannelId Id)
{
	switch(Id)
	{
		case USART1_Id:
		
		#if( USART1_PIN_REMAP == REMAP_ENABLE)
			
			RCC_EnableClock(RCC_AFIO_ID);
			RCC_EnableClock(RCC_GPIOB_ID);
			
			AFIO_Remap(USART1_REMAP , AFIO_REMAP_NONE);
			
			GPIO_InitPin(GPIOB , USART1_TX_PIN_RM , AF_OUTPUT_PP_SPEED_10MHz);
			GPIO_InitPin(GPIOB , USART1_RX_PIN_RM , GPIO_INPUT_FLOATING);
				
		#else
			RCC_EnableClock(RCC_GPIOA_ID);
			
			GPIO_InitPin(GPIOA , USART1_TX_PIN , AF_OUTPUT_PP_SPEED_10MHz);
			GPIO_InitPin(GPIOA , USART1_RX_PIN , GPIO_INPUT_FLOATING);
			
		#endif
		
		break ;
		case USART2_Id: 
		
		#if( USART2_PIN_REMAP == REMAP_ENABLE)
			
			RCC_EnableClock(RCC_AFIO_ID);
			RCC_EnableClock(RCC_GPIOD_ID);
			
			AFIO_Remap(USART2_REMAP , AFIO_REMAP_NONE);
			
			GPIO_InitPin(GPIOD , USART2_TX_PIN_RM , AF_OUTPUT_PP_SPEED_10MHz);
			GPIO_InitPin(GPIOD , USART2_RX_PIN_RM , GPIO_INPUT_FLOATING);
				
		#else
			RCC_EnableClock(RCC_GPIOA_ID);
		
			GPIO_InitPin(GPIOA , USART2_TX_PIN , AF_OUTPUT_PP_SPEED_10MHz);
			GPIO_InitPin(GPIOA , USART2_RX_PIN , GPIO_INPUT_FLOATING);
			
		#endif	
		
		break ;
		case USART3_Id: 
		
		#if( USART3_PIN_REMAP == REMAP_ENABLE)
			
			RCC_EnableClock(RCC_AFIO_ID);
			RCC_EnableClock(RCC_GPIOD_ID);	
			
			AFIO_Remap(USART2_REMAP , AFIO_REMAP_FULL);
			
			GPIO_InitPin(GPIOD , USART3_TX_PIN_RM , AF_OUTPUT_PP_SPEED_10MHz);
			GPIO_InitPin(GPIOD , USART3_RX_PIN_RM , GPIO_INPUT_FLOATING);
				
		#else
			RCC_EnableClock(RCC_GPIOB_ID);
			
			GPIO_InitPin(GPIOB , USART3_TX_PIN , AF_OUTPUT_PP_SPEED_10MHz);
			GPIO_InitPin(GPIOB , USART3_RX_PIN , GPIO_INPUT_FLOATING);
			
		#endif	
		
		break ;
		default:
		break ;
	}
}


void Uart_SetBaudRate(const Uart_ConfigType * Config)
{
	
	uint32_t BaudValue   = (RCC_SYS_CLOCK * 25) / ( Config->BaudRate *4 ) ;
	
	uint32_t Mantissa    =   BaudValue / 100;
	
	uint32_t Fraction    = ((BaudValue - Mantissa * 100) * 16 + 50 ) /100;
	
	Config->USARTx->BRR  = ((Mantissa) << 4 ) + Fraction ;
		
}


