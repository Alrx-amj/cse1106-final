#include <stdio.h> 
#include <unistd.h>
#include <pigpio.h>
#define PIN 17
 
int main (int argc, char* argv[])
{
    gpioInitialiase ();
    gpioSetMode (PIN, PI_OUTPUT);
    gpioWrite (pin, 1);// led on 
    getchar(); // wait for enter key
    gpioWrite (PIN,0);// led off
    getchar(); // waits for enter key
    gpioTerminate();
    return 0; 
}
