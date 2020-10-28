/*********************************************************/
/* Author	: Mohamed sayed								 */
/* Date 	: 20 October 2020	    					 */		
/* Version  : V01										 */	
/*********************************************************/
#include "Std_types.h"
#include "BIT_MATH.h"

#include "UART_interface.h"

#include "ESP_interface.h"
#include "ESP_private.h"
#include "ESP_config.h"


static Uart_ConfigType UART ;
static uint8_t ESP_RX_Buffer[ESP_MAX_RX_BUFFER_SIZE];
static uint32_t ESP_BufferCounter ; 

/*CallBack function to receive the data from the ESP*/
void ESP_CallBack(void)
{
	/*Store the crrent byte into the receiving buffer*/
	ESP_RX_Buffer[ESP_BufferCounter] = (uint8_t)USART1->DR ;
	/*incremnt the buffer counter*/
	ESP_BufferCounter++;
	/*reset the buffer counter if it reachs the max receiving buffer size*/
	if(ESP_BufferCounter >= ESP_MAX_RX_BUFFER_SIZE)
	{
		ESP_BufferCounter = 0	;
	}
	else
	{
		/*Do Nothing*/
	}
	
}


void UartEsp_init(void)
{
	
	UART.USARTx     = ESP_USART_CHANNEL 				;
	UART.Id         = ESP_USART_CHANNEL_ID 		    	;
	UART.BaudRate   = ESP_BAUD_RATE      				;
	UART.Parity     = UART_PARITY_BIT_NONE			 	;
	UART.Mode       = UART_MODE_TX_RX 					;	
	UART.StopBits   = UART_STOP_BIT_1BIT				;
	UART.WordLenght = UART_WORD_LENGHT_8BIT			    ;
	UART_Init(&UART)									;	
	
}

ErrorStatus ESP_Init(void)
{
	/*temp variable to store function status*/
	uint8_t Status         = E_OK;
	/*temp variable to count the timeout*/
	uint32_t Local_TimeOut = 0   ;
	/*temp variable to check for the max time out*/
	uint8_t  Local_MaxTime = 0   ;
	
	/*initialize the esp Uart channel*/
	UartEsp_init();
	/*set the the uart receiving call back function*/
	UART_SetCallBack(ESP_USART_CHANNEL_ID , ESP_CallBack , RECEIVE_INTERRUPT);
	/*Enable the uart channel RX interrupt*/
	UART_EnableInterrupt(ESP_USART_CHANNEL , RECEIVE_INTERRUPT);
	/*command to Disable the ESP echo*/
	UART_TransmitSynchronous(ESP_USART_CHANNEL , "ATE0\r\n");
	/*wait until the esp responds with OK*/
	while(Find_string(ESP_RX_Buffer , "OK") == 0) 
	{
	  /*increment the time out counter*/
	  Local_TimeOut++;
	  /*check if it the time out reachs the maximum time out*/
	  if(Local_TimeOut == ESP_MAX_RX_TIMEOUT)
	  {
		  /*time out reachs the maximum time out reset the time out counter*/
		  Local_TimeOut = 0 ;
		  /*increment the repeat receiving counter*/
		  Local_MaxTime++;
		  
		  if(Local_MaxTime == ESP_MAX_TIME_COUNT)
		  {
			  /*when it reachs the maximum number of command repeat sending without any response 
			    but the status as timeout error and break the loop	  */
			  Status = E_TIMEOUT ;
			  break;
		  }
		  else
		  {
			/*Reset esp receving buffer*/
			Reset_Buffer();
			/*Send the same command again */
			UART_TransmitSynchronous(ESP_USART_CHANNEL , "ATE0\r\n");
		  }
	  }
		  
	}
	/*Reset the local variable to be used again in the next command*/
    Local_TimeOut = 0 ;
	Local_MaxTime = 0 ;
	
	/*Reset esp receving buffer*/
    Reset_Buffer();
	
	/*command to Set the ESP Mode as station mode*/
    UART_TransmitSynchronous(ESP_USART_CHANNEL , "AT+CWMODE=1\r\n");
	
	/*wait until the esp responds with OK*/
	while(Find_string(ESP_RX_Buffer , "OK") == 0) 
	{
	  /*increment the time out counter*/
	  Local_TimeOut++;
	  
	  if(Local_TimeOut == ESP_MAX_RX_TIMEOUT)
	  {
		  /*time out reachs the maximum time out reset the time out counter*/
		  Local_TimeOut = 0 ;
		  /*increment the repeat receiving counter*/
		  Local_MaxTime++;
		  
		  if(Local_MaxTime == ESP_MAX_TIME_COUNT)
		  {
			  /*when it reachs the maximum number of command repeat sending without any response 
			    but the status as timeout error and break the loop	  */
			  Status = E_TIMEOUT ;
			  break;
		  }
		  else
		  {
			/*Reset esp receving buffer*/
			Reset_Buffer();
			/*Send the same command again */
			UART_TransmitSynchronous(ESP_USART_CHANNEL , "AT+CWMODE=1\r\n");
		  }
	  }
		  
	}
	
	Reset_Buffer();
	
	return Status;
}

