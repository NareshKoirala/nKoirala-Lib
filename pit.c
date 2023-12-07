#include "derivative.h"
#include "pit.h"
#include "clock.h"

unsigned int microT = 0;
unsigned long pit = 0;
unsigned long checker = 0;
unsigned long msCounter = 0;

unsigned long tick(unsigned int ms)
{
    return (busspeed * ((double)ms / 1000.00));
}

void timer(unsigned int ms)
{
    int i = 1;
    unsigned long tickPerSec = tick(ms);

    if (tickPerSec < 65000)
    {
        microT = 1;
        pit = tickPerSec + 1;
    }
    else
    {
        do
        {
            if ((tickPerSec % i) == 0)
            {
                if ((tickPerSec / i) <= 65000)
                {
                    if ((tickPerSec / i) * i == tickPerSec)
                    {
                        checker = 1;
                        microT = i;
                        pit = (tickPerSec / i);
                    }
                }
            }
            i++;

        } while (checker == 0);
    }
}

int noBlockDefaultDelay(PIT_Channel ch)
{
    if (PITTF & ch)
    {
      PITTF = ch;
      return 1;
    }
    return 0;
}

void PIT_InitChannel(PIT_Channel ch, PIT_MicroTimer mt, PIT_Interrupt ie, unsigned int ms, unsigned int checker)
{

    if (mt == PIT_MT1)
    {

        if (checker == 1)
        {
            PITMUX |= ch;
            noblockTimer(ms, ch, mt);
        }
        if (ie)
        {
            PITINTE |= ch;
        }
        else
        {
            PITINTE &= ~ch;
        }

        PITCE |= ch;
    }
    else
    {

        if (checker == 1)
        {
            PITMUX &= ~ch;
            noblockTimer(ms, ch, mt);
        }
        
        if (ie)
        {
            PITINTE |= ch;
        }
        else
        {
            PITINTE &= ~ch;
        }

        PITCE |= ch;
    }
    
    PIT_Start();
}


void noblockTimer(unsigned int ms, PIT_Channel ch, PIT_MicroTimer mt)
{
    timer(ms);

    {
        unsigned int mic = microT;

        unsigned long pst = pit;

        if (mt == PIT_MT1)
        {
            PITMTLD1 = mic - 1;
        }
        else
        {
            PITMTLD0 = mic - 1;
        }

        if (ch == PIT_CH0)
        {
            PITLD0 = pst - 1;
        }
        if (ch == PIT_CH1)
        {
            PITLD1 = pst - 1;
        }
        if (ch == PIT_CH2)
        {
            PITLD2 = pst - 1;
        }
        if (ch == PIT_CH3)
        {
            PITLD3 = pst - 1;
        }
    }
}

void initializingOnems(PIT_Channel ch)
{
    timer(1);

    {
        unsigned long mic = microT;
        unsigned long pst = pit;

        PITMUX |= ch;

        PITMTLD1 = mic - 1;

        if (ch == PIT_CH0)
        {
            PITLD0 = pst - 1;
        }
        if (ch == PIT_CH1)
        {
            PITLD1 = pst - 1;
        }
        if (ch == PIT_CH2)
        {
            PITLD2 = pst - 1;
        }
        if (ch == PIT_CH3)
        {
            PITLD3 = pst - 1;
        }

        PITINTE &= ~ch;

        PITCE |= ch;
    }
}

void PIT_Set1msDelay(PIT_Channel ch)
{
    if (msCounter == 0)
    {
        msCounter = 1;
        initializingOnems(ch);
    }

    PIT_Start();

    while (!(PITTF & ch));
    PITTF = ch;
}

void PIT_Start()
{
    if (!(PITCFLMT & PITCFLMT_PITE_MASK))
        PITCFLMT |= PITCFLMT_PITE_MASK;
}

void PIT_Sleep(PIT_Channel ch, unsigned int ms)
{
    unsigned int i;

    PIT_Start();
    
    forceload(ch);

    for (i = 0; i < ms; i++) 
    {
        PIT_Set1msDelay(ch);
    }
}

void PIT_Delay_us(PIT_Channel ch, unsigned int us)
{
    unsigned long pst = (busspeed / 1000000) * us;

    PITMUX |= ch;

    PITMTLD1 = 1 - 1;

    if (ch == PIT_CH0)
    {
        PITLD0 = pst - 1;
    }
    if (ch == PIT_CH1)
    {
        PITLD1 = pst - 1;
    }
    if (ch == PIT_CH2)
    {
        PITLD2 = pst - 1;
    }
    if (ch == PIT_CH3)
    {
        PITLD3 = pst - 1;
    }

    PITINTE &= ~ch;

    PITCE |= ch;

    forceload(ch);

    while (!(PITTF & ch))
        ;
    PITTF = ch;
}

void forceload(PIT_Channel ch)
{
    PITFLT |= ch;
    PITTF = ch;
}

/*
    if(PITTF & PITTF_PTF1_MASK)
    {
      PITTF = PITTF_PTF1_MASK;
      SWL_TOG(SWL_GREEN);
    }


    interrupt VectorNumber_Vpit0 void Vpit0_Handler(void)
    {
        PITTF = PITTF_PTF0_MASK; //clear flag;
    }
*/