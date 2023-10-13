#include "sw_led.h"
#include "derivative.h"


void SWL_Init (void)
{
    DDR1AD1 = 0b11100000,
    ATD1DIEN1 = 0b00011111;
}

void SWL_ON (SWL_LEDColour led)
{
    PT1AD1 |= led;
}
void SWL_OFF (SWL_LEDColour led)
{
    PT1AD1 &= ~led;
}
void SWL_TOG (SWL_LEDColour led)
{
    PT1AD1 ^= led;
}


// is a specific switch being pushed (T/F)
int SWL_Pushed (SWL_SwitchPos pos)
{
    if (pos & SWL_ANY)
        return 1;
    else 
        return 0;
}

// is any switch being pushed (T/F)
int SWL_Any (void);