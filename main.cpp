
#include "UART.h"

int main()
{
	UART uart;

	uart.initUart();

	while(1)
	{
		printf("%d\n", uart.receiveChar());
	}
	return 1;
}
