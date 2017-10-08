#ifndef COMMON_H
#define COMMON_H


#define LOW_THRESHOLD 300u 	// Below this value, switch on Relay
#define	HIGH_THRESHOLD 600u

#define SHORTCIRCUITVALUE 950u // Short Cicuit plates
#define OPENCIRCUITVALUE 75u // Open Cicuit plates

#define RELAY_ON 1u 
#define RELAY_OFF 0u
#define SYSTEMFAILURE_SOC 2u //Open Circuit Sensor 
#define SYSTEMFAILURE_SSC 3u //Short Circuit Sensor

extern void UART_Init(void);
extern void Uart_Data(unsigned char data );
extern void Uart_String(unsigned char *dat);
extern void Port_Init(void); 

extern void DIO_Init(void);
extern void RelayTrigger(unsigned int flag);
extern void LED_Blink(unsigned long int n);

extern void GSMSendMessage(unsigned int state);

extern void ADC_Init(void);
extern unsigned int Read_ADC(void);

#endif
