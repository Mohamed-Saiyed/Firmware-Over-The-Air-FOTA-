/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 23 October 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/
#ifndef FPEC_PRIVATE_H
#define FPEC_PRIVATE_H

#define FPEC_BASE			(0x40022000)

#define OPTION_BYTE_BASE    (0x1FFFF800)

#define FPEC		((FPEC_Typedef *)	FPEC_BASE)
#define OB			((OB_Typedef   *)	OPTION_BYTE_BASE)

#define FLASH_KEY1	(0x45670123)
#define FLASH_KEY2	(0xCDEF89AB)


#define START_OF_FLASH	(0x08000000)
#define END_OF_FLASH	(0x08010000)

typedef struct 
{
	volatile uint32_t ACR	 ;
	volatile uint32_t KEYR   ;
	volatile uint32_t OPTKEYR;
	volatile uint32_t SR	 ;
	volatile uint32_t CR	 ;
	volatile uint32_t AR	 ;
		uint32_t RESERVED	 ;
	volatile uint32_t OBR	 ;
	volatile uint32_t WRPR	 ;

}FPEC_Typedef;

typedef struct 
{
	volatile uint16_t RDP		;
	volatile uint16_t USER		;	
	volatile uint16_t DATA0		;
	volatile uint16_t DATA1		;
	volatile uint16_t WRPR[4]	;
	
}OB_Typedef;

static ErrorStatus VerifyAddress(uint32_t Address);
static void FPEC_UnlockOptionByte(void);
static void FPEC_LockOptionByte(void);
static void FPEC_Unlock(void);
static void FPEC_Lock(void);
static uint16_t BigToLittle_endian(uint16_t Val);

#endif	/*FPEC_PRIVATE_H*/
