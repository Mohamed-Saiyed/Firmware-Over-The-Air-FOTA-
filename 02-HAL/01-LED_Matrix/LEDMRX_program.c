/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 24 ‎September 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/

#include "Std_types.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "SysTick_interface.h"

#include "LEDMRX_interface.h"
#include "LEDMRX_private.h"
#include "LEDMRX_config.h"

static volatile uint8_t LEDMAT_Init_Flag = FALSE ;

static volatile uint8_t CurrentDataIndex = 0 ;

static volatile uint8_t CurrentColumns   = 0 ;

static volatile uint8_t LineIndex = 0 ;

static volatile uint8_t NumOfLineColumns = 0 ;

static volatile uint16_t DelayFactor = 0 ;

static volatile uint8_t *Copy_DataForAlphabet = NULL;

static volatile uint8_t Copy_DataForLine[LEDMAT_MAX_LINE_LENGHT + 14];/*+14 for padding*/

ErrorStatus LedMatrix_Init(void)
{
	uint8_t ERR_State = E_OK ;
	
	/*Check for multitable initialization*/
	if(LEDMAT_Init_Flag == TRUE)
	{
		ERR_State = E_NOK ;
	}
	else
	{
		uint8_t Local_RowIndex = 0;
		uint8_t Local_ColIndex = 0;
		/**************Init Led Matrix Rows Pin by Pin************/
		for(Local_RowIndex = 0 ; Local_RowIndex < LEDMAT_COLS_NUM ; Local_RowIndex++)
		{
			GPIO_InitPin(LedMat_RowsMap[Local_RowIndex].GPIOx , LedMat_RowsMap[Local_RowIndex].LedMatPin , GPIO_OUTPUT_PP_SPEED_2MHz);
		
		}
		/***********Init Led Matrix Columns Pin by Pin************/
		for(Local_ColIndex = 0 ; Local_ColIndex < LEDMAT_ROWS_NUM ; Local_ColIndex++)
		{
			GPIO_InitPin(LedMat_ColsMap[Local_ColIndex].GPIOx , LedMat_ColsMap[Local_ColIndex].LedMatPin , GPIO_OUTPUT_PP_SPEED_2MHz);
		
		}
		/*Notify the system that ledmatirx is initialized*/
		LEDMAT_Init_Flag = TRUE ;
	}
	
	return ERR_State ;
}

ErrorStatus LedMatrix_Display(uint8_t *Data)
{
	/*temp variable to store function state*/
	uint8_t ERR_State = E_OK ;
	
	/*Check if the module is not initialized*/
	if(LEDMAT_Init_Flag == FALSE)
	{
		ERR_State = E_NOK ;
	}
	/*Null pointer checking*/
	else if(Data == NULL)
	{
		ERR_State = E_NOK ;
	}
	else
	{
		/*Copy data buffer to a static global buffer to be used in call back functions functions*/
		Copy_DataForAlphabet = Data ;
		/*first disable all columns*/
		DisableColumns();
		/*Put the data bits of the current index in the The selected row*/
		SetRowsValues(Copy_DataForAlphabet[CurrentDataIndex]);
		/*then Active the column*/
		SetColumn(CurrentColumns);
		/*Start systick timer with inttrupt peridoicly with a configured period and use DsiplayColumnForAlphabet as the callback function*/
		SysTick_SetIntervalPeriodic(LEDMAT_DELAY_IN_TICK , DsiplayColumnForAlphabet);
	}
	
	
	return ERR_State ;
}