ErrorStatus ESP_NetworkConnect(uint8_t *NetworkName , uint8_t *Password)
{
	/*temp variable to store function status*/
	uint8_t Status         = E_OK;
	/*temp variable to count the timeout*/
	uint32_t Local_TimeOut = 0   ;
	/*temp variable to check for the max time out*/
	uint8_t  Local_MaxTime = 0   ;
	
	/*Send command to connect the esp to wifi netwrok*/
	UART_TransmitSynchronous(ESP_USART_CHANNEL , "AT+CWJAP_CUR=");
	UART_TransmitSynchronous(ESP_USART_CHANNEL , "\"");
	UART_TransmitSynchronous(ESP_USART_CHANNEL , NetworkName);
	UART_TransmitSynchronous(ESP_USART_CHANNEL , "\"");
	UART_TransmitSynchronous(ESP_USART_CHANNEL , ",");
	UART_TransmitSynchronous(ESP_USART_CHANNEL , "\"");
	UART_TransmitSynchronous(ESP_USART_CHANNEL , Password);
	UART_TransmitSynchronous(ESP_USART_CHANNEL , "\"");
	UART_TransmitSynchronous(ESP_USART_CHANNEL , "\r\n");
	
	/*wait until the esp responds with OK or respond with CONNECT*/
	while(Find_string(ESP_RX_Buffer , "IP") == 0) 
	{
	  /*increment the time out counter*/
		Local_TimeOut++;  
		  
		if(Local_TimeOut == ESP_MAX_RX_TIMEOUT)  
		{  
		  /*time out reachs the maximum time out reset the time out counter*/  
		  Local_TimeOut = 0 ;  
		  /*increment the repeat receiving counter*/  
		  Local_MaxTime++;  
		    
		  if(Local_MaxTime == ESP_MAX_TIME_COUNT)  
		  {  
			  /*when it reachs the maximum number of command repeat sending without any response  
			    but the status as timeout error and break the loop	  */  
			  Status = E_TIMEOUT ;  
			  break;  
		  }  
		  else
		  {
			/*Reset esp receving buffer*/
			Reset_Buffer();
			/*Send the same command again */
			ESP_NetworkConnect(NetworkName , Password);
		  }
	  }
		  
	}	
	
	 Reset_Buffer();
	
	return Status;
}

ErrorStatus ESP_ServerConnect(uint8_t *IP)
{
	
	/*temp variable to store function status*/
	uint8_t Status         = E_OK;
	/*temp variable to count the timeout*/
	uint32_t Local_TimeOut = 0   ;
	/*temp variable to check for the max time out*/
	uint8_t  Local_MaxTime = 0   ;
	
	/*send a command to connect the esp with the server according to its Ip address*/
	UART_TransmitSynchronous(ESP_USART_CHANNEL , "AT+CIPSTART=");
	UART_TransmitSynchronous(ESP_USART_CHANNEL , "\"TCP\"");
	UART_TransmitSynchronous(ESP_USART_CHANNEL , ",");
	UART_TransmitSynchronous(ESP_USART_CHANNEL , "\"");
	UART_TransmitSynchronous(ESP_USART_CHANNEL , IP);
	UART_TransmitSynchronous(ESP_USART_CHANNEL , "\"");
	UART_TransmitSynchronous(ESP_USART_CHANNEL , ",");
	UART_TransmitSynchronous(ESP_USART_CHANNEL , "80");
	UART_TransmitSynchronous(ESP_USART_CHANNEL , "\r\n");
	
	/*wait until the esp responds with OK*/
	while(Find_string(ESP_RX_Buffer , "OK") == 0) 
	{
	   /*increment the time out counter*/
		Local_TimeOut++;  
		  
		if(Local_TimeOut == ESP_MAX_RX_TIMEOUT)  
		{  
		  /*time out reachs the maximum time out reset the time out counter*/  
		  Local_TimeOut = 0 ;  
		  /*increment the repeat receiving counter*/  
		  Local_MaxTime++;  
		    
		  if(Local_MaxTime == ESP_MAX_TIME_COUNT)  
		  {  
			  /*when it reachs the maximum number of command repeat sending without any response  
			    but the status as timeout error and break the loop	  */  
			  Status = E_TIMEOUT ;  
			  break;  
		  }  
		  else
		  {
			/*Reset esp receving buffer*/
			  Reset_Buffer();
			/*Send the same command again */
			  ESP_ServerConnect(IP);
		  }
	  }
		  
	}
	
	Reset_Buffer();
	
	return Status;
}

