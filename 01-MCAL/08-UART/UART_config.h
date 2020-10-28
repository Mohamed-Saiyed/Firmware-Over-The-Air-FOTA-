/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 16 October 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/

#ifndef UART_CONFIG_H
#define UART_CONFIG_H

#define USART1_PIN_REMAP 	REMAP_ENABLE
#define USART2_PIN_REMAP 	REMAP_DISABLE
#define USART3_PIN_REMAP 	REMAP_DISABLE

#define USART_USE_DISPATCHER   0

#define USART_FRAME_CHECK      0

#define USART_NUM_OF_CHANNELS  1	 

#define USART_MAX_RX_BUFFER   100

#define USART_ERROR_ID		  -50


#endif /*UART_CONFIG_H*/
