/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 30 ‎September 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/

#ifndef OS_PRIVATE_H
#define OS_PRIVATE_H

typedef enum 
{
	TASK_READY      = 1 ,
	TASK_RUNNNING   = 2 ,
	TASK_BLCOKED    = 3 ,
	TASK_SUSPENDED  = 4
}TASK_State_e;

typedef struct 
{
	uint32_t period ;
	void    (*Task) (void);
	uint8_t InitialDelay ;
	TASK_State_e State ;
	
}TCP_t;


#endif /*OS_PRIVATE_H*/
