/*
 
 */ 
//#define F_CPU 8000000
#include <avr/io.h>


#define usingLcd
#define usingUart
#define usingGeneralAVR

#define maxChar 8

/**********************
LCD PIN CONFIGURATION
*********************/
#define lcdRsDir DDRA_B0
#define lcdEnDir DDRA_B1
#define lcdD4Dir DDRA_B2
#define lcdD5Dir DDRA_B3
#define lcdD6Dir DDRA_B4
#define lcdD7Dir DDRA_B5

#define lcdRs PORTA_B0
#define lcdEn PORTA_B1
#define lcdD4 PORTA_B2
#define lcdD5 PORTA_B3
#define lcdD6 PORTA_B4
#define lcdD7 PORTA_B5


#include "C://Emancipator/Emancipator.h"
#include "C://Emancipator/USART_RS232_H_file.h"

lcd display (16,2);


int main(void)
{
	display.init();
	//UART1_Init(9600);
	USART_Init(9600);
	delay_ms(200);
	display.writeText(0,0,"Bluetooth Read");
	delay_ms(1500);
	
	char Read;
	char *message[maxChar];
	
	while(1)
	{
		while (USART_DataReady() > 0)
		{
			char recieved = UART1_Read();
			*message += recieved;

			// Process message when new line character is recieved
			if (recieved == '\n')
			{
				display.writeText(1,0,*message);


				*message = ""; // Clear recieved buffer
			}
		}
			
		//display.writeText(1,0,message);
		_delay_ms(100);
	}		
}