/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 28 ‎September 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/

#ifndef IR_PRIVATE_H
#define IR_PRIVATE_H

#define IR_ADDRESS_BITS		8

#define IR_FRAME_SIZE       33

#define IR_ADDRESS			0x00

#define IR_DATA_BITS		8

void IR_CallBack(void);
void IR_ResetDataBuffer(void);
void IR_SysTickCallBack(void);

#endif /*IR_PRIVATE_H*/
