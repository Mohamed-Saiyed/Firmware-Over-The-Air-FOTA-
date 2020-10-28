/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 23 ‎September 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/

#ifndef SYSTICK_INTERFACE_H
#define SYSTICK_INTERFACE_H


void SysTick_Init(void);
void SysTick_SetBusyWait(uint32_t TickCounts);
ErrorStatus SysTick_SetIntervalSingle(uint32_t TickCounts , void (*Ptr)(void));
ErrorStatus SysTick_SetIntervalPeriodic(uint32_t TickCounts , void (*Ptr)(void));
uint32_t SysTick_GetElapsedTime(void);
uint32_t SysTick_GetRemainingTime(void);
void SysTick_Stop(void);
void SysTick_Start(uint32_t TickCounts);
void SysTick_SetCallBack(void (*ptr) (void));


#endif /*SYSTICK_INTERFACE_H*/
