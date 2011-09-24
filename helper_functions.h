#define false 0
#define true 1

#define INPUT 0
#define OUTPUT 1
#define ANALOG 2

#define LOW 0
#define HIGH 1

static void __inline__ delay(register unsigned int n)
{
__asm__ __volatile__ (
"1: \n"
" dec %[n] \n"
" jne 1b \n"
: [n] "+r"(n));
}

void pinMode(int pin, int mode);

void digitalWrite(int pin, int mode);

int digitalRead(int pin);

void initADC(void);

int analogRead(int pin);

void analogWrite(int pin, int duty_cycle);