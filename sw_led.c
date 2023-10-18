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
    if (PT1AD1 & pos)
        return 1;
    return 0;
}

// is any switch being pushed (T/F)
int SWL_Any (void)
{
    if (PT1AD1 & SWL_ANY)
        return 1;
    return 0;
}

int SwcountLED ()
{
    int count=0;
    
    if(SWL_Pushed(SWL_GREEN))
        count += 1;
    if(SWL_Pushed(SWL_RED))
        count += 1;
    if(SWL_Pushed(SWL_YELLOW))
        count += 1;
    return count;
}

int sw_count()
{
    int count=0;
    
    if(SWL_Pushed(SWL_UP))
        count += 1;
    if(SWL_Pushed(SWL_DOWN))
        count += 1;
    if(SWL_Pushed(SWL_RIGHT))
        count += 1;
    if(SWL_Pushed(SWL_LEFT))
        count += 1;
    if(SWL_Pushed(SWL_CTR))
        count += 1;
    return count;

}

SwState states(SwState current, SWL_SwitchPos pos)
{
    if ((PT1AD1 & pos) && current == Idle)
        return Pressed;

    if((PT1AD1 & pos) && current == Pressed) 
        return Held;

    if (!(PT1AD1 & pos) && current == Held)
        return Released;
    if (!(PT1AD1 & pos) && current == Released) 
        return Idle;
}

void delay(unsigned int i)
{
    i = i*2667;
    while(--i);
}

void delayMore(int i)
{
    i = i/20;
    while(i--)
    {
        delay(20);
    }
}
void delaysSec(int i)
{

}

void DelaySpeed(unsigned long mS)
{
    unsigned long iterations= 2*(mS*940/7);

    for(iterations; 0< iterations;iterations--);
}


