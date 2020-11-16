/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 16 October 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/
#ifndef UART_PRIVATE_H
#define UART_PRIVATE_H

#include "UART_interface.h"

#define USART_NUM_OF_CHANNELS	3

#define USART1_BASE		(0x40013800)
#define USART2_BASE		(0x40004400)
#define USART3_BASE		(0x40004800)

#define USART1			((USART_Typedef *) USART1_BASE  )
#define USART2			((USART_Typedef *) USART2_BASE  )
#define USART3	        ((USART_Typedef *) USART3_BASE  )

#define REMAP_ENABLE   			1
#define REMAP_DISABLE   		0

#define USART1_RX_PIN			GPIO_PIN_10
#define USART1_TX_PIN		    GPIO_PIN_9

#define USART1_RX_PIN_RM		GPIO_PIN_7
#define USART1_TX_PIN_RM 		GPIO_PIN_6

#define USART2_RX_PIN			GPIO_PIN_3
#define USART2_TX_PIN			GPIO_PIN_2

#define USART2_RX_PIN_RM		GPIO_PIN_6
#define USART2_TX_PIN_RM		GPIO_PIN_5

#define USART3_RX_PIN			GPIO_PIN_11
#define USART3_TX_PIN			GPIO_PIN_10
	
#define USART3_RX_PIN_RM		GPIO_PIN_9
#define USART3_TX_PIN_RM		GPIO_PIN_8

typedef struct
{
	volatile uint32_t SR     ;
	volatile uint32_t DR	 ;	
	volatile uint32_t BRR    ;
	volatile uint32_t CR1    ;
	volatile uint32_t CR2    ;
	volatile uint32_t CR3    ;
	volatile uint32_t GTPR   ;
	
}USART_Typedef;

void Reset_RX_Buffer(void);
void USART_Hndler(Uart_ChannelId Id);
static void Enable_UartNvicInterrput(Uart_ChannelId Id);

#endif /*UART_PRIVATE_H*/
