/*
	Author: Rodrigo Ignacio Rojas Garcia
	Contact Information: rrojas@clemson.edu
	Purpose: Display numbers 0-9 in a 7-Segment ANODE display continously 
*/

// Library Declaration Section 
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	// Variable Declaration Section
	int c1;
	int powerPin = -1;
	
	powerPin = atoi(argv[1]);
	

    // Initializes RaspberryPi GPIO Pins
    wiringPiSetupGpio(); 
    pinMode(powerPin, OUTPUT);
	pinMode(5, OUTPUT);		// a
	pinMode(6, OUTPUT);		// f
	pinMode(12, OUTPUT);	// e
	pinMode(13, OUTPUT);	// d
	pinMode(16, OUTPUT);	// c
	pinMode(19, OUTPUT);	// b
	pinMode(20, OUTPUT);	// g
	pinMode(21, OUTPUT);	// dp
	
	// Digital output of value HIGH is outputted by desired GPIO pin passed in argument
	digitalWrite(powerPin, HIGH);
	
	while (1)
	{
		for (c1 = 0; c1 < 10; c1++)
		{
			switch(c1)
			{
				case 0:
					digitalWrite(5, LOW);
					digitalWrite(6, LOW);
					digitalWrite(12, LOW);
					digitalWrite(13, LOW);
					digitalWrite(16, LOW);
					digitalWrite(19, LOW);
					digitalWrite(20, HIGH);
					digitalWrite(21, HIGH);
					sleep(1);
					break;
				case 1:
					digitalWrite(5, HIGH);
					digitalWrite(6, HIGH);
					digitalWrite(12, HIGH);
					digitalWrite(13, HIGH);
					digitalWrite(16, LOW);
					digitalWrite(19, LOW);
					digitalWrite(20, HIGH);
					digitalWrite(21, HIGH);
					sleep(1);
					break;
				case 2:
					digitalWrite(5, LOW);
					digitalWrite(6, HIGH);
					digitalWrite(12, LOW);
					digitalWrite(13, LOW);
					digitalWrite(16, HIGH);
					digitalWrite(19, LOW);
					digitalWrite(20, LOW);
					digitalWrite(21, HIGH);
					sleep(1);
					break;
				case 3:
					digitalWrite(5, LOW);
					digitalWrite(6, HIGH);
					digitalWrite(12, HIGH);
					digitalWrite(13, LOW);
					digitalWrite(16, LOW);
					digitalWrite(19, LOW);
					digitalWrite(20, LOW);
					digitalWrite(21, HIGH);
					sleep(1);
					break;
				case 4:
					digitalWrite(5, HIGH);
					digitalWrite(6, LOW);
					digitalWrite(12, HIGH);
					digitalWrite(13, HIGH);
					digitalWrite(16, LOW);
					digitalWrite(19, LOW);
					digitalWrite(20, LOW);
					digitalWrite(21, HIGH);
					sleep(1);
					break;
				case 5:
					digitalWrite(5, LOW);
					digitalWrite(6, LOW);
					digitalWrite(12, HIGH);
					digitalWrite(13, LOW);
					digitalWrite(16, LOW);
					digitalWrite(19, HIGH);
					digitalWrite(20, LOW);
					digitalWrite(21, HIGH);
					sleep(1);
					break;
				case 6:
					digitalWrite(5, HIGH);
					digitalWrite(6, LOW);
					digitalWrite(12, LOW);
					digitalWrite(13, LOW);
					digitalWrite(16, LOW);
					digitalWrite(19, HIGH);
					digitalWrite(20, LOW);
					digitalWrite(21, HIGH);
					sleep(1);
					break;
				case 7:
					digitalWrite(5, LOW);
					digitalWrite(6, HIGH);
					digitalWrite(12, HIGH);
					digitalWrite(13, HIGH);
					digitalWrite(16, LOW);
					digitalWrite(19, LOW);
					digitalWrite(20, HIGH);
					digitalWrite(21, HIGH);
					sleep(1);
					break;
				case 8:
					digitalWrite(5, LOW);
					digitalWrite(6, LOW);
					digitalWrite(12, LOW);
					digitalWrite(13, LOW);
					digitalWrite(16, LOW);
					digitalWrite(19, LOW);
					digitalWrite(20, LOW);
					digitalWrite(21, HIGH);
					sleep(1);
					break;
				case 9:
					digitalWrite(5, LOW);
					digitalWrite(6, LOW);
					digitalWrite(12, HIGH);
					digitalWrite(13, HIGH);
					digitalWrite(16, LOW);
					digitalWrite(19, LOW);
					digitalWrite(20, LOW);
					digitalWrite(21, HIGH);
					sleep(1);
					break;
				
			}
		}
	}
	
	return 0;
}
