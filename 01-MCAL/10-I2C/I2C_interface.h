/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 4 November 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/

#ifndef I2C_INTERFACE_H
#define I2C_INTERFACE_H

typedef enum
{
	I2C1_ID = 0 ,
	I2C2_ID = 1
	
}I2C_ID;

typedef enum 
{
	I2C_FREQ_2 MHZ = 2  ,
	I2C_FREQ_3 MHZ = 3  ,
	I2C_FREQ_4 MHZ = 4  ,
	I2C_FREQ_5 MHZ = 5  ,
	I2C_FREQ_6 MHZ = 6  ,
	I2C_FREQ_7 MHZ = 7  ,
	I2C_FREQ_8 MHZ = 8  ,
	I2C_FREQ_9 MHZ = 9  ,
	I2C_FREQ_10MHZ = 10 ,
	I2C_FREQ_11MHZ = 11 ,
	I2C_FREQ_12MHZ = 12 ,
	I2C_FREQ_13MHZ = 13 ,
	I2C_FREQ_14MHZ = 14 ,
	I2C_FREQ_15MHZ = 15 ,
	I2C_FREQ_16MHZ = 16 ,
	I2C_FREQ_17MHZ = 17 ,
	I2C_FREQ_18MHZ = 18 ,
	I2C_FREQ_19MHZ = 19 ,
	I2C_FREQ_20MHZ = 20 ,
	I2C_FREQ_21MHZ = 21 ,
	I2C_FREQ_22MHZ = 22 ,
	I2C_FREQ_23MHZ = 23 ,
	I2C_FREQ_24MHZ = 24 ,
	I2C_FREQ_25MHZ = 25 ,
	I2C_FREQ_26MHZ = 26 ,
	I2C_FREQ_27MHZ = 27 ,
	I2C_FREQ_28MHZ = 28 ,
	I2C_FREQ_29MHZ = 29 ,
	I2C_FREQ_30MHZ = 30 ,
	I2C_FREQ_31MHZ = 31 ,
	I2C_FREQ_32MHZ = 32 ,
	I2C_FREQ_33MHZ = 33 ,
	I2C_FREQ_34MHZ = 34 ,
	I2C_FREQ_35MHZ = 35 ,
	I2C_FREQ_36MHZ = 36 
	
}I2C_FreqConfigType;

typedef enum
{
	I2C_ADDRESS_MODE_7BIT  = 0 ,
	I2C_ADDRESS_MODE_10BIT = 1 
	
}I2C_SlaveAddressMode;

typedef enum
{
	I2C_DUTYCYCLE_NONE = 0 ,
	I2C_DUTYCYCLE_2    = 1 ,
	I2C_DUTYCYCLE_16_9 = 2 
	
}I2C_DutyCycle;

typedef enum
{
	I2C_MODE_STANDARD  = 0 ,
	I2C_MODE_FAST	   = 1
	
}I2c_Mode;

typedef struct 
{
	I2C_Typdef			 *I2Cx				;
	
	I2C_ID				 ID					;

	I2c_Mode			 Mode				;
	
	uint32_t 			 ClockStretching	;
	
	uint32_t 			 ClockSpeed			;
	
	I2C_FreqConfigType 	 I2C_PeripheralFreq	;
	
	I2C_SlaveAddressMode AddressingMode	  	;	 
	
	I2C_DutyCycle		 DutyCycle			;	
	
}I2c_ConfigType;


ErrorStatus I2C_Init(I2c_ConfigType *Config);

void I2C_MemWrite(I2c_ConfigType *Config , uint8_t SlaveAddress , uint16_t MemAddress ,  uint8_t *Data , uint32_t Size);

void I2C_MasterTransmit(I2c_ConfigType *Config , uint8_t SlaveAddress , uint8_t *Data , uint32_t Size);

void I2C_MasterReceive();

#endif /*I2C_INTERFACE_H*/
