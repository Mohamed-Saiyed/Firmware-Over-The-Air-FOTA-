#include "string.h"
#include "Std_types.h"

#include "RCC_Interface.h"
#include "Systick_Interface.h"
#include "GPIO_interface.h"
#include "FPEC_Interface.h"
#include "UART_interface.h"
#include "ESP_interface.h"
#include "CRC_Interface.h"
#include "I2C_interface.h"
#include "EEPROM.h"
#include "EEPROM_config.h"
#include "NVIC_Private.h"

#include "FOTA.h"
#include "FOTAConfig.h"


#define NEW_SOFTWARE_CHECKING 							0x01
#define NEW_SOFTWARE_AVAILABLE 							0x02
#define NEW_SOFTWARE_GET_RECORD							0x03
#define NEW_SOFTWARE_STORE_RECORD						0x04
#define NEW_SOFTWARE_RECIEVE_FINISH_OK					0x05
#define NEW_SOFTWARE_PARSING_IN_GOING      				0x06
#define NEW_SOFTWARE_DOWNLOAD_FINSIHED_OK				0x07






HexFileRecordParameters NewRecord = {0};
FotaEepromParameters EepromParameters;
uint8_t NewSoftwareStatus = NEW_SOFTWARE_CHECKING;
static uint8_t CurrentSoftwareVersion[10];
uint8_t NewVersion[10];






void __set_MSP(uint32_t topOfMainStack)
{
  register uint32_t __regMainStackPointer     __asm("msp");
  __regMainStackPointer = topOfMainStack;
}


void __Fota_SetValidSoftwareFlag(uint8_t Val)
{
	uint16_t Page = NUM_OF_PAGES - 1 ,Offset =1 ;
	uint8_t ValidInstalledSw = Val;
	Eeprom_write(&Page,&Offset,&ValidInstalledSw,1);
}	


void __Fota_SetNewSoftwareFlag(uint8_t Val)
{
	uint16_t Page = NUM_OF_PAGES - 1 ,Offset =0 ;
	uint8_t NewSw = Val;
	Eeprom_write(&Page,&Offset,&NewSw,1);
}	

void __Fota_WriteNewSoftwareVersion(void)
{
	uint16_t Page = NUM_OF_PAGES - 1 ,Offset = 2 ;
	Eeprom_write(&Page,&Offset,NewVersion,5);
}	

void __Fota_ReadNewSoftwareVersion(void)
{
	uint16_t Page = NUM_OF_PAGES - 1 ,Offset = 2 ;
	Eeprom_Read(&Page,&Offset,NewVersion,5);
}	

void __Fota_ReadCurrentSoftwareVersion(void)
{
	uint16_t Page = NUM_OF_PAGES - 1 ,Offset = 8 ;
	Eeprom_Read(&Page,&Offset,CurrentSoftwareVersion,5);
}	


void __Fota_ChangeSoftwareVersion(void)
{
	uint16_t Page = NUM_OF_PAGES - 1 ,Offset = 8 ;
	Eeprom_write(&Page,&Offset,NewVersion,5);
	strcpy(CurrentSoftwareVersion,NewVersion);
}	


void __Fota_EreaseAppErea(void)
{
	uint16_t NumOfPageToBeEreased = (FOTA_APP_END_PAGE - FOTA_APP_START_PAGE) + 1;
	for(uint16_t LocalIndex = 0 ; LocalIndex < NumOfPageToBeEreased; LocalIndex++)
	{
		FPEC_PageErase(FOTA_APP_START_PAGE + LocalIndex);
	}
	
}
void FOTA_CheckNewSoftwareParametersEeprom(uint8_t* New_SW,uint8_t* ValidInstalledSw)
{
	uint16_t Page =NUM_OF_PAGES-1 ,Offset =0 ;
	Eeprom_Read(&Page,&Offset,New_SW,1);
	Eeprom_Read(&Page,&Offset,ValidInstalledSw,1);
}


void FOTA_Init(void)
{
	NewRecord.FileCounter = 0x01;
	EepromParameters.CurrentPage = 0;
	EepromParameters.CurrentOffset = 0;
		
	
	ESP_Init();	
	ESP_NetworkConnect();
	EEPROM_Init();
	__Fota_ReadCurrentSoftwareVersion();

}


