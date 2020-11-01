/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 13 ‎September 2020	    					 */		
/* Version  : V02                                        */
/* LOG		: V01 -> First Creation	with unsigned DT	 */
/*			  V02 -> Adding signed DT        			 */	
/*********************************************************/

#ifndef STD_TYPES_H
#define STD_TYPES_H

#define TRUE 	1
#define FALSE	0

typedef unsigned char        uint8_t 	;
typedef unsigned short int   uint16_t	;
typedef unsigned long  int   uint32_t	;

typedef signed char       int8_t 	;
typedef signed short int  int16_t	;
typedef signed long  int  int32_t	;

typedef enum
{
	E_OK					= 0, 
	E_TIMEOUT				= 1,
	E_NOK 					= 2,
	NULL_PTR 				= 3,
	MULTIPLE_INITIALIZATION = 4
	
}ErrorStatus;





#endif /*STD_TYPES_H*/
