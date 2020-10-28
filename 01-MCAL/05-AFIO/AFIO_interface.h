/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 20 ‎September 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/
#ifndef AFIO_INTERFACE_H
#define AFIO_INTERFACE_H


#define PAx		0x0
#define PBx		0x1
#define PCx		0x2
#define PDx		0x3
#define PEx		0x4
#define PFx		0x5
#define PGx		0x6

typedef uint8_t AFIO_Pinxx_t;

typedef enum 
{
	AFIO_REMAP_NONE    = 0 ,
	AFIO_REMAP_PARTIAL = 1 ,
	AFIO_REMAP_FULL    = 2
	
}AFIO_RemapOptions;


typedef enum 
{
	SPI1_REMAP			 = 0  ,
	I2C1_REMAP 			 = 1  ,
	USART1_REMAP 		 = 2  ,
	USART2_REMAP 		 = 3  ,
	USART3_REMAP 		 = 4  ,
	TIM1_REMAP 			 = 5  ,
	TIM2_REMAP			 = 6  ,
	TIM3_REMAP 		  	 = 7  ,
	TIM4_REMAP 		  	 = 8  ,
	CAN_REMAP 		  	 = 9  ,
	PD01_REMAP 		  	 = 10 ,
	TIM5CH4_REMAP 	   	 = 11 ,
	ADC1_ETRGINJ_REMAP	 = 12 ,
	ADC1_ETRGREG_REMAP	 = 13 ,
	ADC2_ETRGINJ_REMAP	 = 14 ,
	ADC2_ETRGREG_REMAP	 = 15 
	
}AFIO_RemapId;

/**************Functions Prototypes*******************/
ErrorStatus AFIO_ConfigExtiLine(AFIO_Pinxx_t Pinx , uint8_t Int_Line);
ErrorStatus AFIO_Remap(AFIO_RemapId Id , AFIO_RemapOptions RemapOptions);


#endif /*AFIO_INTERFACE_H*/
