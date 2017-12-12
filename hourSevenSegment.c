/*
	Author: Rodrigo Ignacio Rojas Garcia
	Contact information: rrojas@clemson.edu
	Purpose: Uses RaspberryPi 3 GPIO pins to display the syste's current hour in a 7-Segment ANODE LED display
*/


// Library Declaration Section
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <wiringPi.h>

int main(int argc, char *argv[])
{
	// Variable Declaration Section 
	int currentHour;	// Used to store the current hour of the machine
	struct tm *currentTime;	// Used to store the time stamp
	int powerPin = -1;	// Used to store GPIO that wil supply 3.3V to the 7-Segment display
	time_t rawTime;		// Used to store the time of the machine

	// Sets variable powerPin to argument which contains GPIO pin that will suppy the 3.3V to 7-Segment display 
	powerPin = atoi(argv[1]);
	
    	// Initializes RaspberryPi GPIO Pins
    	wiringPiSetupGpio(); 
	// Sets GPIO pins as OUTPUT
   	pinMode(powerPin, OUTPUT);
	pinMode(5, OUTPUT);		// a
	pinMode(6, OUTPUT);		// f
	pinMode(12, OUTPUT);	// e
	pinMode(13, OUTPUT);	// d
	pinMode(16, OUTPUT);	// c
	pinMode(19, OUTPUT);	// b
	pinMode(20, OUTPUT);	// g
	pinMode(21, OUTPUT);	// dp
	
	// Delivers 3.3V to 7-Segment Display 
	digitalWrite(powerPin, HIGH);
	
	// Infinite loop which will keep calculating the machine's currenttime
	while (1)
	{
		// Calculates the time of the machine and stores it on variable rawTime
		time(&rawTime);
		// Calls function localtime() to obtain machine's current time and set it to variable currentTime
		currentTime = localtime(&rawTime);
		// Stores the machine's current hour into currentHour variable by accessing currenTime struct
		currentHour = currentTime->tm_hour;
	
		// Series of IF statements that will set GPIO pins to HIGH or LOW depending on what the
		// current hour that needs to be displayed
		if (currentHour == 0 || currentHour == 12)
		{
			digitalWrite(5, LOW);
			digitalWrite(6, LOW);
			digitalWrite(12, LOW);
			digitalWrite(13, LOW);
			digitalWrite(16, LOW);
			digitalWrite(19, LOW);
			digitalWrite(20, HIGH);
			digitalWrite(21, HIGH);
			sleep(1);
		}
		if (currentHour == 1 || currentHour == 13)
		{
			digitalWrite(5, HIGH);
			digitalWrite(6, HIGH);
			digitalWrite(12, HIGH);
			digitalWrite(13, HIGH);
			digitalWrite(16, LOW);
			digitalWrite(19, LOW);
			digitalWrite(20, HIGH);
			digitalWrite(21, HIGH);
			sleep(1);
		}
		if (currentHour == 2 || currentHour == 14)
		{	
			digitalWrite(5, LOW);
			digitalWrite(6, HIGH);
			digitalWrite(12, LOW);
			digitalWrite(13, LOW);
			digitalWrite(16, HIGH);
			digitalWrite(19, LOW);
			digitalWrite(20, LOW);
			digitalWrite(21, HIGH);
		}
		if (currentHour == 3 || currentHour == 15)
		{
			digitalWrite(5, LOW);
			digitalWrite(6, HIGH);
			digitalWrite(12, HIGH);
			digitalWrite(13, LOW);
			digitalWrite(16, LOW);
			digitalWrite(19, LOW);
			digitalWrite(20, LOW);
			digitalWrite(21, HIGH);
			sleep(1);
		}
		if (currentHour == 4 || currentHour == 16)
		{
			digitalWrite(5, HIGH);
			digitalWrite(6, LOW);
			digitalWrite(12, HIGH);
			digitalWrite(13, HIGH);
			digitalWrite(16, LOW);
			digitalWrite(19, LOW);
			digitalWrite(20, LOW);
			digitalWrite(21, HIGH);
			sleep(1);
		}
		if (currentHour == 5 || currentHour == 17)
		{
			digitalWrite(5, LOW);
			digitalWrite(6, LOW);
			digitalWrite(12, HIGH);
			digitalWrite(13, LOW);
			digitalWrite(16, LOW);
			digitalWrite(19, HIGH);
			digitalWrite(20, LOW);
			digitalWrite(21, HIGH);
			sleep(1);
		}
		if (currentHour == 6 || currentHour == 18)
		{
			digitalWrite(5, HIGH);
			digitalWrite(6, LOW);
			digitalWrite(12, LOW);
			digitalWrite(13, LOW);
			digitalWrite(16, LOW);
			digitalWrite(19, HIGH);
			digitalWrite(20, LOW);
			digitalWrite(21, HIGH);
			sleep(1);
		}
		if (currentHour == 7 || currentHour == 19)
		{
			digitalWrite(5, LOW);
			digitalWrite(6, HIGH);
			digitalWrite(12, HIGH);
			digitalWrite(13, HIGH);
			digitalWrite(16, LOW);
			digitalWrite(19, LOW);
			digitalWrite(20, HIGH);
			digitalWrite(21, HIGH);
			sleep(1);
		}
		if (currentHour == 8 || currentHour == 20)
		{
			digitalWrite(5, LOW);
			digitalWrite(6, LOW);
			digitalWrite(12, LOW);
			digitalWrite(13, LOW);
			digitalWrite(16, LOW);
			digitalWrite(19, LOW);
			digitalWrite(20, LOW);
			digitalWrite(21, HIGH);
			sleep(1);
		}
		if (currentHour == 9 || currentHour == 21)
		{
			digitalWrite(5, LOW);
			digitalWrite(6, LOW);
			digitalWrite(12, HIGH);
			digitalWrite(13, HIGH);
			digitalWrite(16, LOW);
			digitalWrite(19, LOW);
			digitalWrite(20, LOW);
			digitalWrite(21, HIGH);
			sleep(1);
		}
		if (currentHour == 10 || currentHour == 22)
		{
			digitalWrite(5, LOW);
			digitalWrite(6, HIGH);
			digitalWrite(12, LOW);
			digitalWrite(13, LOW);
			digitalWrite(16, HIGH);
			digitalWrite(19, LOW);
			digitalWrite(20, LOW);
			digitalWrite(21, LOW);
		}	
		if (currentHour == 11 || currentHour == 23)
		{	
			digitalWrite(5, LOW);
			digitalWrite(6, HIGH);
			digitalWrite(12, HIGH);
			digitalWrite(13, LOW);
			digitalWrite(16, LOW);
			digitalWrite(19, LOW);
			digitalWrite(20, LOW);
			digitalWrite(21, LOW);
			sleep(1);
		}		
	
	}

	// Exits program	
	return 0;
}
