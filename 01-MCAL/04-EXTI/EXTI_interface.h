/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 20 ‎September 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/
#ifndef EXTI_INTIT_H
#define EXTI_INTIT_H

/*EXTI line definetion*/
#define EXTI_LINE_0			0
#define EXTI_LINE_1			1
#define EXTI_LINE_2			2
#define EXTI_LINE_3			3
#define EXTI_LINE_4			4
#define EXTI_LINE_5			5
#define EXTI_LINE_6			6
#define EXTI_LINE_7			7
#define EXTI_LINE_8			8
#define EXTI_LINE_9			9
#define EXTI_LINE_10		10
#define EXTI_LINE_11		11
#define EXTI_LINE_12		12
#define EXTI_LINE_13		13
#define EXTI_LINE_14		14
#define EXTI_LINE_15		15
#define EXTI_LINE_16		16
#define EXTI_LINE_17		17
#define EXTI_LINE_18		18
#define EXTI_LINE_19		19

typedef uint8_t EXTI_Line_t ;

typedef enum
{
	EXTI_RISING_EDGE  	= 0	,
	EXTI_FALLING_EDGE 	= 1	,
	EXTI_ON_CHANGE_EDGE = 2
	
}EXTI_Edge_e;

/**************Functions Prototypes*******************/
ErrorStatus EXTI_EnableInterrupt(AFIO_Pinxx_t Pinxx , EXTI_Line_t Int_Line , EXTI_Edge_e Int_Edge);
ErrorStatus EXTI_ConfigInterruptEdge(EXTI_Line_t Int_Line , EXTI_Edge_e Int_Edge);
ErrorStatus EXTI_DisableInterrupt(EXTI_Line_t Int_Line);
ErrorStatus EXTI_ClearPending(EXTI_Line_t Int_Line);
ErrorStatus EXTI_GenrateSWI(EXTI_Line_t Int_Line);
/**************Callback Functions Prototypes*******************/
void EXTI0_SetCallBack	  (void (*ptr) (void));
void EXTI1_SetCallBack	  (void (*ptr) (void));
void EXTI2_SetCallBack	  (void (*ptr) (void));
void EXTI3_SetCallBack	  (void (*ptr) (void));
void EXTI4_SetCallBack	  (void (*ptr) (void));
void EXTI5_SetCallBack	  (void (*ptr) (void));
void EXTI6_SetCallBack	  (void (*ptr) (void));
void EXTI7_SetCallBack	  (void (*ptr) (void));
void EXTI8_SetCallBack	  (void (*ptr) (void));
void EXTI9_SetCallBack	  (void (*ptr) (void));
void EXTI10_SetCallBack	  (void (*ptr) (void));
void EXTI11_SetCallBack	  (void (*ptr) (void));
void EXTI12_SetCallBack	  (void (*ptr) (void));
void EXTI13_SetCallBack	  (void (*ptr) (void));
void EXTI14_SetCallBack	  (void (*ptr) (void));
void EXTI15_SetCallBack	  (void (*ptr) (void));


#endif /*EXTI_INTIT_H*/


