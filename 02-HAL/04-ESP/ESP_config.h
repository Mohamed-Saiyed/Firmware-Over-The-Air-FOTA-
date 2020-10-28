/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 20 October 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/
#ifndef  ESP_CONFIG_H
#define  ESP_CONFIG_H

/*Options:
		 USART1
		 USART2
		 USART3
*/
#define ESP_USART_CHANNEL  		USART1

/*Options:
		 USART1_Id
		 USART2_Id
		 USART3_Id
*/
#define ESP_USART_CHANNEL_ID	USART1_Id

/*This pramter is dependant on the sys clock*/
#define ESP_MAX_RX_TIMEOUT		60000

#define ESP_MAX_RX_BUFFER_SIZE  1100

#define ESP_BAUD_RATE			115200

#define ESP_MAX_TIME_COUNT		4

#endif	 /*ESP_CONFIG_H*/

