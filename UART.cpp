//####################################################
//#Saturday, 17.Januar.2015 made by Lars C. Schwensen#
//####################################################

//#################################################################
//#This file handles the UART functionality                       #
//#DEVICE: BeagleBone Black                                       #
//#OS: Debian                                                     #
//#################################################################

//UART.cpp

#include "UART.h"

#include <fcntl.h> //handles O_RDWR etc.
#include <string.h> // needed for memset

#include <fstream>

UART::UART() {
	char target[] = ENABLE_PATH;
	char value[] = SELECTED_UART;

	writeTo(target, value);
}

UART::~UART() {
	closeDevice();
}

int UART::openDevice()
{
	const char *device = UART_PATH;
	fd = open(device, O_RDWR | O_NOCTTY | O_NDELAY);

	if(fd == -1) {
		printf("failed to open port!\n");
	}

	return fd;
}

void UART::closeDevice()
{
	close(fd);
}

int UART::initUart()
{
	struct termios settings;
	memset(&settings,0,sizeof(settings));

	settings.c_iflag = 0; //input flags
	settings.c_oflag = 0; //output flags
	settings.c_cflag=
			CS8 | //8 bits
			CREAD | //enable receiver
			CLOCAL; //ignore modem status lines
	settings.c_lflag=0;
	settings.c_cc[VMIN]=1; //minimum one value
	settings.c_cc[VTIME]=5; //time

	fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) & ~O_NONBLOCK); //blocking mode (does not really work)

	if(openDevice())
	{
		cfsetispeed(&settings,BAUD); //input baudrate
		cfsetospeed(&settings,BAUD); //output baudrate

		tcsetattr(fd,TCSANOW,&settings);
		return 1;
	}

	return -1;
}

void UART::sendChar(uint8_t character)
{
	write(fd,&character,1);
}

uint8_t UART::receiveChar()
{
	uint8_t character;

	while(read(fd, &character, 1) < 1);

	return character;
}

int UART::writeTo(char target[], char value[])
{
	std::ofstream targetFile;
	targetFile.open(target);
	if(targetFile.is_open())
	{
		targetFile << value;
		targetFile.close();
		return 1;
	}
	return -1;
}

