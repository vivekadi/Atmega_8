#include<avr/io.h>
#include<util/delay.h>
#define blink_port_D PORTD
#define blink_port_A PORTA
#define blink_port_B PORTB
#define blink_port_C PORTC
#define F_CPU 1000000UL
int main(void)
{  
  DDRD = DDRD |(0X01<<PD6);
  DDRA = DDRA |(0x01<<PA6);
  DDRC = DDRC |(0X01<<PB6);
  DDRB =DDRB |(0X01<<PC6);
    while('!')
    {
     blink_port_D |= (0X01<<PD6);
       _delay_ms(500);
    
       blink_port_D &= ~(0X01<<PD6);
       _delay_ms(500);
     
     blink_port_A |=(0X01<<PA6);
     _delay_ms(500);
     
     blink_port_A &= ~(0X01<<PA6);
     _delay_ms(500);
     blink_port_B |=(0X01<<PB6);
     _delay_ms(500);
     
     blink_port_B &= ~(0X01<<PB6);
     _delay_ms(500);
     blink_port_C |=(0X01<<PC6);
     _delay_ms(500);
     
     blink_port_C &= ~(0X01<<PC6);
     _delay_ms(500);
     
    }
}

