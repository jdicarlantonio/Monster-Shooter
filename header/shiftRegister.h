#ifndef SHIFTREGISTER_H
#define SHIFTREGISTER_H

#include <avr/io.h>
#include <util/delay.h>

#define PORT PORTB  
#define DDR DDRB
#define DATA PB0            // data pin
#define SHIFT_CLK PB1       // shift clock
#define STORE_CLK PB2       // store block

void shiftInit()
{
    // init DDR
    DDR |= ((1 << SHIFT_CLK) | (1 << STORE_CLK) | (1 << DATA));
}

void shiftHigh()
{
    PORT |= (1 << DATA);
}

void shiftLow()
{
    PORT &= (~(1 << DATA));
}

// pulse the shift clock
void shiftPulse()
{
    PORT |= (1 << SHIFT_CLK);
    PORT &= (~(1 << SHIFT_CLK));
}

// pulse the store clock
void shiftLatch()
{
    PORT |= (1 << STORE_CLK);
    _delay_loop_1(1); // delay for data storage
    PORT &= (~(1 << STORE_CLK));
    _delay_loop_1(1);
}

void shiftWrite(uint8_t data)
{
    // send all 8 bits one at a time
    for(uint8_t i = 0; i < 8; i++)
    {
        // output data according to MSB
        if(data & 0b10000000)
        {
            // MSB is one
            shiftHigh();
        }
        else
        {              
            // MSB is zero
            shiftLow();
        }

        shiftPulse();  // pulse shift clock
        data = data << 1;  // shift MSB
    }

    // send bits to output latch
    shiftLatch();
}

void Wait()
{
    for(uint8_t i=0;i<50;i++)
    {
        _delay_loop_2(0);
    }
}

#endif
