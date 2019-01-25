#include<avr/io.h>
#define F_CPU 1000000UL
#define LED PD4 

int main()
{ 
   DDRD=0x10;         //configure PORTD as output (pin6 or PD4)
   TCNT0=0x00;
   TCCR0 =0x01;     // prescaler , or clock dision selection CS02 CS01 CS00 
   
  while(1)
  {     
      while ((TIFR & 0x01) == 0); 
      TCNT0 = 0x00;
      TIFR=0x01; //clear timer1 overflow flag                 
      PORTD ^= (0x01 << LED);                
  } 
}
