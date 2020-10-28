/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 20 ‎September 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/

#include "Std_types.h"
#include "BIT_MATH.h"

#include "AFIO_interface.h"

#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_config.h"

static void (*EXTI0_CallBack)     (void);
static void (*EXTI1_CallBack)     (void);
static void (*EXTI2_CallBack)     (void);
static void (*EXTI3_CallBack)     (void);
static void (*EXTI4_CallBack)     (void);
static void (*EXTI5_CallBack)     (void);
static void (*EXTI6_CallBack)     (void);
static void (*EXTI7_CallBack)     (void);
static void (*EXTI8_CallBack)     (void);
static void (*EXTI9_CallBack)     (void);
static void (*EXTI10_CallBack)    (void);
static void (*EXTI11_CallBack)    (void);
static void (*EXTI12_CallBack)    (void);
static void (*EXTI13_CallBack)    (void);
static void (*EXTI14_CallBack)    (void);
static void (*EXTI15_CallBack)    (void);

ErrorStatus EXTI_EnableInterrupt(AFIO_Pinxx_t Pinxx , EXTI_Line_t Int_Line , EXTI_Edge_e Int_Edge)
{
	/*Temp variable to store the return Function status */
	uint8_t State = 0 ;
	
	/*The maximum EXTI lines is 19*/
	if(Int_Line <= 19)
	{
		/*Select The Pinx Port to configure EXTI Line */
		AFIO_ConfigExtiLine(Pinxx , Int_Line);
		/*Enable Interrupt in EXTI linex*/
		SET_BIT(EXTI->IMR , Int_Line);
		/*Configure Iterrupt polarity*/
		EXTI_ConfigInterruptEdge(Int_Line , Int_Edge);
		State = E_OK;
	}
	else
	{
		State = E_NOK;
	}
	
	return State;
}

ErrorStatus EXTI_ConfigInterruptEdge(EXTI_Line_t Int_Line , EXTI_Edge_e Int_Edge)
{
	/*Temp variable to store the return Function status */
	uint8_t State = 0 ;
	
	/*The maximum EXTI lines is 19*/
	if(Int_Line <= 19)
	{
		switch(Int_Edge)
		{
			case EXTI_RISING_EDGE:
				/*Select the interrupt to fire when Rising edge is detected*/
				SET_BIT(EXTI->RTSR , Int_Line);
			break;
			case EXTI_FALLING_EDGE:
				/*Select the interrupt to fire when Falling edge is detected*/
				SET_BIT(EXTI->FTSR , Int_Line);
			break;
			case EXTI_ON_CHANGE_EDGE:
			 /*Select the interrupt to fire when Falling or Rising edge is detected*/
				SET_BIT(EXTI->FTSR , Int_Line);
				SET_BIT(EXTI->RTSR , Int_Line);
			break;
			default:
			break;
		}
		State = E_OK;
	}
	else
	{
		State = E_NOK;
	}
	
	return State;
}

ErrorStatus EXTI_DisableInterrupt(EXTI_Line_t Int_Line)
{
	/*Temp variable to store the return Function status */
	uint8_t State = 0 ;
	
	/*The maximum EXTI lines is 19*/
	if(Int_Line <= 19)
	{
		/*Cleae intrrupt mode */
		CLR_BIT(EXTI->IMR  , Int_Line);
		/*clear the Rising edge trigger*/
		CLR_BIT(EXTI->RTSR , Int_Line);
		/*clear the Falling edge trigger*/
		CLR_BIT(EXTI->FTSR , Int_Line);
		State = E_OK;
	}
	else
	{
		State = E_NOK;
	}
	
	return State;
}

ErrorStatus EXTI_ClearPending(EXTI_Line_t Int_Line)
{
	/*Temp variable to store the return Function status */
	uint8_t State = 0 ;
	
	/*The maximum EXTI lines is 19*/
	if(Int_Line <= 19)
	{
		/*Clear interrupt pending flag by writing 1 in the corresponding bit*/
		SET_BIT(EXTI->PR , Int_Line);
		State = E_OK;
	}
	else
	{
		State = E_NOK;
	}
	
	return State;
}


