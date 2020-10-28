/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 20 October 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/
#ifndef ESP_INTERFACE_H
#define ESP_INTERFACE_H


ErrorStatus ESP_Init(void);
/*
*
*
*/
ErrorStatus ESP_NetworkConnect(uint8_t *NetworkName , uint8_t *Password);
/*
*
*
*/

ErrorStatus ESP_ServerConnect(uint8_t *IP);
/*
*
*
*/

ErrorStatus ESP_SendData(uint8_t *DataBuffer , uint8_t *DataSize);
/*
*
*
*/

void ESP_ReceiveData(uint8_t *StoredataBuffer);
/*
*
*
*/

#endif	/*ESP_INTERFACE_H*/

