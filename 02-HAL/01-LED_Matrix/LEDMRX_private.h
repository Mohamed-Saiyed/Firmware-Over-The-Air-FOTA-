/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 24 ‎September 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/

#ifndef LEDMRX_PRIVATE_H
#define LEDMRX_PRIVATE_H

#define ACTIVE_LOW		0
#define ACTIVE_HIGH		1


#define LEDMAT_COL_CONTROL				0
#define LEDMAT_ROW_CONTROL				1

#define LEDMAT_SYSTICK_TIMING			0
#define LEDMAT_TIMER_TIMING				1	


void SetRowsValues(uint8_t Data);
void SetColumn(uint8_t Column);
void DsiplayColumnForAlphabet(void);
void DsiplayColumnForLine(void);
void DisableColumns(void);

#endif /*LEDMRX_PRIVATE_H*/