ErrorStatus EXTI_GenrateSWI(EXTI_Line_t Int_Line)
{
	/*Temp variable to store the return Function status */
	uint8_t State = 0 ;
	
	/*The maximum EXTI lines is 19*/
	if(Int_Line <= 19)
	{
		/*Set the Pending flag for the EXTI Line*/
		SET_BIT(EXTI->SWIER , Int_Line);
		State = E_OK;
	}
	else
	{
		State = E_NOK;
	}
	
	return State;
}


/*******Setting Exti CallBack Functions*******/
void EXTI0_SetCallBack(void (*ptr) (void))
{
	if(ptr == NULL)
	{
		/*Do Nothing*/
	}
	else
	{
		EXTI0_CallBack = ptr;
	}
	
}

void EXTI1_SetCallBack(void (*ptr) (void))
{
	if(ptr == NULL)
	{
		/*Do Nothing*/
	}
	else
	{
		EXTI1_CallBack = ptr;
	}
	
}

void EXTI2_SetCallBack(void (*ptr) (void))
{
	if(ptr == NULL)
	{
		/*Do Nothing*/
	}
	else
	{
		EXTI2_CallBack = ptr;
	}
	
}

void EXTI3_SetCallBack(void (*ptr) (void))
{
	if(ptr == NULL)
	{
		/*Do Nothing*/
	}
	else
	{
		EXTI3_CallBack = ptr;
	}
	
}


void EXTI4_SetCallBack(void (*ptr) (void))
{
	if(ptr == NULL)
	{
		/*Do Nothing*/
	}
	else
	{
		EXTI4_CallBack = ptr;
	}
	
}

void EXTI5_SetCallBack(void (*ptr) (void))
{
	if(ptr == NULL)
	{
		/*Do Nothing*/
	}
	else
	{
		EXTI5_CallBack = ptr;
	}
	
}

void EXTI6_SetCallBack(void (*ptr) (void))
{
	if(ptr == NULL)
	{
		/*Do Nothing*/
	}
	else
	{
		EXTI6_CallBack = ptr;
	}
	
}

void EXTI7_SetCallBack(void (*ptr) (void))
{
	if(ptr == NULL)
	{
		/*Do Nothing*/
	}
	else
	{
		EXTI7_CallBack = ptr;
	}
	
}

void EXTI8_SetCallBack(void (*ptr) (void))
{
	if(ptr == NULL)
	{
		/*Do Nothing*/
	}
	else
	{
		EXTI8_CallBack = ptr;
	}
	
}

void EXTI9_SetCallBack(void (*ptr) (void))
{
	if(ptr == NULL)
	{
		/*Do Nothing*/
	}
	else
	{
		EXTI9_CallBack = ptr;
	}
	
}

void EXTI10_SetCallBack(void (*ptr) (void))
{
	if(ptr == NULL)
	{
		/*Do Nothing*/
	}
	else
	{
		EXTI10_CallBack = ptr;
	}
	
}

void EXTI11_SetCallBack(void (*ptr) (void))
{
	if(ptr == NULL)
	{
		/*Do Nothing*/
	}
	else
	{
		EXTI11_CallBack = ptr;
	}
	
}

void EXTI12_SetCallBack(void (*ptr) (void))
{
	if(ptr == NULL)
	{
		/*Do Nothing*/
	}
	else
	{
		EXTI12_CallBack = ptr;
	}
	
}

void EXTI13_SetCallBack(void (*ptr) (void))
{
	if(ptr == NULL)
	{
		/*Do Nothing*/
	}
	else
	{
		EXTI13_CallBack = ptr;
	}
	
}

void EXTI14_SetCallBack(void (*ptr) (void))
{
	if(ptr == NULL)
	{
		/*Do Nothing*/
	}
	else
	{
		EXTI14_CallBack = ptr;
	}
	
}

void EXTI15_SetCallBack(void (*ptr) (void))
{
	if(ptr == NULL)
	{
		/*Do Nothing*/
	}
	else
	{
		EXTI15_CallBack = ptr;
	}
	
}

/*******Setting Exti interrupt Handlers*******/

void EXTI0_IRQHandler(void)
{
	if(EXTI0_CallBack == NULL)
	{
		/*Do Nothing*/
	}
	else
	{
	  EXTI0_CallBack();
	}
	
	EXTI_ClearPending(EXTI_LINE_0);	
}

