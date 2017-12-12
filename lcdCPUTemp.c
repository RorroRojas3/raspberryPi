/*
	Author: Rodrigo Ignacio Rojas Garcia
	Contact Information: rrojas@clemson.edu
	Purpose: Display text on the RaspberryPi 3
*/

// Library Declaration Section
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wiringPi.h>          
#include <lcd.h>  
#include <unistd.h>             
 
// Constants Declaration Section
#define ROWS 2	// Defines number of rows of LCD Display
#define COLUMNS 16	// Defines number of columns of LCD Display
#define BITS 4	// Defines 4/8 bit mode of LCD Display
#define RS 2	// Defines GPIO pin 2 as the Register Select which will send commands and text 
#define E 3		// Defines GPIO pin 3 as the Enable pin so instructions can be sent
#define LCD0 4	// Defines GPIO pin 4 as data line for D4
#define LCD1 5	// Defines GPIO pin 5 as data line for D5
#define LCD2 6	// Defines GPIO pin 6 as data line for D6
#define LCD3 7	// Defines GPIO pin 7 as data line for D7
#define MAXCHARACTERS 256

int main(int argc, char *argv[])
{
	// variable Declartion Section
    int lcdDisplay; // Used as a handler
	FILE *tempFile; // Used to open file that contains RaspberryPi 3 CPU temperature
	char line[MAXCHARACTERS];	// Used to store current line being read
	char tempString[MAXCHARACTERS];	// Used to store temperature string
	double temperature = -1;	// Used to store the CPU temperature 
	
	// Sets up RaspberryPi GPIO pins
	wiringPiSetupGpio();      
	// Sets up RaspberryPi pins for the LCD display
    lcdDisplay = lcdInit (ROWS, COLUMNS, BITS, RS, E, LCD0, LCD1, LCD2, LCD3, 0, 0, 0, 0);
    
    // Infinite loop that will keep displaying the RaspberryPi CPU temperature constantly
   	while (1)
    {	
    	// Opens file containing RaspberryPi CPU temperature
		tempFile = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
		// If file cannot be accessed it terminates the program 
		if (tempFile == NULL)
		{
			printf("Error in opening file, program will be terminated\n");
			exit(1);
		}
		// Reads file opened until it reaches the end of the file 
		while(fgets(line, sizeof(line), tempFile))
		{
			// Stores line that obtains temperature information into variable tempString
			strcpy(tempString, line);
		}
		// Converts string tempString into a number 
		temperature = atoi(tempString);
		temperature = temperature / 1000;
		// Sets the poisiton of LCD display to first row and first column
    	lcdPosition(lcdDisplay,0,0);   
		// Displayts message into LCD display	
		lcdPuts(lcdDisplay, "CPU Temperature:" );
		// Sets position of LCD display to second row first column
		lcdPosition(lcdDisplay,0,1);
		// Converts integer variable temperature into string 
		sprintf(tempString, "%.2f Celcius", temperature);
		lcdPuts(lcdDisplay, tempString);  
		// Sleeps program for one second
    	sleep(1);
    	// Clears all output of CPU display 
    	lcdClear(lcdDisplay);
  	}
    
}
