/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 13 ‎September 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/
#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H

#include "GPIO_private.h"
/********GPIO Pins Enumeration******/
#define GPIO_PIN_0		0
#define GPIO_PIN_1		1
#define GPIO_PIN_2		2
#define GPIO_PIN_3		3
#define GPIO_PIN_4		4
#define GPIO_PIN_5		5
#define GPIO_PIN_6		6
#define GPIO_PIN_7		7
#define GPIO_PIN_8		8
#define GPIO_PIN_9		9
#define GPIO_PIN_10		10
#define GPIO_PIN_11		11
#define GPIO_PIN_12		12
#define GPIO_PIN_13		13
#define GPIO_PIN_14		14
#define GPIO_PIN_15		15

#define GPIOA		GPIO_PORT_A
#define GPIOB 		GPIO_PORT_B
#define GPIOC       GPIO_PORT_C

/********Status of Gpio Pin*************/
#define GPIO_PIN_HIGH	(1)
#define GPIO_PIN_LOW	(0)

/***********GPIO Pins Modes***************/

/***********GPIO Pins Output Modes********/
#define GPIO_OUTPUT_PP_SPEED_10MHz	(0x01)
#define GPIO_OUTPUT_OD_SPEED_10MHz	(0x05)
#define AF_OUTPUT_PP_SPEED_10MHz	(0x09)
#define AF_OUTPUT_OD_SPEED_10MHz	(0x0D)
                                    
#define GPIO_OUTPUT_PP_SPEED_2MHz	(0x02)
#define GPIO_OUTPUT_OD_SPEED_2MHz	(0x06)
#define AF_OUTPUT_PP_SPEED_2MHz		(0x0A)
#define AF_OUTPUT_OD_SPEED_2MHz		(0x0E)
                                    
#define GPIO_OUTPUT_PP_SPEED_50MHz	(0x03)
#define GPIO_OUTPUT_OD_SPEED_50MHz	(0x07)
#define AF_OUTPUT_PP_SPEED_50MHz	(0x0B)
#define AF_OUTPUT_OD_SPEED_50MHz	(0x0F)

/***********GPIO Pins Inputs Modes********/
#define GPIO_ANALOG					(0x00)
#define GPIO_INPUT_FLOATING			(0x04)
#define GPIO_INPUT_PULL				(0x08)


/********User defined Data types for functions arguments*******/
typedef uint8_t DIO_Pin_t ;
typedef uint8_t DIO_Mode_t;
typedef uint8_t DIO_PinStatus_t	;


/******Functions prototypes***************/
ErrorStatus GPIO_InitPin(GPIO_Typedef *GPIOx , DIO_Pin_t Pin , DIO_Mode_t Mode);
ErrorStatus GPIO_WritePin(GPIO_Typedef *GPIOx, DIO_Pin_t Pin, DIO_PinStatus_t Staus);
ErrorStatus GPIO_ReadPin(GPIO_Typedef *GPIOx , DIO_Pin_t Pin, uint8_t *Buffer);
ErrorStatus GPIO_TogglePin(GPIO_Typedef *GPIOx , DIO_Pin_t Pin);
ErrorStatus GPIO_LockPin(GPIO_Typedef *GPIOx , DIO_Pin_t Pin);

#endif /*GPIO_INTERFACE_H*/
