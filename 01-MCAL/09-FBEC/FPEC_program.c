/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 23 October 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/
#include "Std_types.h"
#include "BIT_MATH.h"

#include "FPEC_interface.h"
#include "FPEC_private.h"
#include "FPEC_config.h"

ErrorStatus FPEC_PageErase(FlashPage Page)
{
	/*Temp Variable to store  the function state*/
	ErrorStatus State   = E_OK;
	/*Temp variable to caluclate the Page Address*/
	uint32_t Local_Temp = 0   ;
	/*check for the page number*/
	if(Page > FLASH_PAGE63)
	{
		State = E_NOK;
	}
	else
	{
		/*wait for the busy flag before any operation*/
		while(BIT_IS_SET(FPEC->SR , 0));
		/*Unlock the Flash controller*/
		FPEC_Unlock();
		/*Enable the page erase bit in the FPEC control Register*/
		SET_BIT(FPEC->CR , 1);
		/*Claulate and store the page base address*/
		/*the Page size == 1024KB starting from the Start of the flash(0x08000000)*/
		Local_Temp = ((Page * 1024) + START_OF_FLASH);
		/*Put the Page Address in the the Flash address Register to Be deleted accordding to the data sheet*/
		FPEC->AR = Local_Temp ;
		/*Start the Earse operation*/
		SET_BIT(FPEC->CR , 6);
		/*wait for the bussy Flag till the operation finshs*/
		while(BIT_IS_SET(FPEC->SR , 0));
		
		/*Clear the end of opreation(EOP) Flag in the status register*/
		SET_BIT(FPEC->SR , 5);
		/*Clear the page erase  Activation bit*/
		CLR_BIT(FPEC->CR , 1);
		/*Lock the Flash again*/
		FPEC_Lock();
	
	}
	
	return State ;
	
}

void FPEC_MassErase(void)
{
	/*wait for the busy flag before any operation*/
	while(BIT_IS_SET(FPEC->SR , 0));
	/*Unlock the Flash controller*/
	FPEC_Unlock();
	/*Enable the Mass erase bit in the FPEC control Register*/
	SET_BIT(FPEC->CR , 2);
	/*Start the Earse operation*/
	SET_BIT(FPEC->CR , 6);
	/*wait for the bussy Flag till the operation finshs*/
	while(BIT_IS_SET(FPEC->SR , 0));
	/*Clear the end of opreation(EOP) Flag in the status register*/	
	SET_BIT(FPEC->SR , 5);
	/*Clear the Mase erase Activation bit*/
	CLR_BIT(FPEC->CR , 2);
	/*Lock the Flash again*/
	FPEC_Lock();

}

ErrorStatus FPEC_ProgrammeHalfword(uint32_t Address , uint16_t Data)
{
	/*Temp Variable to store  the function state*/
	ErrorStatus State;
	/*Check for the passed address*/
	if(VerifyAddress(Address) == E_OK)
	{
		/*wait for the busy flag before any operation*/
		while(BIT_IS_SET(FPEC->SR , 0));
		/*Unlock the Flash controller*/	
		FPEC_Unlock();
		/*Loop in the size of data the user wants to programme*/
	
		/*GO into flash programming mode*/
		SET_BIT(FPEC->CR , 0);
		/*put the Data int the current address*/
		*((volatile uint16_t *) Address) = Data;
		/*wait for the bussy Flag till the operation finshs*/
		while(BIT_IS_SET(FPEC->SR , 0));
		
		/*Clear the end of opreation(EOP) Flag in the status register*/	
		SET_BIT(FPEC->SR , 5);
		/*Step out from flash programming mode */
		CLR_BIT(FPEC->CR , 0);
		
		
		/*Lock the Flash again*/
		FPEC_Lock();
		/*put the Errorstatus state as OK*/
		State = E_OK;
	}
	else
	{
		/*if the address is not vaild put the status as NOT OK*/
		State = E_NOK;
	}
	
	/*return function state*/
	return State ;
	
}

void FPEC_OB_RDPLevelConfig(RDP_Level_e RDPLevel)
{
	/*first store the read protection level before working */
	volatile RDP_Level_e Temp_RDPLevel  = RDPLevel;
	/*wait for the busy flag before any operation*/
	while(BIT_IS_SET(FPEC->SR , 0));
	/*Unlock the Flash controller*/	
	FPEC_Unlock();
	/*Unlock the Flash OptionByte controller*/	
	FPEC_UnlockOptionByte();
	
	/*Before setting the flash Read protection level .. erase the option bytes*/
	
	/*Enable option byte erase bit*/
	SET_BIT(FPEC->CR, 5);
	/*Start the erase operation*/
	SET_BIT(FPEC->CR, 6);
	/*wait for the bussy Flag till the operation finshs*/
	while(BIT_IS_SET(FPEC->SR , 0));
	
	/**then set the read protection level**/
	
	/*Disable the option byte erase option after erasing*/
	CLR_BIT(FPEC->CR, 5);
    /*Set the option programming mode*/
	SET_BIT(FPEC->CR, 4);
	/*Put the read protection level into the Option byte read protection register */
	OB->RDP = Temp_RDPLevel ;
	/*Clear the option programming mode*/
	CLR_BIT(FPEC->CR, 4);
	
	/*Lock the Flash again*/
	FPEC_Lock();
	/*Unlock the Flash OptionByte controller*/	
	FPEC_LockOptionByte();
		
}

