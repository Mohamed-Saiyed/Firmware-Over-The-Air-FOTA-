/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 24 ‎September 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/

#ifndef LEDMRX_CONFIG_H
#define LEDMRX_CONFIG_H


#define LEDMAT_MAX_LINE_LENGHT  	50

#define LEDMAT_COLS_NUM  			8

#define LEDMAT_ROWS_NUM				8

#define LEDMAT_DELAY_IN_TICK		2000

#define LEDMAT_DISP_LINE_SPEED		30
 
 /*Options:
						ACTIVE_LOW
						ACTIVE_HIGH
 */
#define LEDMAT_COL_ACTIVE				  ACTIVE_LOW

 /*Options:
						ACTIVE_LOW
						ACTIVE_HIGH
 */
#define LEDMAT_ROW_ACTIVE         ACTIVE_HIGH

 /*Options:
						LEDMAT_COL_CONTROL
						LEDMAT_ROW_CONTROL
 */
#define LEDMAT_CONTROL						LEDMAT_COL_CONTROL

 /*Options:
						LEDMAT_SYSTICK_TIMING
						LEDMAT_TIMER_TIMING
 */
#define LEDMAT_TIMING							LEDMAT_SYSTICK_TIMING


typedef struct
{
	GPIO_Typedef *GPIOx;
	
	uint8_t   LedMatPin;
	
}LedMat_Map;


static LedMat_Map LedMat_RowsMap[LEDMAT_ROWS_NUM] ={
	
	  {GPIOA,GPIO_PIN_0}  ,
	  {GPIOA,GPIO_PIN_1}  ,
	  {GPIOA,GPIO_PIN_2}  ,
	  {GPIOA,GPIO_PIN_3}  ,
	  {GPIOA,GPIO_PIN_4}  ,
	  {GPIOA,GPIO_PIN_5}  ,
	  {GPIOA,GPIO_PIN_6}  ,
	  {GPIOA,GPIO_PIN_7}  
};

static LedMat_Map LedMat_ColsMap[LEDMAT_COLS_NUM] ={
	
	  {GPIOB,GPIO_PIN_0}  ,
	  {GPIOB,GPIO_PIN_1}  ,
	  {GPIOB,GPIO_PIN_5}  ,
	  {GPIOB,GPIO_PIN_6}  ,
	  {GPIOB,GPIO_PIN_7}  ,
	  {GPIOB,GPIO_PIN_8}  ,
	  {GPIOB,GPIO_PIN_9}  ,
	  {GPIOB,GPIO_PIN_10}  
};



#endif /*LEDMRX_CONFIG_H*/
