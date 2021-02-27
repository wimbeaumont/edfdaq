#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

// include the Raspberry Pi IO definitions 
#include <pigpio.h>
/*
gcc -o rbpi_blink_simple rbpi_blink_simple.c -lpigpio -lpthread

program to let all gpio toggle 
note you have to link the Raspberry Pi IO lib
*/



int main(int argc, char *argv[]) {
   
    int allgpio[]= { 2,3,4,17,27,23,10,9,11,5,6,13,18,26,14,15,18,23,24,25,8,7,12,16,20,21 };
    int nr_io= sizeof(allgpio) /sizeof(allgpio[0]);
	// you have to initialize the libary and configure the processor IO 
	int err= gpioInitialise(); 
	if (err <0) return err; 
 
   printf("Monitoring gpios");
     for ( int lc =0;lc < nr_io;lc++) {
	for ( int lc =0;lc < nr_io;lc++) gpioSetMode(allgpio[lc], PI_OUTPUT); // Set as output.
    }
	
for (;;)
  {
    for ( int lc =0;lc < nr_io;lc++)   gpioWrite (allgpio[lc], 1) ;	// On
    sleep (1) ;		// you need some time to see it 
	// remove both  sleep  statements to see what happens 
    for ( int lc =0;lc < nr_io;lc++) gpioWrite (allgpio[lc], 0) ;	// Off
    sleep (1) ;
  }


   gpioTerminate();
   return 0; 
}

