/*
Frisbot
Morgan Redfield
2011 August 22

This application controls a frisbot with three light sensors arranged
120 degrees apart. The frisbot will seek out the brightest light source
and move towards it.

TODO: figure out ADC code
Choose drive pins
choose sensor pins
figure out math for sense function
*/
#include <io.h>
//#include <msp430g2231.h>

#include <signal.h>
#include "helper_functions.h"

#define SLOP 50

int abs(int a) {
    if (a < 0) {
        return -a;
    } else {
        return a;
    }
}

void initIO(void) {
  P1DIR |= 0x71;
}

void move(int direction) {
    //P1.0 is left wheel
    //P1.6 is right wheel
    //just a test?
    P1OUT = 0;
    switch (direction) {
        case 0: //go straight
    	    P1OUT ^= 0x41;
            break;
        case 1: //turn left (only right wheel on)
            P1OUT ^= 0x40;
            break;
        case 2: //turn right (only left wheel on)
       	    P1OUT ^= 0x01;
            break;
        //case 3: //go back
        //	P1OUT ^= 0x30;
        //	break;
        default: //else stop
            break;
    }
}

int senseLight(void) {
    int left = analogRead(1); //left
    int right = analogRead(2); //right
    int rear = analogRead(3); //rear
    //read the light sensors and return the direction to go

    if (abs(rear - left) < SLOP && abs(rear - right) < SLOP) {
        if (abs(left - right) < SLOP) {
            // we're heading towards it
            return 0; //go straight
        } else {
            // we're off by a little bit
            if (left > right) {
                return 1; // turn left
            } else {
                return 2; // turn right
            }
        }
    } else {
        // the light is behind us, we need to turn around
        return 1; //turn left always
    }
}

int main(void) {
  WDTCTL = WDTPW + WDTHOLD;	// Stop WDT
  BCSCTL3 |= LFXT1S_2;	//Set ACLK to use internal VLO (12 kHz clock) auxillieary clock
  //MCLK master clock
  //SMCLK sub main clock
  initIO();		//Setup LED and button
  initADC();    //setup ADCs on pins 1, 2, and 3 = 0xE
  pinMode(1, ANALOG);
  pinMode(2, ANALOG);
  pinMode(3, ANALOG);
  
  analogWrite(2, 255);
  while(1) {
  	//int direction = senseLight();
  	//move(direction);
  }
}