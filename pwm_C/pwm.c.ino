#include<avr/io.h>
#include<util/delay.h>

#define FAST_PWM_MODE (0X09<<WGM01)
#define NON_INV_PWM   (0X01<<COM01)
#define CLOCK_TYPE    (0X01<<CS00)
#define TIMER_CONTROL_REG0   TCCR0

#define F_CPU 1000000UL

void PWM_val(uint8_t dutyvalue);
void PWM_INT(void);

int main(void)
{
  uint8_8 brigtness =0;
  
  
  PWM_INIT();
  
  //infinite loop
  
  while(1)
  {
    //fade in
    for(brightness=0;brightness<255;brightness++)
    {
      PWM_val(brightness);
      
      _delay_ms(20);
      
    }
    
  _delay_ms(500);
    for(brightness=255;brightness>0;brightness--)
    {
      //fade out
       
       PWM_val(brightness);
       
       _delay_ms(20);
       
      }
    _delay_ms(500);
    }
  }

