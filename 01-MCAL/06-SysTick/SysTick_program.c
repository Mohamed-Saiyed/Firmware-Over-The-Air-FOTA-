/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 23 ‎September 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/
#include "Std_types.h"
#include "BIT_MATH.h"

#include "SysTick_interface.h"
#include "SysTick_private.h"
#include "SysTick_config.h"

static void (*SysTick_Callback) (void) = NULL;

static volatile uint8_t SysTick_IntervalMode = 0 ;

void SysTick_Init(void)
{
	/*Disable SysTick interrupt*/
	CLR_BIT(SysTick->CTRL , 1);
	/*Disable SysTick*/
	CLR_BIT(SysTick->CTRL , 0);
	#if (STK_CLOCK_SOURCE == AHP_CLK_DIV8)
		/*Choose AHP/8 as SysTick Clock source*/
		CLR_BIT(SysTick->CTRL , 2);
	#elif (STK_CLOCK_SOURCE == AHP_CLK)
		/*Choose AHP as SysTick Clock source*/
		SET_BIT(SysTick->CTRL , 2);
	#else
		#error "Wrong Systick clock source"
	#endif
}
void SysTick_SetBusyWait(uint32_t TickCounts)
{
	/*Preload TickCounts value in systick load rigester*/
	SysTick->LOAD = TickCounts - 1;
	/*Enable SysTick*/
	SET_BIT(SysTick->CTRL , 0) ;
	/*Wait until SysTick finshs counting... the COUNTFLAG To be 1*/
	while(BIT_IS_CLEAR(SysTick->CTRL , 16));
}
ErrorStatus SysTick_SetIntervalSingle(uint32_t TickCounts , void (*Ptr)(void))
{
	/*Temp variable to store function state*/
	uint8_t state = 0 ;
	/*Check if the pointer points to NULL*/
	if(Ptr != NULL)
	{
		SysTick_Stop();
		/*Preload TickCounts value in systick load rigester*/
		 SysTick->LOAD = TickCounts ;
		/*Enable SysTick interrupt*/
	     SET_BIT(SysTick->CTRL , 1) ;
		/*Setting SysTick Callback Function*/
		 SysTick_Callback = Ptr ;
		/*Set the interval mode*/
		SysTick_IntervalMode = SYSTICK_INTERVAL_SINGLE;
		/*Enable SysTick*/
	    SET_BIT(SysTick->CTRL , 0) ;
		
		state = E_OK ;
	}
	else
	{
		state = E_NOK ;
	}
	
	return state ;
}

void SysTick_Start(uint32_t TickCounts)
{
	
	SysTick_Stop();
	/*Preload TickCounts value in systick load rigester*/
	 SysTick->LOAD = TickCounts ;
	/*Enable SysTick interrupt*/
     SET_BIT(SysTick->CTRL , 1) ;
	/*Set the interval mode*/
	SysTick_IntervalMode = SYSTICK_INTERVAL_SINGLE;
	/*Enable SysTick*/
    SET_BIT(SysTick->CTRL , 0) ;
	
}

ErrorStatus SysTick_SetIntervalPeriodic(uint32_t TickCounts , void (*Ptr)(void))
{
	/*Temp variable to store function state*/
	uint8_t state = 0 ;
	/*Check if the pointer points to NULL*/
	if(Ptr != NULL)
	{
		/*Preload TickCounts value in systick load rigester*/
		 SysTick->LOAD = TickCounts - 1 ; /*(TickCounts - 1) according to the Datasheet*/
		/*Enable SysTick interrupt*/
	     SET_BIT(SysTick->CTRL , 1) ;
		/*Setting SysTick Callback Function*/
		 SysTick_Callback = Ptr ;
		/*Set the interval mode*/
		SysTick_IntervalMode = SYSTICK_INTERVAL_PERIODIC;
		/*Enable SysTick*/
	   SET_BIT(SysTick->CTRL , 0) ;
		
		state = E_OK ;
	}
	else
	{
		state = E_NOK ;
	}
	
	return state ;
}
uint32_t SysTick_GetElapsedTime(void)
{
	/*Local Temp variable to store Elapsed time value*/
	uint32_t Local_ElspsedTime = 0 ;
	/*Elapsed time = the Loaded value - the Remaining Time*/
	Local_ElspsedTime = ((SysTick->LOAD) - (SysTick->VAL))  ;
	/*return the Elapsed Time*/
	return Local_ElspsedTime ;
}
uint32_t SysTick_GetRemainingTime(void)
{
	/*Local Temp variable to store Remaining time value*/
	uint32_t Local_RemainingTime = 0 ;
	/*Elapsed time = the Loaded value - the Remaining Time*/
	Local_RemainingTime = SysTick->VAL ;
	/*return the Remaining Time*/
	return Local_RemainingTime ;
}
void SysTick_Stop(void)
{
	/*Disable SysTick interrupt*/
	CLR_BIT(SysTick->CTRL , 1);
	/*Disable SysTick*/
	CLR_BIT(SysTick->CTRL , 0);
	/*Clear SysTick load Register*/
	SysTick->LOAD = 0 ;
	/*Clear SysTick value Register*/
	SysTick->VAL = 0  ;
}

void SysTick_SetCallBack(void (*ptr) (void))
{
	if(ptr != NULL)
	{
		SysTick_Callback = ptr ;
	}
	else
	{
		
	}
}

void SysTick_Handler(void)
{
	uint8_t Local_Temp;
	
	if(SysTick_Callback != NULL)
	{
		if(SysTick_IntervalMode == SYSTICK_INTERVAL_SINGLE)
		{
			/*Disable SysTick interrupt*/
			CLR_BIT(SysTick->CTRL , 1);
			/*Disable SysTick*/
			CLR_BIT(SysTick->CTRL , 0);
			/*Clear SysTick load Register*/
			SysTick->LOAD = 0 ;
			/*Clear SysTick value Register*/
			SysTick->VAL = 0  ;
		}
		else
		{
			
		}
		/*Call the set call back function*/
		SysTick_Callback();
	}
	else
	{
		
	}
	/*Clear SysTick interrupt Flag according to the datasheet*/
	Local_Temp = GET_BIT(SysTick->CTRL , 16);
}
