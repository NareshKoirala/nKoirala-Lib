#include "derivative.h"
#include "segs.h"
#include "clock.h"
#include "pit.h"

// setup ports to speak with 7-segs
void Segs_Init(void)
{
    DDRA |= PORTA_PA1_MASK | PORTA_PA0_MASK;
    DDRB = 0xFF;

    Segs_Clear();
}

// show HEX decoding (changes all of display to HEX, w/wo dp)
/* Params: (address, data, dp) */
void Segs_Normal(unsigned char addr, unsigned char data, Segs_DPOption x)
{
    PORTB = 0b01011000;

    PORTB |= (addr & 0x7);

    PORTA |= PORTA_PA1_MASK;

    latch();

    PORTB = data;

    if (!x)
    {
        PORTB |= 0x80;
    }
    else
    {
        PORTB &= ~0x80;
    }

    PORTA &= ~PORTA_PA1_MASK;

    latch();
}

void segsDecimal(unsigned char Addr)
{
    PORTB = 0b01011000;

    PORTB |= (Addr & 0x7);

    PORTA |= PORTA_PA1_MASK;

    latch();

    PORTB = PORTB;

    PORTB &= ~0x80;
    
    PORTA &= ~PORTA_PA1_MASK;

    latch();
}

// control segs manually
/* Params: (address, data) */
void Segs_Custom(unsigned char addr, unsigned char data)
{
    PORTB = 0b01111000;

    PORTB |= (addr & 0x7);

    PORTA |= PORTA_PA1_MASK;

    latch();

    PORTB = data;

    PORTB |= 0x80;

    PORTA &= ~PORTA_PA1_MASK;

    latch();
}

// clear the display
/* Params: (address) */
void Segs_ClearDigit(unsigned char addr)
{
    Segs_Custom(addr, 0);
    PORTB = 0x80;
}

// clear the entire display
void Segs_Clear(void)
{
    unsigned char i = 0;
    for (i = 0; i < 8; i++)
    {
        Segs_ClearDigit(i);
    }
}

// clear display  upper or lower line
/* Params: (line) */
void Segs_ClearLine(Segs_LineOption x)
{
    unsigned char i = 0;

    if (x)
    {
        i = 4;
        for (i = 4; i < 8; i++)
        {
            Segs_ClearDigit(i);
        }
    }
    else
    {
        i = 0;
        for (i = 0; i < 4; i++)
        {
            Segs_ClearDigit(i);
        }
    }
}

// show a 16-bit value on the upper or lower display
/* Params: (value, line) */
void Segs_16H(unsigned int num, Segs_LineOption x)
{
    int i = 0;
    if (x)
    {
        for (i = 7; i > 3; i--)
        {
            Segs_Normal(i, (unsigned char)(num % 16), Segs_DP_OFF);
            num /= 16;
        }
    }
    else
    {
        for (i = 3; i >= 0; i--)
        {
            Segs_Normal(i, (unsigned char)(num % 16), Segs_DP_OFF);
            num /= 16;
        }
    }
}

// show a decimal value on the first or second line of the 7-segs
/* Params: (value, line) */
void Segs_16D(unsigned int num, Segs_LineOption x)
{
    int i = 0;
    if (x)
    {
        for (i = 7; i > 3; i--)
        {
            Segs_Normal(i, (unsigned char)(num % 10), Segs_DP_OFF);
            num /= 10;
        }
    }
    else
    {
        for (i = 3; i >= 0; i--)
        {
            Segs_Normal(i, (unsigned char)(num % 10), Segs_DP_OFF);
            num /= 10;
        }
    }
}

// show the 8-bit value starting on the digit as addr (0-6)
/* Params: (addr, value) */
// void Segs_8H (unsigned char, unsigned char)
// {

// }

// say Err on the appropriate line
/* Params: (line) */

void Segs_SayErr(Segs_LineOption x)
{
    int i = 0;
    unsigned char val = E;

    if (!x)
    {
        while (i < 4)
        {
            if (i == 1)
            {
                val = r;
            }
            if (i == 2)
            {
                val = r;
            }
            if (i == 3)
            {
                val = o;
            }

            Segs_Custom(i, val);

            i++;
        }
    }
    else
    {
        i = 4;
        val = E;
        while (i < 8)
        {
            if (i == 5)
            {
                val = r;
            }
            if (i == 6)
            {
                val = r;
            }
            if (i == 7)
            {
                val = o;
            }

            Segs_Custom(i, val);
            i++;
        }
    }
}

void latch()
{
    int i = 10;
    PORTA &= ~PORTA_PA0_MASK;

    if (busspeed > 8000000)
    {
        while (--i)
            ;
    }

    PORTA |= PORTA_PA0_MASK;
}

void owo(Segs_LineOption x)
{
    int i = 0;
    unsigned char val = DEGREE_SIGN;

    if (!x)
    {
        while (i < 4)
        {
            if (i == 1)
            {
                val = u;
            }
            if (i == 2)
            {
                val = u;
            }
            if (i == 3)
            {
                val = DEGREE_SIGN;
            }

            Segs_Custom(i, val);

            i++;
        }
    }
    else
    {
        i = 4;
        val = DEGREE_SIGN;
        while (i < 8)
        {
            if (i == 5)
            {
                val = u;
            }
            if (i == 6)
            {
                val = u;
            }
            if (i == 7)
            {
                val = DEGREE_SIGN;
            }

            Segs_Custom(i, val);
            i++;
        }
    }
}

unsigned int count = 0;
void loading(unsigned char addr)
{
    unsigned int segs = SEG_E;

    PIT_Sleep(PIT_CH3, 400);

    if (count > 5)
    {
        count = 0;
    }

    if (count == 0)
    {
        segs = SEG_E;
    }
    if (count == 1)
    {
        segs = SEG_F;
    }
    if (count == 2)
    {
        segs = SEG_A;
    }
    if (count == 3)
    {
        segs = SEG_B;
    }
    if (count == 4)
    {
        segs = SEG_C;
    }
    if (count == 5)
    {
        segs = SEG_D;
    }

    Segs_Custom(addr, segs);

    count++;
}
