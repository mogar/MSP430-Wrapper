#include <io.h>
#include "helper_functions.h"

void pinMode(int pin, int mode) {
    /*
    mode:
    0 - input
    1 - output
    2 - analog
    */
    if (mode == INPUT) {
        P1DIR &= ~(1 << pin);
    } else if (mode == OUTPUT) {
        P1DIR |= 1 << pin;
        P1OUT &= ~(1 << pin);
        ADC10AE0 &= ~ (1 << pin);
    } else if (mode == ANALOG) {
        ADC10AE0 |= 1 << pin;
    }
    
}

void digitalWrite(int pin, int mode) {
    if (mode == 0) {
        P1OUT &= ~(1 << pin);
    } else {
        P1OUT |= 1 << pin;
    }
}

int digitalRead(int pin) {
    return P1IN & (1 << pin);
}

void initADC(void) {
    // set up the ADC to use
    
    /*
    Using a range from Vss to Vcc
    Takes 16 ADC10 clks to convert
    enable the ADC
    */
    ADC10CTL0 = SREF_0 + ADC10SHT_2 + ADC10ON;
    
    /*
    Using internal oscillator for ADC
    Single sample, single channel mode
    */
    ADC10CTL1 = ADC10SSEL_0 + CONSEQ_0;
    
}

int analogRead(int pin) {
    if (ADC10AE0 & (1 << pin)) {
        ADC10CTL1 &= 0x0FFF; //ignore whatever channel was being looked at
        ADC10CTL1 |= (0xF & pin) << 12;//select the new ADC channel to read
        ADC10CTL0 |= ENC + ADC10SC;    // Sampling and conversion start
        while (ADC10CTL1 & ADC10BUSY); //wait until it's done
        return ADC10MEM;
    } else {
        return -1;
    }
}

void analogWrite2(int duty_cycle) {
    //TODO: see if I can update this to use any pin
    int pin = 2;
    pinMode(pin, OUTPUT);
    P1SEL |= 1 << pin;
    CCR0 = 512 - 1; //set PWM period
    CCTL1 = OUTMOD_7;                         // CCR1 reset/set
    CCR1 = duty_cycle;                        // CCR1 PWM duty cycle
    TACTL = TASSEL_2 + MC_1;                  // SMCLK, up mode
    
}