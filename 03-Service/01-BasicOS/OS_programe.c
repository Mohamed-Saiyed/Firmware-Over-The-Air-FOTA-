/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 30 ‎September 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/


#include "Std_types.h"
#include "BIT_MATH.h"

#include "SysTick_interface.h"

#include "OS_interface.h"
#include "OS_Private.h"
#include "OS_config.h"

static volatile uint32_t g_Tick_Counter = 0 ;

TCP_t TCB[NUM_OF_TASKS] = {NULL}

void OS_CreateTASK(uint8_t ID , uint32_t period , uint8_t InitialDelay , void (*TASK) (void))
{
	TCB[ID].period 	     =  period        ;
	TCB[ID].Task   	     =  TASK   		  ;
	TCB[ID].InitialDelay =  period		  ;
	TCB[ID].State        =  TASK_READY    ;
}

void OS_StartScheduler(void)
{
	SysTick_Init(void);
	SysTick_SetIntervalPeriodic(TICK_RATE_HZ , Scheduler);
}

void Scheduler(void)
{
	volatile uint32_t Local_Index = 0 ;
	for(Local_Index = 0 ; Local_Index < NUM_OF_TASKS ; Local_Index++)
	{
			if((g_Tick_Counter % TCB[Local_Index].period ) == 0)
			{
				if(TCB[Local_Index].Task != NULL && TCB[Local_Index].State == TASK_READY)
				{
					if(TCB[Local_Index].InitialDelay == 0)
					{
						TCB[Local_Index].Task();
					}
					else
					{
						TCB[Local_Index].InitialDelay--;
					}
						
				}
				else
				{
					/*Do Nothing*/
				}
			}
			else
			{
				/*Do Nothing*/
			}
				
	}
	g_Tick_Counter++;
}