uint32_t FPEC_OB_GetWPR(void)
{
	/*Store the flash pages write protection register into a Local Vaiable*/
	/*flash WRPR is 32-bit rigster its reset value is 0xFFFFFFFF and each 8-bit show the statu of WPR[x] reg
	in option byte*/
	uint32_t RetVal = FPEC->WRPR ;
	
	return RetVal ;
}

void FPEC_OB_DisableWPR(FlashPage Page)
{
	/*local variable to select an array index*/
	uint8_t WriteProtectionIndex =  0  ;
	/*local temp variable to store the current Write protection value*/
    uint32_t WriteProtectionPages =  0  ;	
	/*each Write protection register has its own variable */
	uint32_t WPR[4]	  = {0} ;
	
	/*to protect the page you have to set its own bit as 0*/
	/*each page protect 3 other pages as follow (bit 0 for the first four pages and bit 1 for the next four pages and so on)
	so making Page >> 2 so change its value every +4 for ex : 1 << 0 is responsible for the first 4 pages and 1 << 1 its  responsible for the second 4 pages*/
	/*get the OB WPR register values before erasing the OB*/
	/*then oring 1 to it at the location of the protected bit make it unprotected*/
	WriteProtectionPages = (FPEC_OB_GetWPR() | (1 << (Page >> 2)));
	
	/*Store the status of each optoij byte WPR register before erasing the option byte 
	so you avoi over writting*/
	WPR[0] =	(WriteProtectionPages  & (0x000000FF)); 		
	WPR[1] =	((WriteProtectionPages & (0x0000FF00)) >> 8 );
	WPR[2] =	((WriteProtectionPages & (0x00FF0000)) >> 16 );  
	WPR[3] =	((WriteProtectionPages & (0xFF000000)) >> 24 );		
	
    /*erase the option byte before any new opration*/
    FLASH_OB_Erase();
	/*wait for the busy flag*/
	while(BIT_IS_SET(FPEC->SR , 0));
	/*unlock the flash interface*/
	FPEC_Unlock();
	/*then unlock the option byte*/
	FPEC_UnlockOptionByte();
	/*Enable option byte programming*/
	SET_BIT(FPEC->CR , 9);
	/*go to the next register every 8 digits*/
	/*index 0 is for bits 1-->8 that means index 0 is responsible for 32 page*/
	WriteProtectionIndex = Page >> 3 ;
	
	/*Lop on the 4 WPR register and store into it its value before earsing the OB and store the new value*/
	for(uint8_t Local_Index = 0 ; Local_Index < 4 ; Local_Index++)
	{
		if((uint8_t)WPR[Local_Index] != 0xFF)
		{
			OB->WRPR[Local_Index] = (uint8_t)WPR[Local_Index];
			/*wait for the bussy Flag till the operation finshs*/
			while(BIT_IS_SET(FPEC->SR , 0));
		}
		else
		{
			/*Do Nothing*/
		}
		
	}
		
    /*Lock the Flash again*/
	FPEC_Lock();
	/*Unlock the Flash OptionByte controller*/
	FPEC_LockOptionByte();
	
}

void FPEC_OB_EnableWPR(FlashPage Page)
{
	/*local variable to select an array index*/
    uint8_t WriteProtectionIndex =  0  ;
	/*local temp variable to store the current Write protection value*/
    uint32_t WriteProtectionPages =  0  ;	
	/*each Write protection register has its own variable */
	uint32_t WPR[4]	  = {0} ;
	
	/*to protect the page you have to set its own bit as 0*/
	/*The WPR Regstir is 16-bit just 8 bits is used for protection and its reset value is (0xFF) so te be able to put a 0 for example into the first bit 
	so you have to ~WPR first and then | (1) , so the its value will be 0x01 and then do ~ for the WPR register again so its value will be (0xFE) 
	that means we put a zero on the first bit with out any change to other bits*/
	/*each page protect 3 other pages as follow (bit 0 for the first four pages and bit 1 for the next four pages and so on)
	so making Page >> 2 so change its value every +4 for ex : 1 << 0 is responsible for the first 4 pages and 1 << 1 its  responsible for the second 4 pages*/
	WriteProtectionPages = ~(((~FPEC_OB_GetWPR()) | (1 << (Page >> 2) )));
	
	/*Store the status of each optoij byte WPR register before erasing the option byte 
	so you avoi over writting*/
	WPR[0] =	(WriteProtectionPages  & (0x000000FF)); 		
	WPR[1] =	((WriteProtectionPages & (0x0000FF00)) >> 8 );
	WPR[2] =	((WriteProtectionPages & (0x00FF0000)) >> 16 );  
	WPR[3] =	((WriteProtectionPages & (0xFF000000)) >> 24 );		
	
    /*erase the option byte before any new opration*/
    FLASH_OB_Erase();
	/*wait for the busy flag*/
	while(BIT_IS_SET(FPEC->SR , 0));
	/*unlock the flash interface*/
	FPEC_Unlock();
	/*then unlock the option byte*/
	FPEC_UnlockOptionByte();
	/*Enable option byte programming*/
	SET_BIT(FPEC->CR , 9);
	/*go to the next register every 8 digits*/
	/*index 0 is for bits 1-->8 that means index 0 is responsible for 32 page*/
	WriteProtectionIndex = Page >> 3 ;
	
	/*Lop on the 4 WPR register and store into it its value before earsing the OB and store the new value*/
	for(uint8_t Local_Index = 0 ; Local_Index < 4 ; Local_Index++)
	{
		if((uint8_t)WPR[Local_Index] != 0xFF)
		{
			OB->WRPR[Local_Index] = (uint8_t)WPR[Local_Index];
		    /*wait for the bussy Flag till the operation finshs*/
			while(BIT_IS_SET(FPEC->SR , 0));
		}
		else
		{
			/*Do Nothing*/
		}
		
	}
		
    /*Lock the Flash again*/
	FPEC_Lock();
	/*Unlock the Flash OptionByte controller*/
	FPEC_LockOptionByte();
		
}

