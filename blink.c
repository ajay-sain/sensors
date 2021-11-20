/*
 * blink.c:
 *      blinks the first LED
 */

#include <stdio.h>
#include <wiringPi.h>

int main (void)
{
  printf ("Raspberry Pi blink\n") ;

    const unsigned int PIN_TO_OUT = 0;
  if (wiringPiSetup () == -1)
    return 1 ;

  pinMode (PIN_TO_OUT, OUTPUT) ;         // aka BCM_GPIO pin 17

  while (1==1)
  {
    digitalWrite (PIN_TO_OUT, 1) ;       // On
    delay (500) ;               // mS
    digitalWrite (PIN_TO_OUT, 0) ;       // Off
    delay (500) ;
  }
  return 0 ;
}