ErrorStatus LedMatrix_DisplayLine(uint8_t *Data , uint8_t NumOfColumns)
{
	/*temp variable to store function state*/
	uint8_t ERR_State    = E_OK ;
	uint8_t Local_Index  =  0 ;
	/*Check if the led matrix is not initialized*/
	if(LEDMAT_Init_Flag == FALSE)
	{
		ERR_State = E_NOK ;
	}
	/*Null pointer checking*/
	else if(Data == NULL)
	{
		ERR_State = E_NOK ;
	}
	else
	{
		
		/*store the line column width in a static global variable to be used in call back function*/
		NumOfLineColumns = NumOfColumns + 14 ;/*for padding the array*/
		/*add 7 empty elemnts at first to the array so the line start appear from the last column (just for the animation)*/
		for(Local_Index = 0 ; Local_Index < 8  ; Local_Index++)
		{		
				Copy_DataForLine[Local_Index] = 0 ;				
        }
		/*Copy data buffer to a static global buffer to be used in call back function*/
		for(Local_Index = 0 ; Local_Index <= NumOfColumns  ; Local_Index++)
		{		
				Copy_DataForLine[Local_Index + 8] = Data[Local_Index] ;				
        }
		/*add 7 empty elemnts at last to the array so the last line of the last alphabet ends then start the first alphabet from the last column(just for the animation)*/
		for(Local_Index = 0 ; Local_Index < 8  ; Local_Index++)
		{		
			  /*add the zeros after the array elments ends and +8 beacause we added 7 elemnts at first*/
				Copy_DataForLine[Local_Index + NumOfColumns + 8] = 0 ;				
		}
		/*first disable all columns*/
		DisableColumns();
		/*Put the data bits of the current index in the The selected row*/
		SetRowsValues(Copy_DataForLine[CurrentDataIndex]);
		/*then Active the column*/
		SetColumn(CurrentColumns);
		/*Start systick timer with inttrupt peridoicly with a configured period and use DsiplayColumnForLine as the callback function*/
		SysTick_SetIntervalPeriodic(LEDMAT_DELAY_IN_TICK , DsiplayColumnForLine);
	}
	
	return ERR_State ;
}

void DsiplayColumnForLine(void)
{
	/*Increment the delay every configured period*/
	DelayFactor++;
	/*Every specified period increment the colmuns by one to but the next byte in the next column*/
	CurrentColumns++  ;
	/*Every specified period increment The data array index to the next byte*/
	CurrentDataIndex++;
	
	if(CurrentDataIndex >= 8)
	{
		CurrentDataIndex = 0 ;
	}
	else
	{		
		/*Do Nothing*/
	}
	if(CurrentColumns >= LEDMAT_COLS_NUM)
	{
		if(DelayFactor >= LEDMAT_DISP_LINE_SPEED)
		{
			/*increment LineIndex after the delay configured*/
			LineIndex++;
			if( LineIndex >= (NumOfLineColumns - 7) )/*decrement 7 from number of columns because last column has one has one elemnts for the array*/
			{
				/*Reset LineIndex when it reach the max line array index(the max line columns)*/
				LineIndex = 0;
			}
			else
			{
				/*Do Nothing*/
			}
			/*reset the delay to count again for the next 8(because we just have an 8-columns led matrix)
  			byte of the array (the next alphabet)*/
			DelayFactor = 0 ;
		}
		else
		{
			/*Do Nothing*/
		}
		/*reset the columns counter when it reachs the max configured columns*/
		CurrentColumns = 0 ;
	}
	else
	{		
		/*Do Nothing*/
	}
	/*first disable all columns*/	
	DisableColumns();
	/*Put the data bits of the current index in the The selected row*/
	/*Note : incrementing by LineIndex == left shifting array elemnts circularly */
	/*ex:if array elemnts = {1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , 10 ,11} the address of the first elemtns is 0x20000000
		then the arry elemnts will be the first 8 byts if i incremented by line index assume its 1 then the address will be
		0x200000001 then the next loop the array elemnts will start from 2 ignoring one but the column counter is the same 
		so it will give you the effect of moving because 2 will be written in the first column instead of 1 and the last column 
		will be 9 which is the first column of the next alphabet (9 instead of 8)*/
	SetRowsValues((Copy_DataForLine + LineIndex)[CurrentDataIndex]);
	/*then Active the column*/
	SetColumn(CurrentColumns);
		
}


