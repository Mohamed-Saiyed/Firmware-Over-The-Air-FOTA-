/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 17 ‎September 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/

#ifndef NVIC_INTERFACE_H
#define NVIC_INTERFACE_H

#define NVIC_PRIGROUP_1		(0x3)  /* Group priorities = 16   ,    Sub priorities = None  */
#define NVIC_PRIGROUP_2		(0x4)  /* Group priorities = 8    ,    Sub priorities = 2     */
#define NVIC_PRIGROUP_3     (0x5)  /* Group priorities = 4    ,    Sub priorities = 4     */
#define NVIC_PRIGROUP_4     (0x6)  /* Group priorities = 2    ,    Sub priorities = 8     */
#define NVIC_PRIGROUP_5     (0x7)  /* Group priorities = None ,    Sub priorities = 16    */

typedef uint8_t NVIC_PriorityGroup;

typedef enum
{
/******Cortex-M3 Processor Exceptions Numbers **************/
	 NonMaskableInt_IRQn         = -14,
	 MemoryManagement_IRQn       = -12,
	 BusFault_IRQn               = -11,
	 UsageFault_IRQn             = -10,
	 SVCall_IRQn                 = -5, 
	 DebugMonitor_IRQn           = -4, 
	 PendSV_IRQn                 = -2, 
	 SysTick_IRQn                = -1, 
	 
/*******STM32F103xxx specific Interrupt Numbers *******************/
	WWDG_IRQn                   = 0, 
    PVD_IRQn                    = 1, 
    TAMPER_IRQn                 = 2, 
    RTC_IRQn                    = 3, 
    FLASH_IRQn                  = 4, 
    RCC_IRQn                    = 5, 
    EXTI0_IRQn                  = 6, 
    EXTI1_IRQn                  = 7, 
    EXTI2_IRQn                  = 8, 
    EXTI3_IRQn                  = 9, 
    EXTI4_IRQn                  = 10,
    DMA1_Channel1_IRQn          = 11,
    DMA1_Channel2_IRQn          = 12,
    DMA1_Channel3_IRQn          = 13,
    DMA1_Channel4_IRQn          = 14,
    DMA1_Channel5_IRQn          = 15,
    DMA1_Channel6_IRQn          = 16,
	DMA1_Channel7_IRQn          = 17,
	ADC1_2_IRQn                 = 18, 
	USB_HP_CAN_TX_IRQn          = 19, 
	USB_LP_CAN_RX0_IRQn         = 20, 
	CAN_RX1_IRQn                = 21, 
	CAN_SCE_IRQn                = 22, 
	EXTI9_5_IRQn                = 23, 
	TIM1_BRK_IRQn               = 24, 
	TIM1_UP_IRQn                = 25, 
	TIM1_TRG_COM_IRQn           = 26, 
	TIM1_CC_IRQn                = 27, 
	TIM2_IRQn                   = 28,
	TIM3_IRQn                   = 29,
	TIM4_IRQn        		    = 30,
	I2C1_EV_IRQn          		= 31,
	I2C1_ER_IRQn                = 32,
	I2C2_EV_IRQn                = 33,
	I2C2_ER_IRQn                = 34,
	SPI1_IRQn          			= 35,
	SPI2_BRK_IRQn               = 36, 
	USART1_IRQn                 = 37, 
	USART2_IRQn                 = 38, 
	USART3_IRQn                 = 39, 
	EXTI15_10_IRQn              = 40,
	RTCAlarm_IRQn               = 41,
	USBWakeup_IRQn              = 42,
	TIM8_BRKIRQn                = 43,
	TIM8_UP_IRQn                = 44,
	TIM8_TRG_COM_IRQn           = 45,
	TIM8_CC_IRQn                = 46,
	ADC3_IRQn                   = 47,
	FSMC_IRQn                   = 48, 
	SDIO_IRQn                   = 49, 
	TIM5_IRQn                   = 50,
	SPI3_IRQn         			= 51,
	UART4_IRQn                  = 52,
	UART5_BRKIRQn          		= 53,
	TIM6_IRQn          			= 54,
	TIM7_IRQn          			= 55,
	DMA2_Channel1_IRQn          = 56,
	DMA2_Channel2_IRQn          = 57,
	DMA2_Channel3_IRQn          = 58,
	DMA2_Channel4_5_IRQn        = 59
 
}IRQn_Type;

/**************Functions Prototypes*******************/
ErrorStatus NVIC_EnableInterrupt(IRQn_Type IRQn);
ErrorStatus NVIC_DisableInterrupt(IRQn_Type IRQn);
ErrorStatus NVIC_SetPendingFlag(IRQn_Type IRQn);
ErrorStatus NVIC_ClearPendingFlag(IRQn_Type IRQn);
ErrorStatus  NVIC_GetActiveFlag(IRQn_Type IRQn , uint8_t *Buffer);
ErrorStatus NVIC_SetPriorityGrouping(NVIC_PriorityGroup PriorityGroup);
ErrorStatus NVIC_GetActiveFlag(IRQn_Type IRQn , uint8_t *Buffer);
ErrorStatus NVIC_SetPriority(IRQn_Type IRQn , uint8_t Priority);

#endif /*NVIC_INTERFACE_H*/

