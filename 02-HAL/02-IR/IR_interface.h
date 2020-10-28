/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 28 ‎September 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/

#ifndef IR_INTERFACE_H
#define IR_INTERFACE_H



typedef struct
{
	GPIO_Typedef  *GPIOx				;
	DIO_Pin_t     IR_ReceiverOutputPin  ;
	uint8_t		  *Data 				;
	void 		  (*IR_CBF)(uint8_t status)		;
}IR_Config;

ErrorStatus IR_init(IR_Config *Config);
/*
*
*
*
*/

void IR_Dispatcher(void);
/*
*
*
*
*/

#endif /*IR_INTERFACE_H*/
