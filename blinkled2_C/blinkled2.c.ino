#include<avr/io.h>
#include<util/delay.h>
#define blink_port PORTD
#define F_CPU 1000000UL
int main(void)
{  
  DDRD = DDRD |(0X01<<PD6);
    while('!')
    {
     blink_port |= (0X01<<PD6);
       _delay_ms(500);
    
       blink_port &= ~(0X01<<PD6);
       _delay_ms(500);
        
    }
    return 0;
  
}