void FOTA_Dispatcher(void)
{

	uint8_t ParseRecord[22]		= {0};
	uint8_t New_SW          	= 0;
	uint8_t ValidInstalledSw	= 0;
	
	switch(NewSoftwareStatus)
	{
		case NEW_SOFTWARE_CHECKING:
		
			FOTA_CheckNewSoftwareParametersEeprom(&New_SW,&ValidInstalledSw);
			
			if(New_SW == 0x24)
			{
				__Fota_ReadNewSoftwareVersion();
				NewSoftwareStatus = NEW_SOFTWARE_AVAILABLE;
			}
			else if(ValidInstalledSw == 0x11)
			{
				FOTA_JumbToAppArea();
			}
			else
			{
				uint8_t x = FOTA_GetNewSoftwareStatus();
				if(x)
				{
					NewSoftwareStatus = NEW_SOFTWARE_AVAILABLE;
				}
			}
			
		break;
		case NEW_SOFTWARE_AVAILABLE:
			
			FOTA_HandleRecord();
			/*CheckCRC*/
			if(NewRecord.EcuRecordCrc == NewRecord.HostCrc)
			{
				NewSoftwareStatus = NEW_SOFTWARE_STORE_RECORD;
			}
			else
			{
				
			}
		
		break;
		case NEW_SOFTWARE_STORE_RECORD:

			/*Store the Record Data*/
			
			if(NewRecord.RecordType == 0x00 || NewRecord.RecordType == 0x01)
			{
				FOTA_StoreRecord(&NewRecord);
			}
			
			if(NewRecord.RecordType == 0x01)
			{
				EepromParameters.CurrentPage = 0;
				EepromParameters.CurrentOffset = 0;
				NewSoftwareStatus = NEW_SOFTWARE_RECIEVE_FINISH_OK;
			}
			else
			{
				NewSoftwareStatus = NEW_SOFTWARE_AVAILABLE;	
			}
			
		break;
		case NEW_SOFTWARE_RECIEVE_FINISH_OK:
			
			__Fota_EreaseAppErea();
			__Fota_SetValidSoftwareFlag(FALSE);
	
			NewSoftwareStatus = NEW_SOFTWARE_PARSING_IN_GOING;
			
		
		break;
		case NEW_SOFTWARE_PARSING_IN_GOING:
		
			FOTA_ReadStoredRecord(&NewRecord,ParseRecord);
		
			if(ParseRecord[1] != 0x01)
			{
				FOTA_ParseRecord(ParseRecord);
			}
			else if(ParseRecord[1] == 0x01)
			{
				NewSoftwareStatus =	NEW_SOFTWARE_DOWNLOAD_FINSIHED_OK;
			}
			
		break;
		case NEW_SOFTWARE_DOWNLOAD_FINSIHED_OK:
			
			__Fota_SetValidSoftwareFlag(0x11);
			__Fota_SetNewSoftwareFlag(0x21);
			__Fota_WriteNewSoftwareVersion();
		__Fota_ChangeSoftwareVersion();
		
			FOTA_JumbToAppArea();
			
		break;
	
	}
		
		
}


void FOTA_JumbToAppArea(void)
{
	void (*ApplicationResetHandler)(void);
	
	SCB->VTOR = FOTA_APP_FLASH_BASE;
	
	uint32_t AppResetHandler = *(volatile uint32_t *)FOTA_APP_RESET_HANDLER_BASE;
	
	uint32_t MSP_value = *(volatile uint32_t *)FOTA_APP_FLASH_BASE;
	
	__set_MSP(MSP_value);
	
	/* shift vector table */
	
	ApplicationResetHandler = (void*)AppResetHandler;
	
	ApplicationResetHandler();
}

uint8_t FOTA_GetNewSoftwareStatus(void)
{
	uint8_t ReceiveBuff[50];
	uint8_t TransmitBuffer[250];
	uint8_t RecordStatus= 0 , RetVal = 0;
				
	ESP_ServerConnect(FOTA_SERVER_IP,FOTA_SERVER_PORT);	
	sprintf(TransmitBuffer,"GET http://%s:%s/ValidationParameters?EcuId=%s&Key=%s&CurrentVersion=%s&RecordStatus=%d&HexFileCounter=%d\r\n",\
			FOTA_SERVER_IP,FOTA_SERVER_PORT,ECU_ID,ECU_SOFTWARE_FILE_KEY,CurrentSoftwareVersion,RecordStatus,NewRecord.FileCounter);	
	ESP_SendData(TransmitBuffer,strlen(TransmitBuffer)+2);
	ESP_Receive(ReceiveBuff);
	
	if(Find_string(ReceiveBuff,50,"true",4))
	{
		GetStringFromTo(ReceiveBuff,'_','C',NewVersion);
		RetVal = 1;
		//NewSoftwareStatus = NEW_SOFTWARE_AVAILABLE;
	}
	
	return RetVal;
		
}