void EXTI1_IRQHandler(void)
{
	if(EXTI1_CallBack == NULL)
	{
		/*Do Nothing*/
	}
	else
	{
	  EXTI1_CallBack();
	}
	
	EXTI_ClearPending(EXTI_LINE_1);	
}

void EXTI2_IRQHandler(void)
{
	if(EXTI2_CallBack == NULL)
	{
		/*Do Nothing*/
	}
	else
	{
	  EXTI2_CallBack();
	}
	
	EXTI_ClearPending(EXTI_LINE_2);	
}

void EXTI3_IRQHandler(void)
{
	if(EXTI2_CallBack == NULL)
	{
		/*Do Nothing*/
	}
	else
	{
	  EXTI3_CallBack();
	}
	
	EXTI_ClearPending(EXTI_LINE_3);	
}

void EXTI4_IRQHandler(void)
{
	if(EXTI4_CallBack == NULL)
	{
		/*Do Nothing*/
	}
	else
	{
	  EXTI4_CallBack();
	}
	
	EXTI_ClearPending(EXTI_LINE_4);	
}

void EXTI9_5_IRQHandler(void)
{
	if(BIT_IS_SET(EXTI->PR , 5))
	{
		if(EXTI5_CallBack == NULL)
		{
			/*Do Nothing*/
		}
		else
		{
			EXTI5_CallBack();
		}
	
		EXTI_ClearPending(EXTI_LINE_5);	
	}
	else if(BIT_IS_SET(EXTI->PR , 6))
	{
		if(EXTI6_CallBack == NULL)
		{
			/*Do Nothing*/
		}
		else
		{
			EXTI6_CallBack();
		}
	
		EXTI_ClearPending(EXTI_LINE_6);			
	}
	else if(BIT_IS_SET(EXTI->PR , 7))
	{
		if(EXTI7_CallBack == NULL)
		{
			/*Do Nothing*/
		}
		else
		{
			EXTI7_CallBack();
		}
	
		EXTI_ClearPending(EXTI_LINE_7);			
	}
	else if(BIT_IS_SET(EXTI->PR , 8))
	{
		if(EXTI8_CallBack == NULL)
		{
			/*Do Nothing*/
		}
		else
		{
			EXTI8_CallBack();
		}
	
		EXTI_ClearPending(EXTI_LINE_8);			
	}
	else
	{
		if(EXTI9_CallBack == NULL)
		{
			/*Do Nothing*/
		}
		else
		{
			EXTI9_CallBack();
		}
	
		EXTI_ClearPending(EXTI_LINE_9);	
	}
	
}

void EXTI15_10_IRQHandler(void)
{
	if(BIT_IS_SET(EXTI->PR , 10))
	{
		if(EXTI10_CallBack == NULL)
		{
			/*Do Nothing*/
		}
		else
		{
			EXTI10_CallBack();
		}
	
		EXTI_ClearPending(EXTI_LINE_10);	
	}
	else if(BIT_IS_SET(EXTI->PR , 11))
	{
		if(EXTI11_CallBack == NULL)
		{
			/*Do Nothing*/
		}
		else
		{
			EXTI11_CallBack();
		}
	
		EXTI_ClearPending(EXTI_LINE_11);			
	}
	else if(BIT_IS_SET(EXTI->PR , 12))
	{
		if(EXTI12_CallBack == NULL)
		{
			/*Do Nothing*/
		}
		else
		{
			EXTI12_CallBack();
		}
	
		EXTI_ClearPending(EXTI_LINE_12);			
	}
	else if(BIT_IS_SET(EXTI->PR , 13))
	{
		if(EXTI13_CallBack == NULL)
		{
			/*Do Nothing*/
		}
		else
		{
			EXTI13_CallBack();
		}
	
		EXTI_ClearPending(EXTI_LINE_13);			
	}
	else if(BIT_IS_SET(EXTI->PR , 14))
	{
		if(EXTI14_CallBack == NULL)
		{
			/*Do Nothing*/
		}
		else
		{
			EXTI14_CallBack();
		}
	
		EXTI_ClearPending(EXTI_LINE_14);	
	}
	else
	{
		if(EXTI15_CallBack == NULL)
		{
			/*Do Nothing*/
		}
		else
		{
			EXTI15_CallBack();
		}
	
		EXTI_ClearPending(EXTI_LINE_15);
	}
	
}
