/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 4 November 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/

#ifndef I2C_PRIVATE_H
#define I2C_PRIVATE_H

#define I2C1_BASE	(0x40005400)
#define I2C2_BASE   (0x40005800)

#define I2C1		((I2C_Typedef *)	I2C1_BASE)
#define I2C2		((I2C_Typedef *)	I2C2_BASE)

#define I2C_REMAP_ENABLE    			1
#define I2C_REMAP_DISABLE       		0

#define I2C1_SDA_PIN			GPIO_PIN_6
#define I2C1_SCL_PIN		    GPIO_PIN_7

#define I2C1_SDA_PIN_RM		    GPIO_PIN_9
#define I2C1_SCL_PIN_RM 		GPIO_PIN_8

#define I2C2_SDA_PIN			GPIO_PIN_11
#define I2C2_SCL_PIN			GPIO_PIN_10

typedef struct 
{
	volatile uint32_t CR1	;
	volatile uint32_t CR2	;
	volatile uint32_t OAR1	;
	volatile uint32_t OAR	;
	volatile uint32_t DR	;
	volatile uint32_t SR1	;
	volatile uint32_t SR2	;
	volatile uint32_t CCR	;
	volatile uint32_t TRISE	;
	
}I2C_Typedef;


static void SetI2cClock(I2c_ConfigType *Config);
static void SetI2cPins(I2c_ConfigType *Config);


#endif /*I2C_PRIVATE_H*/
