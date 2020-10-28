/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 16 October 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/

#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H



typedef enum
{
	UART_WORD_LENGHT_8BIT = 0 ,
	UART_WORD_LENGHT_9BIT = 1
	
}Uart_WordLenght;

typedef enum
{
	UART_STOP_BIT_1BIT      = 0 ,
	UART_STOP_BIT_HALFBIT   = 1 ,
	UART_STOP_BIT_2BITS     = 2 ,
	UART_STOP_BIT_1_HALFBIT = 3 
	
}Uart_StopBits;

typedef enum 
{
	UART_PARITY_BIT_EVEN	= 0 ,
	UART_PARITY_BIT_ODD		= 1 ,
	UART_PARITY_BIT_NONE 	= 2
	
}Uart_ParityBit;

typedef enum
{
	USART1_Id = 0 ,
	USART2_Id = 1 ,
	USART3_Id = 2
	
}Uart_ChannelId;
#include "UART_private.h"
typedef enum
{
	UART_MODE_RX	 = 0 ,
	UART_MODE_TX     = 1 ,
	UART_MODE_TX_RX  = 2
	
}Uart_Mode;

typedef enum
{
	RECEIVE_INTERRUPT  = 0 ,	
	TRANSMIT_INTERRUPT = 1
	
}Uart_Interrupt;


typedef struct
{
	USART_Typedef	 *USARTx	; 
	
	Uart_ChannelId   Id		    ;
	
	Uart_WordLenght  WordLenght ;
					 
	Uart_StopBits    StopBits   ;
			
    Uart_Mode	   	 Mode		;
				
	uint32_t		 BaudRate   ;
					 
	Uart_ParityBit   Parity	    ;
		
}Uart_ConfigType;


void UART_EnableInterrupt(USART_Typedef *USARTx , Uart_Interrupt Int);
void Uart_SetBaudRate(const Uart_ConfigType * Config);
ErrorStatus UART_Init(const Uart_ConfigType * Config);
void Uart_SetPins(Uart_ChannelId Id);
void Uart_RX_Dispatcher(void);
void Uart_TX_Dispatcher(void);
void UART_Setup(void);
ErrorStatus UART_TransmitAsynchronous(uint8_t *Buffer , uint32_t BufferSize);
ErrorStatus UART_TransmitSynchronous(USART_Typedef *USARTx ,uint8_t *Buffer);
ErrorStatus UART_ReceiveAsynchronous(uint8_t *Buffer , uint32_t BufferSize) ;
ErrorStatus UART_ReceiveSynchronous(USART_Typedef *USARTx ,uint8_t *Buffer , uint32_t BufferSize , uint32_t Timeout);
void UART_SetCallBack(Uart_ChannelId Id , void (*ptr) (void) , Uart_Interrupt Int);
#endif /*UART_INTERFACE_H*/