void DsiplayColumnForAlphabet(void)
{
	/*Every specified period increment The data array index to the next byte*/
	CurrentDataIndex++;
	/*Every specified period increment the colmuns by one to but the next byte in the next column*/
	CurrentColumns++  ;
	if(CurrentDataIndex >= 8)
	{
		CurrentDataIndex = 0 ;
	}
	else
	{		
		/*Do Nothing*/
	}
	if(CurrentColumns >= LEDMAT_COLS_NUM)
	{
		/*reset the columns counter when it reachs the max configured columns*/
		CurrentColumns = 0 ;
	}
	else
	{		
		/*Do Nothing*/
	}	
	
	/*first disable all columns*/
	DisableColumns();
	/*Put the data bits of the current index in the The selected row*/
	SetRowsValues(Copy_DataForAlphabet[CurrentDataIndex]);
	/*then Active the column*/
	SetColumn(CurrentColumns);
		
}


void SetRowsValues(uint8_t Data)
{
	uint8_t Local_Idx = 0;
	uint8_t Local_RowIndex = 0;
	uint8_t Local_TempData[8] ;
	
	/*Get each bit of the selceted array byte*/
	for(Local_Idx = 0 ; Local_Idx < 8 ; Local_Idx++)
	{
		Local_TempData[Local_Idx] = GET_BIT(Data , Local_Idx );
	}
	/*reset the local variable to use it again in another loop*/
	Local_Idx = 0;
	/*Write the data on each row bit by bit*/
	/*a single bit should be written on a single row at atime*/
	for(Local_RowIndex = 0 ; Local_RowIndex < LEDMAT_ROWS_NUM ; Local_RowIndex++)
	{
		GPIO_WritePin(LedMat_RowsMap[Local_RowIndex].GPIOx,LedMat_RowsMap[Local_RowIndex].LedMatPin , Local_TempData[Local_Idx]);
		/*checking on the byte size which is 8 bits*/
		if(Local_Idx >= 7)
		{
			Local_Idx = 0 ;
		}
		else
		{
			Local_Idx++;
		}
	}

}


void SetColumn(uint8_t Column)
{
  	/*Enalbe the the selected column*/
	#if ( LEDMAT_COL_ACTIVE == ACTIVE_LOW )
		GPIO_WritePin(LedMat_ColsMap[Column].GPIOx , LedMat_ColsMap[Column].LedMatPin , GPIO_PIN_LOW) ; 
	#elif (LEDMAT_COL_ACTIVE == ACTIVE_HIGH )
		GPIO_WritePin(LedMat_ColsMap[Column].GPIOx , LedMat_ColsMap[Column].LedMatPin , GPIO_PIN_HIGH) ; 
	#else
	
	#endif
	
}

void DisableColumns(void)
{
	uint8_t Local_ColIndex = 0;
	/*Disable all columns of the led matirx*/
	
	#if ( LEDMAT_COL_ACTIVE == ACTIVE_LOW )
		for(Local_ColIndex = 0 ; Local_ColIndex < LEDMAT_COLS_NUM ; Local_ColIndex++)
		{
			GPIO_WritePin(LedMat_ColsMap[Local_ColIndex].GPIOx,LedMat_ColsMap[Local_ColIndex].LedMatPin,GPIO_PIN_HIGH);
		
		}
	#elif (LEDMAT_COL_ACTIVE == ACTIVE_HIGH )
		for(Local_ColIndex = 0 ; Local_ColIndex < LEDMAT_COLS_NUM ; Local_ColIndex++)
		{
			GPIO_WritePin(LedMat_ColsMap[Local_ColIndex].GPIOx,LedMat_ColsMap[Local_ColIndex].LedMatPin,GPIO_PIN_LOW);
		
		}
	#else
	
	#endif
	
}

