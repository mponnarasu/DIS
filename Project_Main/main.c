/******************************************************************************/
/* BLINKY.C: LED Flasher                                                      */
/******************************************************************************/
/* This file is part of the uVision/ARM development tools.                    */
/* Copyright (c) 2005-2006 Keil Software. All rights reserved.                */
/* This software may only be used under the terms of a valid, current,        */
/* end user licence from KEIL for a compatible version of KEIL software       */
/* development tools. Nothing else gives you the right to use this software.  */
/******************************************************************************/
                  
#include <LPC21xx.H>                       /* LPC21xx definitions */
#include "common.h"


unsigned int tick = 0u; // Latest Tick
unsigned int tick_old; // Previous tick

/* Timer Counter 0 Interrupt executes each 1ms @ 60 MHz CPU Clock */
__irq void tc0 (void) {
  tick++;
  T0IR = 1;                                    // Clear interrupt flag
  VICVectAddr = 0;                             // Acknowledge Interrupt
}


/* Setup the Timer Counter 0 Interrupt */
/* Pclk = 15Mhz, PR = 0 */
void Timer_Init()
{
  T0PR = 0;
  T0MR0 = 29999999;                               // 1mSec = 15000-1 counts
  T0MCR = 3;                                   // Interrupt and Reset on MR0
  T0TCR = 1;                                   // Timer0 Enable
  VICVectAddr0 = (unsigned long)tc0;           // set interrupt vector in 0
  VICVectCntl0 = 0x20 | 4;                     // use it for Timer 0 Interrupt
  VICIntEnable = 0x00000010;                   // Enable Timer0 Interrupt
  
}

int main (void) 
{
   static unsigned char GsmInitFlag = 0u; 
   unsigned int readADCValue; //Read ADC value 
   /* Initialization */ 
   Port_Init(); // It should be selecting required Port Configuration
   DIO_Init();  // Ensure Relay is OFF
   ADC_Init();  //ADC Configuration Settings
   UART_Init(); // Setup UART configuration for 9600 baud
   Timer_Init();// Setup Timer Interrupt for 1 second
   IODIR1 = 0x00FF0000;
   IOCLR1 = 0x00FF0000;
   while(1)
   {
      if(GsmInitFlag != 0u)
	  {	  	  
	      /* Run forever */
		  if(tick != tick_old)
		  {
		     /* System Implementation */
			 /* ADC Reading */
			 readADCValue = Read_ADC();
			 /* Sensor Diagnostics */
	         if(readADCValue > SHORTCIRCUITVALUE)
			 {
			    GSMSendMessage(SYSTEMFAILURE_SSC);
				/* Switch OFF relay */
				RelayTrigger(RELAY_OFF);
				LED_Blink(2);   
			 }
			 else if(readADCValue < OPENCIRCUITVALUE)
			 {
			    /* Send Message "System Failure" */
				GSMSendMessage(SYSTEMFAILURE_SOC);
				/* Switch OFF relay */
				RelayTrigger(RELAY_OFF);
				LED_Blink(3);   
			 }
			 else
			 {	
		        /* Threshold Checking */
				if(readADCValue > HIGH_THRESHOLD) //High Moisture
				{
				   /* Switch OFF relay */
				   RelayTrigger(RELAY_OFF);
				   /* Send Message "System OFF */
				   GSMSendMessage(RELAY_OFF);
				   LED_Blink(4); 
				 }
				 
				 if(readADCValue < LOW_THRESHOLD)  //Dry weather 
				 {
				    /* Switch ON relay */
					RelayTrigger(RELAY_ON);
					/* Send Message "System ON" */
					GSMSendMessage(RELAY_ON);
					LED_Blink(5);
				 }			 
			   }
			   tick_old = tick; // Update tick old to tick		  
		  }
		  else
		  {
		     /* Do Nothing */
		  }
      }
      else
      { 
         if(tick > 6u)
		 {
		    GsmInitFlag = 1u; 
		 }
      }
   }
}
