#include <avr/io.h>
#include <util/delay.h>
#define LCD_DATA PORTD                //LCD data port
#define LCD_ctrl PORTB
#define en PB2                         // enable 
#define rw PB1                       // read/write 
#define rs PB0                     // register select 
#define F_CPU 1000000UL
void LCD_cmd(unsigned char cmd);
void init_LCD(void);
void LCD_write(unsigned char data);
void LCD_Sting_Write(unsigned char *string) ;
void LCD_set_cursor(char a, char b);
unsigned int read_adc();
void init_adc();
int main(void)
{  
    /***************************Prog Initialization**********************************/
  int val,one,ten,b;
  float a;
  DDRD|=0xFF;                                  // setting the port B as output
  DDRB|=0X07;     // setting for port D pin 0,1,2 as output
  init_LCD();
    // initialization of LCD
  init_adc();
  _delay_ms(100);
                           
     /***************************************************************************/
   LCD_String_Write("TS ACTIVATED");
   _delay_ms(500);
   init_LCD(); // CLEAR LCD
  LCD_String_Write("ROOM TEMP=");
  while(1)
  { LCD_set_cursor(1,11);
    a=read_adc();
    _delay_ms(500);
    a=(a/2);
    b=a;
    one=(b%10)+(0x30);
    ten=(b/10)+(0x30);
    if(ten != 0x30)
    { 
    LCD_write(ten);
  LCD_set_cursor(1,12);
      }       
   LCD_write(one);
  }


  return 0;
}
void init_LCD(void)
{
  LCD_cmd(0x38);                            // initialization of 8bit mode
  _delay_ms(50);
  
  LCD_cmd(0x01);                                 // clear LCD
  _delay_ms(50);
  
  LCD_cmd(0x0E);                        // Setting cursor ON
  _delay_ms(50);
  
  LCD_cmd(0x80);                     // —8 go to first line and –0 is for 0th position
  _delay_ms(50);

}

void init_adc()
{
  
    // AREF = AVcc
    ADMUX = (1<<REFS0);
 
    // ADC Enable and prescaler of 128
    // 16000000/128 = 125000
    ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

unsigned int read_adc()
{// select the corresponding channel 0~7
  // ANDing with ’7' will always keep the value
  // of ‘ch’ between 0 and 7
  int ch=2;
  ch &= 0b00000111;  // AND operation with 7
  ADMUX = (ADMUX & 0xF8)|ch; // clears the bottom 3 bits before ORing
 
  // start single convertion
  // write ’1' to ADSC
  ADCSRA |= (1<<ADSC);
 
  // wait for conversion to complete
  // ADSC becomes ’0' again
  // till then, run loop continuously
  while(ADCSRA & (1<<ADSC));
 
  return (ADC);
}

void LCD_cmd(unsigned char cmd)
{
LCD_ctrl =(0<<rs)|(0<<rw)|(1<<en);
//LCD_ctrl = 0X04;
LCD_DATA=cmd;

_delay_ms(1);
LCD_ctrl =(0<<rs)|(0<<rw)|(0<<en);
//LCD_ctrl = 0X00;
_delay_ms(1);

}

void LCD_write(unsigned char data)        // Writing a character
{
  
  LCD_ctrl = (1<<rs)|(0<<rw)|(1<<en);
  LCD_ctrl = 0X05;
  LCD_DATA= data;
  _delay_ms(1);
  LCD_ctrl = (1<<rs)|(0<<rw)|(0<<en);
  //LCD_ctrl = 0x01;
  _delay_ms(1);

}
void LCD_String_Write(unsigned char *string)             //store address value of the string in //pointer*string
{
  int i=0;
  while(string[i]!= '\0')                               // Loop will execute till it detects null character
{
  LCD_write(string[i]);                            // sending data on LCD byte by byte
  i++;
  _delay_ms(10);
}

}



void LCD_set_cursor(char a, char b)
{
  if(a == 1)
  LCD_cmd(0x80 + b);
  else if(a == 2)
  LCD_cmd(0xC0 + b);
}

