#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#define LCD_DATA PORTD                //LCD data port
#define LCD_ctrl PORTB
#define F_CPU 1000000UL
void LCD_cmd(unsigned char cmd);
void init_LCD(void);
void LCD_write(unsigned char data);
void LCD_Sting_Write(unsigned char *string) ;
int main(void)
{
  DDRD|=0xFF;                                  // setting the port B as output
  DDRB|=0X07;                                // setting for port D pin 0,1,2 as output
  init_LCD();                                 // initialization of LCD
  _delay_ms(100);                           
  LCD_String_Write("Shreyas Pillu");                    
  _delay_ms(500);
  LCD_cmd(LINE_2);                                   //Line 2 command
  LCD_String_Write("Gr8 Anil Kumar");         
  _delay_ms(500);
  /*LCD_cmd(0X94);                  //Line 3 command
  LCD_String_Write("Prof. Varun M");
  _delay_ms(500);
  LCD_cmd(0XD4);                  //Line 4 command
  LCD_String_Write("Manager Vemula");
  _delay_ms(100);*/
  LCD_cmd(0X0F);               // blink the cursor after printing is done
  return 0;
}


void LCD_cmd(unsigned char cmd)
{
LCD_ctrl =(0<<RS)|(0<<RS)|(1<<EN);
//LCD_ctrl = 0X04;
LCD_DATA=cmd;

_delay_ms(50);
LCD_ctrl =(0<<RS)|(0<<RW)|(0<<EN);
//LCD_ctrl = 0X00;
_delay_ms(50);

}

void LCD_write(unsigned char data)        // Writing a character
{
  
  LCD_ctrl = (1<<RS)|(0<<RW)|(1<<EN);
  //LCD_ctrl = 0X05;
  LCD_DATA= data;
  _delay_ms(50);
  LCD_ctrl = (1<<RS)|(0<<RW)|(0<<EN);
  //LCD_ctrl = 0x01;
  _delay_ms(50);

}

void LCD_String_Write(unsigned char *string)             //store address value of the string in pointer *string
{
  int i=0;
  while(string[i]!= '\0')                               // Loop will execute till it detects null character
{
  LCD_write(string[i]);                            // sending data on LCD byte by byte
  i++;
  _delay_ms(100);
}

}

