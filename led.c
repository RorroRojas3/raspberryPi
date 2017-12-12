/*
	Author: Rodrigo Ignacio Rojas Garcia
	Contact: rrojas@clemson.edu
	Purpose: Set RaspberryPi 3 GPIO pins as OUTPUT to send a digital output of value either HIGH or LOW 
*/

// Library Declaration Section
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <string.h>

// Function which will display the correct way to run program along with its corresponding arguments 
void menu()
{
	printf("Usage:\n");
	printf("Light up LED -> ./program pinNumber 1\r\n");
	printf("Turn OFF LED -> ./program pinNumber 0\r\n");
}

int main(int argc, char *argv[])
{
	// Variable Declaration Section 
	int highOrLow = -1;
	int pinNumber = -1;
	// If the number of arguments is not two, program terminates
	if (argc != 3)
	{
		printf("Wrong arguments\r\n");
		menu();
		return 0;
	}
	
	// Stores pin number entered by user into variable pinNumber
	pinNumber = atoi(argv[1]);
	
	// Checks if user wants to turn ON LED
	if (strcmp(argv[2], "1") == 0)
	{
		highOrLow = HIGH;
	}
	
	// Checks if user wants to turn OFF LED
	if (strcmp(argv[2], "0") == 0)
	{
		highOrLow = LOW;
	}
	
	// Initializes RaspberryPi Setup
    wiringPiSetup(); 
    // Initializes RaspberryPi GPIO Pins
    wiringPiSetupGpio(); 
    // Sets pin entered by user as OUTPUT
    pinMode(pinNumber, OUTPUT);
    // Turns LED ON or OFF depending on user input
    digitalWrite(pinNumber, highOrLow );
    
    // Terminates program 
    return 0;
}
