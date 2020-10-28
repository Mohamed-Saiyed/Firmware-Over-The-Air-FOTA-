/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 24 ‎September 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/

#ifndef LEDMRX_INTERFACE_H
#define LEDMRX_INTERFACE_H

ErrorStatus LedMatrix_Init(void);
/*
*
*
*
*/

ErrorStatus LedMatrix_Display(uint8_t *Data);
/*
*
*
*
*/
ErrorStatus LedMatrix_DisplayLine(uint8_t *Data , uint8_t NumOfColumns);
/*
*
*
*
*/

#endif /*LEDMRX_INTERFACE_H*/
