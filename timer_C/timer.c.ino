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


int main(void)
{  

    /***************************Prog Initialization**********************************/
  int ones=0x30, tens=0x30, setclk =0, val;
  DDRD|=0xFF;                                  // setting the port B as output
  DDRB|=0X07;
   
  PORTC = 0x00;
  DDRC=0x00;
                // setting for port D pin 0,1,2 as output
  init_LCD();
  _delay_ms(100);  // initialization of LCD
                                
     /***************************************************************************/
  
  
  LCD_String_Write("Press Start");
  while(setclk == 0)
   {
  PORTC = 0x00;
  
  
  if(bit_is_set(PINC,PC1))
  {
    setclk = 1;
    LCD_set_cursor(1,0);
    LCD_String_Write("Time Count =");
    
    _delay_ms(500);
  }
  
  else
    setclk = 0;
  
  }
  
  
  
  
  
    while(setclk == 1)
  { PORTC = 0x00;
    
    LCD_set_cursor(1,13);
    
    if(tens>0x30)
    {
      LCD_write(tens); 
      if(tens == 0x3a)
      { 
        LCD_set_cursor(1,0);
        LCD_String_Write("time count ");
        
        _delay_ms(1000);
 
      }

    }
    
    LCD_write(ones); 
    _delay_ms(1000);
    ones++;
    if(ones == 0x3a)
    {
      tens++;
      ones=0x30;
    }
    
    if(bit_is_set(PINC,PC0))
    { 
      setclk=0;
      LCD_set_cursor(1,0);
      LCD_String_Write("time count ");
    }
    
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




void LCD_String_Write(unsigned char *string)             //store address value of the string in pointer *string
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

