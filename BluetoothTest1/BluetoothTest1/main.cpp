#include <avr/io.h>
#include <inttypes.h>

#define F_CPU 8000000UL
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD -1

int main()
{
	char* ReceivedChar = "";

	UBRRH = (MYUBRR >> 8);
	UBRRL = MYUBRR;
	
	//Enable The receiver and transmitter
	UCSRB=(1<<RXEN)|(1<<TXEN);
	UCSRC |= (1 << URSEL) |(1 << UCSZ1) | (1 << UCSZ0);    // Set frame: 8data, 1 stp

	while(1)
	{
		while ( (UCSRA & (1 << RXC)) == 0 ){};   // Wait until data is received
		
		ReceivedChar = UDR;                     // Read the data from the RX buffer
		
		while ( (UCSRA & (1 << UDRE)) == 0 ){};  // Wait until buffer is empty

		UDR = ReceivedChar;                     // Send the data to the TX buffer
	}
}