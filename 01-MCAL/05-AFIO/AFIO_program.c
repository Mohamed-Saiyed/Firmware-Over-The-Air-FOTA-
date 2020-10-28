/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 20 ‎September 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/
#include "Std_types.h"
#include "BIT_MATH.h"


#include "AFIO_interface.h"
#include "AFIO_private.h"
#include "AFIO_config.h"

ErrorStatus AFIO_ConfigExtiLine(AFIO_Pinxx_t Pinx , uint8_t Int_Line)
{
	/*Temp variable to store the return Function status */
	uint8_t state = 0 ;
	/*The las port is Port G*/
	if(Pinx <= PGx)
	{
		/*We need to go to the higher rigester every 4 EXTI Lines == Int_Line / 4*/
		uint8_t Arr_Index = Int_Line >> 2 ;
		/*Every exti line has 4 bits for configuration*/
		uint8_t EXTI_Line = ((Int_Line % 4) * 4 ) ;
		
		/*Reset Exti line configeration bits*/
		AFIO->EXTICR[Arr_Index] &= ~ (0xF  << EXTI_Line)  ;
		/*Set Exti line Port*/
		AFIO->EXTICR[Arr_Index] |=   (Pinx << EXTI_Line)  ;
		
		state = E_OK ; 
	}
	else
	{
		state = E_NOK ; 
	}
	
	return state ;
}

ErrorStatus AFIO_Remap(AFIO_RemapId Id , AFIO_RemapOptions RemapOptions)
{
	switch(Id)
	{                                 
		case SPI1_REMAP		   :SET_BIT(AFIO->MAPR , 0);		break ;
		case I2C1_REMAP        :SET_BIT(AFIO->MAPR , 1);		break ;
		case USART1_REMAP 	   :SET_BIT(AFIO->MAPR , 2);		break ;
		case USART2_REMAP 	   :SET_BIT(AFIO->MAPR , 3);		break ;
		case USART3_REMAP      :
			
			switch(RemapOptions)
			{
				case AFIO_REMAP_PARTIAL: AFIO->MAPR |= (0x1 << 4) ; break ;
				case AFIO_REMAP_FULL   : AFIO->MAPR |= (0x3 << 4) ; break ;
				default : break ;
			}


		break ;
		case TIM1_REMAP 	   :
		
			switch(RemapOptions)
			{
				case AFIO_REMAP_PARTIAL: AFIO->MAPR |= (0x1 << 6) ; break ;
				case AFIO_REMAP_FULL   : AFIO->MAPR |= (0x3 << 6) ; break ;
				default : break ;
			}

		break ;
		case TIM2_REMAP	       :
			
			switch(RemapOptions)
			{
				case AFIO_REMAP_PARTIAL: AFIO->MAPR |= (0x1 << 8) ; break ;
				case AFIO_REMAP_FULL   : AFIO->MAPR |= (0x3 << 8) ; break ;
				default : break ;
			}

		break ;
		case TIM3_REMAP        :
			
			switch(RemapOptions)
			{
				case AFIO_REMAP_PARTIAL: AFIO->MAPR |= (0x1 << 10) ; break ;
				case AFIO_REMAP_FULL   : AFIO->MAPR |= (0x3 << 10) ; break ;
				default : break ;
			}
			
		break ;
		case TIM4_REMAP        : SET_BIT(AFIO->MAPR , 12);		break ;
		case CAN_REMAP 	       : AFIO->MAPR |= (0x3 << 13) ;	break ;
		case PD01_REMAP        : SET_BIT(AFIO->MAPR , 15);		break ;
		case TIM5CH4_REMAP 	   : SET_BIT(AFIO->MAPR , 16);		break ;
		case ADC1_ETRGINJ_REMAP: SET_BIT(AFIO->MAPR , 17);		break ;
		case ADC1_ETRGREG_REMAP: SET_BIT(AFIO->MAPR , 18);		break ;
		case ADC2_ETRGINJ_REMAP: SET_BIT(AFIO->MAPR , 19);		break ;
		case ADC2_ETRGREG_REMAP: SET_BIT(AFIO->MAPR , 20);		break ;
		default                :	                        	break ;
	}
	
}

