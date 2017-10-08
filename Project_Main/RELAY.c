/*******************************************************************************************************
*                                       UART0 PROGRAM                                                  *
********************************************************************************************************
*                                     HEADER DECLARATIONS                                              *
*******************************************************************************************************/
#include<lpc21xx.h>
#include "common.h"
 
void DIO_Init(void)
{
   IODIR0 = 0x00000008;  // P0.03 = 1, Relay DIgital Output
   /* Relay should be OFF at INIT */
   IOCLR0 = 0x00000008;  // P0.03 = 1, RELAY OFF
}

void RelayTrigger(unsigned int flag)
{
   if(flag)
   {
      IOSET0 = 0x00000008;  // P0.03 = 1, RELAY ON 
   }
   else
   {
      IOCLR0 = 0x00000008;  // P0.03 = 1, RELAY OFF  
   }
}

void LED_Blink(unsigned long int n)
{
   IOCLR1 = 0x00FF0000; /* Clear All Leds*/
   IOSET1 = 0x00010000 << n;      
}
 
/*********************************************END******************************************************/