void FLASH_OB_Erase(void)
{
	/*Store the current Read protection level before erasing the option byte to restore it*/
	RDP_Level_e RDPLevel = FPEC_OB_RDPGetLevel();
	/*wait for the busy Flag*/	
	while(BIT_IS_SET(FPEC->SR , 0));
	/*Unlock the Flash controller*/	
	FPEC_Unlock();
	/*Unlock the Flash OptionByte controller*/
	FPEC_UnlockOptionByte();
	/*Set the option byte erase enable bit*/
	SET_BIT(FPEC->CR, 5);
	/*Trigger the erase opration by setting the start bit*/
    SET_BIT(FPEC->CR, 6);
	/*wait for the bussy Flag till the operation finshs*/
	while(BIT_IS_SET(FPEC->SR , 0));
	/*clear the option byte erase enable bit*/
	CLR_BIT(FPEC->CR, 5);
	/*after erasing the option byte restore the read protection level*/
	FPEC_OB_RDPLevelConfig(RDPLevel);
	/*Lock the Flash again*/
	FPEC_Lock();
	/*Unlock the Flash OptionByte controller*/
	FPEC_LockOptionByte();
	

}

RDP_Level_e FPEC_OB_RDPGetLevel(void)
{
	/*temp variable to store the current read protection level*/
	uint8_t Local_RDP_Level = 0 ;
	
	/*the default Read protection level is 0*/
	RDP_Level_e RDP_Level   = RDP_LEVEL_0 ;
	/*GEt the read protection level from the option byte register of the flash interface*/
	Local_RDP_Level = GET_BIT(FPEC->OBR , 1);
	/*if the bit is set so the the memory is read protected*/
	if(Local_RDP_Level == 1)
	{
		RDP_Level = RDP_LEVEL_1 ;
	}
	/*else there is no read protection on the memory*/
	else
	{
		RDP_Level = RDP_LEVEL_0 ;
	}
	
	return RDP_Level ;
	
}

/**********************************************************/
/*
*
helper functino to check if the address passed is at the range of the the ECU flash or Not
*
*/
static ErrorStatus VerifyAddress(uint32_t Address)
{
	ErrorStatus State;
	
	if((Address < START_OF_FLASH) || (Address >END_OF_FLASH))
	{
		State = E_NOK;
	}
	else
	{
		State =E_OK;		
	}
	
	return State ;
}

/*
static helper function to unlock the option byte
*/
static void FPEC_UnlockOptionByte(void)
{
	if(BIT_IS_CLEAR(FPEC->CR , 9))
	{	
		FPEC->OPTKEYR = FLASH_KEY1 ;
		
		FPEC->OPTKEYR = FLASH_KEY2 ;
	}
	else
	{
		/*Do Nothing*/
	}
	
}

/*
static helper function to lock the option byte
*/
static void FPEC_LockOptionByte(void)
{
	if(BIT_IS_SET(FPEC->CR , 9))
	{
		CLR_BIT(FPEC->CR , 9);
	}
	else
	{
		/*Do Nothing*/
	}
	
}

/*
static helper function to unlock Flash interface
*/
static void FPEC_Unlock(void)
{
	if(BIT_IS_SET(FPEC->CR , 7))
	{	
		FPEC->KEYR = FLASH_KEY1 ;
		
		FPEC->KEYR = FLASH_KEY2 ;
	}
	else
	{
		/*Do Nothing*/
	}
	
}

/*
static helper function to the  lock Flash interface
*/
static void FPEC_Lock(void)
{
	if(BIT_IS_CLEAR(FPEC->CR , 7))
	{
		SET_BIT(FPEC->CR , 7);
	}
	else
	{
		/*Do Nothing*/
	}
	
}

/*helper function to convert a big endian 16-bit value to little endian */
static uint16_t BigToLittle_endian(uint16_t Val)
{
	return (((Val>>8)  & 0x00FF) |
	        ((Val<<8)  & 0xFF00));

}
