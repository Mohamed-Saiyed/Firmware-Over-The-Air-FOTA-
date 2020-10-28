/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 23 October 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/
#ifndef FPEC_INTERFACE_H
#define FPEC_INTERFACE_H

typedef enum
{
	FLASH_PAGE0  = 0  ,
	FLASH_PAGE1  = 1  ,
	FLASH_PAGE2  = 2  ,
	FLASH_PAGE3  = 3  ,
	FLASH_PAGE4  = 4  ,
	FLASH_PAGE5  = 5  ,
	FLASH_PAGE6  = 6  ,
	FLASH_PAGE7  = 7  ,
	FLASH_PAGE8  = 8  ,
	FLASH_PAGE9  = 9  ,
	FLASH_PAGE10 = 10 ,
	FLASH_PAGE11 = 11 ,
	FLASH_PAGE12 = 12 ,
	FLASH_PAGE13 = 13 ,
	FLASH_PAGE14 = 14 ,
	FLASH_PAGE15 = 15 ,
	FLASH_PAGE16 = 16 ,
	FLASH_PAGE17 = 17 ,
	FLASH_PAGE18 = 18 ,
	FLASH_PAGE19 = 19 ,
	FLASH_PAGE20 = 20 ,
	FLASH_PAGE21 = 21 ,
	FLASH_PAGE22 = 22 ,
	FLASH_PAGE23 = 23 ,
	FLASH_PAGE24 = 24 ,
	FLASH_PAGE25 = 25 ,
	FLASH_PAGE26 = 26 ,
	FLASH_PAGE27 = 27 ,
	FLASH_PAGE28 = 28 ,
	FLASH_PAGE29 = 29 ,
	FLASH_PAGE30 = 30 ,
	FLASH_PAGE31 = 31 ,
	FLASH_PAGE32 = 32 ,
	FLASH_PAGE33 = 33 ,
	FLASH_PAGE34 = 34 ,
	FLASH_PAGE35 = 35 ,
	FLASH_PAGE36 = 36 ,
	FLASH_PAGE37 = 37 ,
	FLASH_PAGE38 = 38 ,
	FLASH_PAGE39 = 39 ,
	FLASH_PAGE40 = 40 ,
	FLASH_PAGE41 = 41 ,
	FLASH_PAGE42 = 42 ,
	FLASH_PAGE43 = 43 ,
	FLASH_PAGE44 = 44 ,
	FLASH_PAGE45 = 45 ,
	FLASH_PAGE46 = 46 ,
	FLASH_PAGE47 = 47 ,
	FLASH_PAGE48 = 48 ,
	FLASH_PAGE49 = 49 ,
	FLASH_PAGE50 = 50 ,
	FLASH_PAGE51 = 51 ,
	FLASH_PAGE52 = 52 ,
	FLASH_PAGE53 = 53 ,
	FLASH_PAGE54 = 54 ,
	FLASH_PAGE55 = 55 ,
	FLASH_PAGE56 = 56 ,
	FLASH_PAGE57 = 57 ,
	FLASH_PAGE58 = 58 ,
    FLASH_PAGE59 = 59 ,
	FLASH_PAGE60 = 60 ,
	FLASH_PAGE61 = 61 ,
	FLASH_PAGE62 = 62 ,
	FLASH_PAGE63 = 63  
	
}FlashPage;

typedef enum
{
	RDP_LEVEL_0 = 0xA5 ,
	RDP_LEVEL_1 = 0x00 
	
}RDP_Level_e;

ErrorStatus FPEC_ProgrammeHalfword(uint32_t Address , uint16_t Data);
/*
*
*
*/

ErrorStatus FPEC_PageErase(FlashPage Page);
/*
*
*
*/
void FPEC_MassErase(void);
/*
*
*
*/
void FPEC_OB_EnableWPR(FlashPage Page);
/*
*
*
*/
void FPEC_OB_RDPLevelConfig(RDP_Level_e RDPLevel);
/*
*
*
*/
RDP_Level_e FPEC_OB_RDPGetLevel(void);
/*
*
*
*/
void FPEC_OB_DisableWPR(FlashPage Page);
/*
*
*
*/
uint32_t FPEC_OB_GetWPR(void);
/*
*
*
*/

#endif	/*FPEC_INTERFACE_H*/