ErrorStatus ESP_SendData(uint8_t *DataBuffer , uint8_t *DataSize)
{
	/*temp variable to store function status*/
	uint8_t Status         = E_OK;
	/*temp variable to count the timeout*/
	uint32_t Local_TimeOut = 0   ;
	/*temp variable to check for the max time out*/
	uint8_t  Local_MaxTime = 0   ;

	/*send a command to notify the ESP of the size of data to to be sent*/	
	UART_TransmitSynchronous(ESP_USART_CHANNEL , "AT+CIPSEND=");
	UART_TransmitSynchronous(ESP_USART_CHANNEL , DataSize);
    UART_TransmitSynchronous(ESP_USART_CHANNEL , "\r\n"); 	
	
	/*wait until the esp responds with OK*/
	while(Find_string(ESP_RX_Buffer , "OK") == 0) 
	{
	 /*increment the time out counter*/
		Local_TimeOut++;  
		  
		if(Local_TimeOut == ESP_MAX_RX_TIMEOUT)  
		{  
		  /*time out reachs the maximum time out reset the time out counter*/  
		  Local_TimeOut = 0 ;  
		  /*increment the repeat receiving counter*/  
		  Local_MaxTime++;  
		    
		  if(Local_MaxTime == ESP_MAX_TIME_COUNT)  
		  {  
			  /*when it reachs the maximum number of command repeat sending without any response  
			    but the status as timeout error and break the loop	  */  
			  Status = E_TIMEOUT ;  
			  break;  
		  }  
		  else
		  {
			/*Reset esp receving buffer*/
			  Reset_Buffer();
			/*Send the same command again */
			UART_TransmitSynchronous(ESP_USART_CHANNEL , "AT+CIPSEND=");
			UART_TransmitSynchronous(ESP_USART_CHANNEL , DataSize); 
			UART_TransmitSynchronous(ESP_USART_CHANNEL , "\r\n"); 	
		  }
		  
	  }
			
	}
	/*after the esp reponse then send teh data buffer*/
	UART_TransmitSynchronous(ESP_USART_CHANNEL , DataBuffer); 	
	UART_TransmitSynchronous(ESP_USART_CHANNEL , "\r\n");
	
	return Status ; 
}

void ESP_ReceiveData(uint8_t *StoredataBuffer)
{
	/*check for all data is sent and stored on the esp rx buffer*/
	if(Find_string(ESP_RX_Buffer , "OK") != 0 && Find_string(ESP_RX_Buffer , "CLOSED") != 0)
	{
		   /**/
		   uint32_t Local_Index = 0 ;
		   /*Local variable to help getting only data from the esp rx buffer*/
		   uint32_t StartOfData = 0 ;
		   
		   /*esp data starts after the letter ':'  +IPD,:*/
		   while(ESP_RX_Buffer[StartOfData] != ':')
		   {
					StartOfData++;
		   }
		   
		   /*increment it by one to skip the letter ':' and only store the valuable data*/
		   StartOfData++ ;
		
		/*copy the data into the user buffer until reaching the end of the data*/		
		while((ESP_RX_Buffer[Local_Index + StartOfData + 0] != 'C')  	&& 
		      (ESP_RX_Buffer[Local_Index + StartOfData + 1] != 'L')  	&&
	      	  (ESP_RX_Buffer[Local_Index + StartOfData + 2] != 'O')  	&&
			  (ESP_RX_Buffer[Local_Index + StartOfData + 3] != 'S')     &&
	      	  (ESP_RX_Buffer[Local_Index + StartOfData + 4] != 'E')  	&&
			  (ESP_RX_Buffer[Local_Index + StartOfData + 5] != 'D')    )
		{
			StoredataBuffer[Local_Index] = ESP_RX_Buffer[Local_Index + StartOfData] ;
			Local_Index++;
		}
		
		/*Reset the esp rx buffer after copying the data*/	
		Reset_Buffer();
		ESP_ServerConnect("162.253.155.226");
  	ESP_SendData("GET http://imtarm.freevar.com/status.txt" , "42");
	}
	else
	{
		/*Do Nothing*/
	}
}
 
void Reset_Buffer(void)
{
	for(uint32_t Local_Index = 0 ; Local_Index <ESP_MAX_RX_BUFFER_SIZE ; Local_Index++)
	{
		 ESP_RX_Buffer[Local_Index] = 0 ;
		
	}
	 ESP_BufferCounter           = 0 ;
}

/********************************************************************/
/*helper function to find a word on a string*/
uint8_t Find_string(uint8_t *string , uint8_t *string_nedded)
{
	uint8_t ret_value = 0 ;
	uint32_t match = 0;
	uint32_t lenOfString = strlen(string);
	uint32_t lenghtOFNeddedString  =  strlen(string_nedded);
	
	if(lenghtOFNeddedString > lenOfString)
	{
		ret_value = 0 ;
	}
	for(uint32_t i = 0 ;i < lenOfString; i++)
	{
		if(string[i] == string_nedded[match])
		{
			match++;

			if(lenghtOFNeddedString == match)
			{
				ret_value = 1 ;
			}
			else
			{
			
			}

		}
		else
		{
			match = 0;
		}
			
	}
	
	return ret_value ;

}
