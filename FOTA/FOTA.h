#ifndef	_FOTA_H_
#define _FOTA_H_



#define ECU_ID							"0x4A7E"
#define ECU_SOFTWARE_FILE_KEY			"0x4A5E673F"

typedef struct
{
	uint8_t  RecordDataSize;
	uint8_t  RecordType;
	uint16_t RecordAddressLow;
	uint16_t RecordAddressHigh;
	uint16_t RecordData[8];
	uint8_t  RecordCheckSum;
	/*********/
	uint32_t HostCrc;
	uint32_t EcuRecordCrc;
	uint32_t FileCounter;
	
	
}HexFileRecordParameters;

typedef struct 
{
	uint16_t CurrentPage;
	uint16_t CurrentOffset;
	
}FotaEepromParameters;


void GetStringFromTo(uint8_t Buffer[],uint8_t From,uint8_t To,uint8_t OutBuffer[]);
void AsciiToHex(uint8_t* AsciiBuff,uint8_t* HexBuff);
void FOTA_ReadStoredRecord(HexFileRecordParameters* RecordParameters,uint8_t*  RecordDataToRead);
void FOTA_AnalyzeRecord(uint8_t* HexRecord,HexFileRecordParameters* RecordParameters);
void FOTA_StoreRecord(HexFileRecordParameters* RecordParameters);
void FOTA_ParseRecord(uint8_t* RecordToParse);
uint8_t FOTA_GetNewSoftwareStatus(void);
void FOTA_HandleRecord(void);
void FOTA_Dispatcher(void);
void FOTA_JumbToAppArea(void);
void FOTA_Init(void);

void __Fota_SetValidSoftwareFlag(uint8_t Val);

void __Fota_SetNewSoftwareFlag(uint8_t Val);

void __Fota_EreaseAppErea(void);

void __Fota_ReadNewSoftwareVersion(void);

void __Fota_WriteNewSoftwareVersion(void);

void __set_MSP(uint32_t topOfMainStack);

void __Fota_ChangeSoftwareVersion(void);

void __Fota_ReadCurrentSoftwareVersion(void);

#endif /*_FOTA_H_*/