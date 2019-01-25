#include <inttypes.h> //short forms for various integer types

#define F_CPU 1000000UL // Crystal frequency required for delay functions

#include <avr/io.h>     // Standard include for AVR
#include <util/delay.h> // Delay functions

int main()
{
    DDRB = 0xff;  // use all pins on PortB for output
    PORTB = 0x00; // set output high -> turn all LEDs off

    // set OC1A pin as output, required for output toggling
    DDRD |= _BV(PD5);

    // enable 8 bit PWM, select inverted PWM
    TCCR1A = _BV(WGM10) | _BV(COM1A1) | _BV(COM1A0);

    // Timer1 running on 1/8 MCU clock with clear timer/counter1 on Compare Match
    // PWM frequency will be MCU clock / 8 / 512, e.g. with 4Mhz Crystal 977 Hz.
    TCCR1B = _BV(CS11) | _BV(WGM12);

    while(1)
    {
        uint8_t i;
        /* dimm LED on */
        for(i = 0; i < 255; i++)
        {
            OCR1AL = i;    // Note OCR1AL NOT OCR1A
            PORTB = i;     // for debugging
            _delay_ms(10); // delay 10 ms just to slow things down
        }
        /* dimm LED off */
        for(i = 255; i > 0; i--)
        {
            OCR1AL = i;    // Note OCR1AL NOT OCR1A
            PORTB = i;     // for debugging
            _delay_ms(10); // delay 10 ms just to slow things down
        }
    }
    return 0;
}
