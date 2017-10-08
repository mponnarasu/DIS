/*******************************************************************************************************
*                                       UART0 PROGRAM                                                  *
********************************************************************************************************
*                                     HEADER DECLARATIONS                                              *
*******************************************************************************************************/
#include<lpc21xx.h>
#include "common.h"
static unsigned int state_new = 0u;
static unsigned int state_old = 0u;
 
unsigned char SMSstring[]={'A','T','+','C','M','G','S','=','"','9','9','8','0','7','9','0','0','3','5','"'};

void delay(void)
{
   unsigned int i,j;
   for(i=0;i<6000;i++)
   {
      for(j=0;j<60;j++)
	  ;
   }
} 
void GSMSendMessage(unsigned int state)
{
   state_new = state;
  
   if(state_new != state_old)
   { 
      state_old = state_new;  
	  switch(state)
	   {
	      case RELAY_ON:
		     Uart_String("AT+CMGF=1\r");    
		     delay();  
		     Uart_String(&SMSstring[0]);
			 Uart_Data('\r');
			 delay();    
		     Uart_String("SYSTEM ON");    
		     Uart_Data(0x1A);
		     break;
	
		  case RELAY_OFF:
			Uart_String("AT+CMGF=1\r");    
		    delay();  
		    Uart_String(&SMSstring[0]);
			Uart_Data('\r');
			delay();    
		    Uart_String("SYSTEM OFF");    
		    Uart_Data(0x1A);
			break;
	
		  case SYSTEMFAILURE_SOC:
			Uart_String("AT+CMGF=1\r");    
		    delay();  
		    Uart_String(&SMSstring[0]);
			Uart_Data('\r');
			delay();    
		    Uart_String("SYSTEM FAILURE SOC");    
		    Uart_Data(0x1A);
			break;
	
		   case SYSTEMFAILURE_SSC:
			Uart_String("AT+CMGF=1\r");    
		    delay();  
		    Uart_String(&SMSstring[0]);
			Uart_Data('\r');
			delay();    
		    Uart_String("SYSTEM FAILURE SSC");    
		    Uart_Data(0x1A);
			break;
	
		   default:
		   break;
	   }
   }
}
/*********************************************END******************************************************/
