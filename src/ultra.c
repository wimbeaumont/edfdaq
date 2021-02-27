/*
 * ultra.c:
 *	program detect a incomming pulse via ISR ( interrupt service routine) 
 *
 * Copyright (c) 2012-2013 Gordon Henderson. <projects@drogon.net>
 ***********************************************************************
 * This file is copied and edited from wiringPi:
 *	https://projects.drogon.net/raspberry-pi/wiringpi/
 *
 *    wiringPi is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    wiringPi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public License
 *    along with wiringPi.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************
 */

#include <stdio.h>
#include <wiringPi.h>
#include <time.h>



#define	LED  14  // used to have a visual feedback .
#define UTRIG 7
#define ECHO 25  
#define LOOPLED 18

int ISRcnt=0;
struct timespec gTime ;
struct timespec sTime ; 
int Time_found; 
static int   LEDstat;	

void EchoISR( ) {
 
	ISRcnt++;
	if( digitalRead(ECHO) ) { // is high so rising edge 
		clock_gettime(CLOCK_MONOTONIC, &sTime);
		digitalWrite (LED, LEDstat) ;
		LEDstat= !LEDstat;
	} 
	else {clock_gettime(CLOCK_MONOTONIC, &gTime);}
	Time_found=TRUE; 
}



int main (void) {

int err_res;
 printf ("ultra sound test\n") ;
  wiringPiSetupGpio() ;

// time sectino
	
/*
struct timespec {
               time_t   tv_sec;        // seconds 
               long     tv_nsec;       // nanoseconds 
           };
*/
 err_res=clock_getres(CLOCK_MONOTONIC , &sTime);
  if (  err_res){
	printf("get timeres failed with  %d \n\r",err_res);
  }
  else {printf("time resolution is %d \n\r" , sTime.tv_nsec);}


  pinMode (LED, OUTPUT) ;
  pinMode (LOOPLED, OUTPUT) ;
  pinMode (UTRIG, OUTPUT) ;	
  wiringPiISR (ECHO, INT_EDGE_BOTH, EchoISR ) ;
  Time_found=FALSE;
  LEDstat=0;	
  int lcnt=0;
  for (;;)  {
    	digitalWrite (UTRIG, HIGH) ;
//	clock_gettime(CLOCK_MONOTONIC, &sTime);
	digitalWrite (UTRIG, LOW) ;	// pulse 
	delayMicroseconds (12);
//	for ( int cnt=0; cnt <300; cnt++) {
//	    digitalWrite (UTRIG, LOW) ;	// pulse 
//	}

    digitalWrite (UTRIG, HIGH) ;	// On 

    delay (500) ;		// mS
    if(Time_found) {
	Time_found=FALSE;
	long nsT=gTime.tv_nsec- sTime.tv_nsec;
	if ( nsT <0 ) {
		nsT+=1e9;
      		gTime.tv_sec--;
        }
	int sT= (int ) ( gTime.tv_sec - sTime.tv_sec); 
//	printf("get interrupt on %d %d \n\r",gTime.tv_sec, gTime.tv_nsec );
//	printf("get starttime on %d %d \n\r",sTime.tv_sec, sTime.tv_nsec );
	printf( "time diff = %d s %d us dist=%f [m]\n\r" ,sT, nsT/1000, 0.5*nsT*308/1e9);
    }
   //printf( "ISRcnt = %d %d \n", ISRcnt ,ISRcnt%4);
   printf( "ISRcnt = %d \n", ISRcnt );
   digitalWrite (LOOPLED , (lcnt++)%2);
    }
  return 0 ;
}