void FOTA_HandleRecord(void)
{
	uint8_t ReceiveBuff[300];
	uint8_t TransmitBuffer[250];
	uint8_t RecordStatus = 1;
	
	ESP_ServerConnect(FOTA_SERVER_IP,FOTA_SERVER_PORT);	
	sprintf(TransmitBuffer,"GET http://%s:%s/ValidationParameters?EcuId=%s&Key=%s&CurrentVersion=%s&RecordStatus=%d&HexFileCounter=%d\r\n",\
			FOTA_SERVER_IP,FOTA_SERVER_PORT,ECU_ID,ECU_SOFTWARE_FILE_KEY,CurrentSoftwareVersion,RecordStatus,NewRecord.FileCounter);
	ESP_SendData(TransmitBuffer,strlen(TransmitBuffer)+2);
	ESP_Receive(ReceiveBuff);
	FOTA_AnalyzeRecord(ReceiveBuff,&NewRecord);	
}
 
void FOTA_ParseRecord(uint8_t* RecordToParse)
{
	uint16_t HalfWordDataToParse = 0;
	uint32_t RecordAddress  = 0;
	uint8_t  RecordDataSize = RecordToParse[0] / 4;
	
	
	uint8_t i = 24;
	for(uint8_t LocalIndex = 2 ; LocalIndex < 6 ; LocalIndex++)
	{
		RecordAddress |= RecordToParse[LocalIndex] << i;
		i-=8;
	}
	for(uint8_t  LocalIndex = 0,DataIndex = 6; LocalIndex < RecordDataSize; LocalIndex++,DataIndex+=2)
	{
		HalfWordDataToParse = (RecordToParse[DataIndex+1] << 8) | RecordToParse[DataIndex];
		FPEC_ProgrammeHalfword(RecordAddress,HalfWordDataToParse);
		RecordAddress +=2;
	}
	
	
}


void FOTA_AnalyzeRecord(uint8_t* RecievedBuffer,HexFileRecordParameters* RecordParameters)
{
	uint32_t LocalIndex = 0;
	uint8_t  RecordInAscii[50] = {0},HostCrcInAscii[20] = {0},HexFileCounterInAscii[10] = {0};
	uint8_t  RecordInHex[50] = {0},HostCrcInHex[20] = {0},HexFileCounterInHex[10] = {0};
	
	GetStringFromTo(RecievedBuffer,'#','=',RecordInAscii);
	GetStringFromTo(RecievedBuffer,'=','+',HostCrcInAscii);
	GetStringFromTo(RecievedBuffer,'+','C',HexFileCounterInAscii);
	
	AsciiToHex(RecordInAscii,RecordInHex);
	AsciiToHex(HostCrcInAscii,HostCrcInHex);
	AsciiToHex(HexFileCounterInAscii,HexFileCounterInHex);

	RecordParameters->FileCounter = 0;
	RecordParameters->RecordAddressLow = 0;
	RecordParameters->RecordDataSize = 0;
	RecordParameters->RecordType = 0;
	RecordParameters->HostCrc = 0;
	RecordParameters->EcuRecordCrc = 0;
	RecordParameters->RecordCheckSum = 0;
	
	
	RecordParameters->RecordDataSize = ((RecordInHex[LocalIndex] << 4) | RecordInHex[LocalIndex+1]) * 2;
	RecordParameters->RecordType = (RecordInHex[6] << 4) | RecordInHex[7];
	
	if(RecordParameters->RecordType == 0x04)
	{
		int i = 12;
		for(LocalIndex = 8 ; LocalIndex < 12 ; LocalIndex++)
		{
			RecordParameters->RecordAddressHigh |= RecordInHex[LocalIndex] << i;
			i-=4;
		}
		
	}
	else if(RecordParameters->RecordType == 0x00)
	{
		int i = 12;
		LocalIndex++;		
		for(LocalIndex = 2 ; LocalIndex < 6 ; LocalIndex++)
		{
			RecordParameters->RecordAddressLow |= RecordInHex[LocalIndex] << i;
			i-=4;
		}
		
	    LocalIndex+=2;
		for(uint8_t DataIndex = 0 ; DataIndex < (RecordParameters->RecordDataSize) / 4 ; DataIndex++)
		{
			RecordParameters->RecordData[DataIndex] = RecordInHex[LocalIndex] << 12 | RecordInHex[LocalIndex+1] << 8 |
										              RecordInHex[LocalIndex+2] << 4  | RecordInHex[LocalIndex+3] << 0 ;
					  
			LocalIndex+=4;
		}
		
	}
	else if(RecordParameters->RecordType == 0x01)
	{

	}
	else
	{
		
	}
	
	RecordParameters->EcuRecordCrc = CRC_ACCUMULAT(CRC1,RecordParameters->RecordData,(RecordParameters->RecordDataSize)/4);
	
	RecordParameters->RecordCheckSum = (RecordInHex[LocalIndex] << 4) | RecordInHex[LocalIndex+1];
	/*Get Host Crc*/
	LocalIndex = 0;
	while(HostCrcInAscii[LocalIndex] != '\0')
	{
		RecordParameters->HostCrc = ((RecordParameters->HostCrc << 4)| HostCrcInHex[LocalIndex++]);
	}
	/*Get HexFile Counter*/
	LocalIndex = 0;
	
	while(HexFileCounterInAscii[LocalIndex] != '\0')
	{
		RecordParameters->FileCounter = ((RecordParameters->FileCounter << 4)| HexFileCounterInHex[LocalIndex++]);
	}
	
	
}


