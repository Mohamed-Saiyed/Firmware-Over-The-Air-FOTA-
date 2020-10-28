/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 30 August 2020 	    					 */		
/* Version  : V01										 */	
/*********************************************************/

#ifndef RCC_INIT_H
#define RCC_INIT_H

/*AHB BUS*/
#define RCC_DMA1_ID		0
#define RCC_DMA2_ID		1
#define RCC_SRAM_ID		2
#define RCC_FLITF_ID	4
#define RCC_CRC_ID	    6
#define RCC_OTGFS_ID    12
#define RCC_ETHMAC_ID   14
#define RCC_ETHMAC_ID   14
#define RCC_ETHMACTX_ID 15
#define RCC_ETHMACRX_ID 16

/*APB2 BUS*/
#define RCC_AFIO_ID		32
#define RCC_GPIOA_ID    34
#define RCC_GPIOB_ID	35
#define RCC_GPIOC_ID	36
#define RCC_GPIOD_ID	37
#define RCC_GPIOE_ID	38
#define RCC_ADC1_ID   	41
#define RCC_ADC2_ID   	42
#define RCC_TIM1_ID 	43	
#define RCC_SPI1_ID 	44
#define RCC_USART1_ID 	46

/*APB1 BUS*/
#define RCC_TIM2_ID 	64
#define RCC_TIM3_ID     65
#define RCC_TIM4_ID		66
#define RCC_TIM5_ID		67
#define RCC_TIM6_ID		68
#define RCC_TIM7_ID		69
#define RCC_WWDG_ID   	75
#define RCC_SPI2_ID   	78
#define RCC_SPI3_ID 	79	
#define RCC_USART2_ID 	81
#define RCC_USART3_ID 	82
#define RCC_UART4_ID	83
#define RCC_UART5_ID    84
#define RCC_I2C1_ID		84
#define RCC_I2C2_ID		86
#define RCC_CAN1_ID		89
#define RCC_CAN2_ID		90
#define RCC_BKP_ID   	91
#define RCC_PWR_ID   	92
#define RCC_DAC_ID 		93
	
typedef uint8_t PerId;

ErrorStatus RCC_SysClockInit(void);
ErrorStatus RCC_EnableClock(PerId Peripheral_Id);
ErrorStatus RCC_DisableClock(PerId Peripheral_Id);

#endif /*RCC_INIT_H*/
