#include <avr/io.h>
#define F_CPU 16000000UL
#define LED PD4

int main (void)
{
    DDRD=0x10;
   
   while (1)
   {  
      
      PORTD ^= (0x01 << LED);         
      delayMicroseconds(1);                                      
      
   }
}