void FOTA_StoreRecord(HexFileRecordParameters* RecordParameters)
{
	uint32_t LocalIndex = 0 ;
	uint8_t  RecordDataToStore[22] = {0};
	
	/*Store only The Record Address*/
	RecordDataToStore[LocalIndex++] = (RecordParameters->RecordDataSize);
	RecordDataToStore[LocalIndex++] = (RecordParameters->RecordType);
	RecordDataToStore[LocalIndex++] = (RecordParameters->RecordAddressHigh & 0xFF00) >> 8;
	RecordDataToStore[LocalIndex++] = (RecordParameters->RecordAddressHigh & 0x00FF);
	RecordDataToStore[LocalIndex++] = (RecordParameters->RecordAddressLow & 0xFF00)  >> 8;
	RecordDataToStore[LocalIndex++] = (RecordParameters->RecordAddressLow & 0x00FF);
	
	for(uint8_t DataIndex = 0 ; DataIndex < (RecordParameters->RecordDataSize) / 4 ; LocalIndex+=2,DataIndex++)
	{ 
		RecordDataToStore[LocalIndex]   =  (RecordParameters->RecordData[DataIndex] & 0xFF00) >> 8;
		RecordDataToStore[LocalIndex+1] =  (RecordParameters->RecordData[DataIndex] & 0x00FF);
		
	}

	Eeprom_write(&EepromParameters.CurrentPage,&EepromParameters.CurrentOffset,RecordDataToStore,LocalIndex);
	
}

void FOTA_ReadStoredRecord(HexFileRecordParameters* RecordParameters,uint8_t*  RecordDataToRead)
{
	
	Eeprom_Read(&EepromParameters.CurrentPage,&EepromParameters.CurrentOffset,RecordDataToRead,6);
	Eeprom_Read(&EepromParameters.CurrentPage,&EepromParameters.CurrentOffset,&RecordDataToRead[6],RecordDataToRead[0]/2);

}

void GetStringFromTo(uint8_t Buffer[],uint8_t From,uint8_t To,uint8_t OutBuffer[])
{
	uint8_t OriginalIndex = 0;
	uint8_t CopyIndex = 0;
	while((Buffer[OriginalIndex] != From) && (Buffer[OriginalIndex] != '\0'))
	{
		OriginalIndex++;
	}

	OriginalIndex++;
	
	while((Buffer[OriginalIndex] != To) && (Buffer[OriginalIndex] != '\0'))
	{
		OutBuffer[CopyIndex++] = Buffer[OriginalIndex++];
	}
	OutBuffer[CopyIndex] = '\0';
	

}

void AsciiToHex(uint8_t* AsciiBuff,uint8_t* HexBuff)
{
	uint8_t LocalIndex = 0;
	while((AsciiBuff[LocalIndex] != '\0'))
	{
		if(AsciiBuff[LocalIndex] >= 0x30 && AsciiBuff[LocalIndex] <= 0x39)
		{
			HexBuff[LocalIndex] = AsciiBuff[LocalIndex] - 0x30;
		}
		else if(AsciiBuff[LocalIndex] >= 0x61 && AsciiBuff[LocalIndex] <= 0x66)
		{
			HexBuff[LocalIndex] = AsciiBuff[LocalIndex] - 0x57;
		}
		else
		{
			HexBuff[LocalIndex] = AsciiBuff[LocalIndex] - 0x37;
		}
		LocalIndex++;
	}

}


