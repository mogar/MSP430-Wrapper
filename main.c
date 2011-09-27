/*
MSP430-Wrapper
Morgan Redfield
2011 September 27

This project reimplements several elements of the Arduino on an MSP430 Launchpad.

Code that would go in the Arduino setup function now goes in the MSP430 setup function below.
Code that would go in the Arduino loop function now goes in the while(1) in the main function below.
*/
#include <io.h>
//#include <msp430g2231.h>

#include <signal.h>
#include "helper_functions.h"

void setup(void) {
  //  Setup Code Goes Here
  pinMode(0, OUTPUT);
  pinMode(6, OUTPUT);
  
  pinMode(3, INPUT);
  //  end setup code
}

int main(void) {
  WDTCTL = WDTPW + WDTHOLD;	// Stop WDT
  BCSCTL3 |= LFXT1S_2;	//Set ACLK to use internal VLO (12 kHz clock) auxilliary clock
  //MCLK master clock
  //SMCLK sub main clock
  
  //call setup function
  setup();

  //declaring local variables
  int num_pressed = 0;
  int button_toggle = 0;
  int led_on = 0;
  
  while(1) {
    // loop code goes here
	if (!digitalRead(3) && button_toggle == 0) 
	{
		button_toggle = 1;
		num_pressed++;
	} 
	else if (button_toggle == 1)
	{
		button_toggle = 0;
		digitalWrite(0, HIGH);
		for (int i = 0; i < 2*num_pressed; i++) {
			led_on = !led_on;
			digitalWrite(6, led_on);
			delay(100000000);
		}
		digitalWrite(0, LOW);
	}
    // end loop code
  }
}