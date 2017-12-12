// Library Declaration Section
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>
#include <unistd.h>

// Fucntions that tells the user how to 
// use the program if wrong arguments are entered 
void menu()
{
	printf("Usage:\n");
	printf("Light up LED -> ./program pinNumber\r\n");
	printf("Turn OFF LED -> ./program pinNumber\r\n");
}

int main(int argc, char *argv[])
{
	// Variable Declaration Section 
	int pinNumber = -1;
	// If the number of arguments is not two, program terminates
	if (argc != 2)
	{
		printf("Wrong arguments\r\n");
		menu();
		return 0;
	}
	
	// Stores pin number entered by user into variable pinNumber
	pinNumber = atoi(argv[1]);
	
	// Initializes RaspberryPi Setup
	wiringPiSetup();
	// Initializes RaspberryPi GPIO Pins
	wiringPiSetupGpio();
	// Sets pin entered by user as OUTPUT
	pinMode(pinNumber, OUTPUT);
	// Turn ON and OFF LED indifinitely 
	while (1)
	{
		digitalWrite(pinNumber, HIGH);
		sleep(1);
		digitalWrite(pinNumber, LOW);
		sleep(1);
	}
	return 0;
}
