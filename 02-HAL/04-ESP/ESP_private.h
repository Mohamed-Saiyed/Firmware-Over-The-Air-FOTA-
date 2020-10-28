/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 20 October 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/
#ifndef ESP_PRIVATE_H	
#define ESP_PRIVATE_H

uint8_t Find_string(uint8_t *string , uint8_t *string_nedded);
void Reset_Buffer(void);
void ESP_CallBack(void);
void UartEsp_init(void);

#endif  /*ESP_PRIVATE_H*/

