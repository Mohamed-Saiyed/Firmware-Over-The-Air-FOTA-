/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 30 ‎September 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/

#ifndef OS_INTERFACE_H
#define OS_INTERFACE_H

void OS_CreateTASK(uint8_t ID , uint8_t period , uint8_t InitialDelay , void (*Taks) (void));
void OS_StartScheduler(void);

#endif /*OS_INTERFACE_H*/
