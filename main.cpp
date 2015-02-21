
#include "UART.h"
#include <ctime>
#include <stdint.h>

volatile int i;

int trash(int count)
{
	for(i=0; i<100000000; i++)
	{
		if(i >= count)
		{
			return i;
		}
	}
	return i;
}

int main()
{
	UART uart;

	uart.initUart();
	
	int i=1;
	while(1)
	{			
		//printf("%d\n", uart.receiveChar());
		uart.sendChar((i % 2));
		//printf("%x\n", 0x01);
		//trash(100000);
		uart.sendChar(0xf0);
		//printf("%x\n", 0xf0);
		//trash(100000);
		uart.sendChar(0x0f);
		//printf("%x\n", 0x0f);
		//trash(100000);
		uart.sendChar(i);
		trash(100000000);
		//trash(100000000);
		//trash(100000000);
		trash(100000000);

		i++;
	}
	//return 1;
}
