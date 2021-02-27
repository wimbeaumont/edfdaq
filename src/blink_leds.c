#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

// include the Raspberry Pi IO definitions 
#include <pigpio.h>
/*
gcc -o rbpi_blink_simple rbpi_blink_simple.c -lpigpio -lpthread

note you have to link the Raspberry Pi IO lib
*/

// use GPIO18 to control the green LED on the adapter board. 
const int LEDgreen=18;


int main(int argc, char *argv[]) {
	// you have to initialize the libary and configure the processor IO 
	int err= gpioInitialise(); 
	if (err <0) return err; 
 
   printf("Monitoring gpios");
 
	gpioSetMode(LEDgreen, PI_OUTPUT); // Set GPIO18 as output.
	
for (;;)
  {
    gpioWrite (LEDgreen, 1) ;	// On
    sleep (1) ;		// you need some time to see it 
	// remove both  sleep  statements to see what happens 
    gpioWrite (LEDgreen, 0) ;	// Off
    sleep (1) ;
  }


   gpioTerminate();
   return 0; 
}

