/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 13 ‎September 2020	    					 */		
/* Version  : V01                                       */
/*********************************************************/
#ifndef BIT_MATH_H
#define BIT_MATH_H

#define NULL		((void *) 0 )


#define SET_BIT(VAR,BIT)   	  ((VAR) |=  (1 << (BIT)))
#define SET_PORT(VAR,VAL)  	  ((VAR) = (VAL))
#define CLR_BIT(VAR,BIT)  	  ((VAR) &= ~((uint32_t)1 << (BIT)))
#define TOGGLE_BIT(VAR,BIT)   ((VAR) ^=  (1 << (BIT)))
#define GET_BIT(VAR,BIT)      (((VAR) >> BIT) & 1)
#define BIT_IS_SET(VAR,BIT)   ((VAR) & (1 << BIT))
#define BIT_IS_CLEAR(VAR,BIT) (!((VAR) & (1 << BIT))) 

#endif /*BIT_MATH_H*/
