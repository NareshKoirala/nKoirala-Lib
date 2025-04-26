#include "derivative.h"
#include "pit.h"
#include "clock.h"

static void nothing(void) {};
static void (*function_pit1)(void) = nothing;
static void (*function_pit0)(void) = nothing;
static void (*function_pit2)(void) = nothing;
static void (*function_pit3)(void) = nothing;

unsigned int microT = 0;
unsigned long pit = 0;
unsigned long LiBchecker = 0;
unsigned long msCounter = 0;

unsigned long tick(unsigned int ms)
{
    return (busspeed * ((double)ms / 1000.00));
}

void timer(unsigned int ms)
{
    int i = 1;
    unsigned long tickPerSec = tick(ms);
    microT = 0;
    pit = 0;

    if (tickPerSec < 65000)
    {
        microT = 1;
        pit = tickPerSec + 1;
    }
    else
    {
        do
        {
            int remainder = (int)(tickPerSec % i);

            if (remainder == 0)
            {
                long div = (tickPerSec / i);

                if (div <= 65000)
                {
                    if (div * i == tickPerSec)
                    {
                        LiBchecker = 1;
                        microT = i;
                        pit = (tickPerSec / i);
                    }
                }
            }
            i++;

        } while (LiBchecker == 0);
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

        if (checker)
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

        if (checker)
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
        else if (ch == PIT_CH1)
        {
            PITLD1 = pst - 1;
        }
        else if (ch == PIT_CH2)
        {
            PITLD2 = pst - 1;
        }
        else if (ch == PIT_CH3)
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

    while (!(PITTF & ch))
        ;
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
    msCounter = 0;
}

void PIT_Delay_us(PIT_Channel ch, unsigned int us)
{
    unsigned int pst = (busspeed / 1000000) * us;

    PITMUX |= ch;

    PITMTLD1 = 1 - 1;

    if (ch == PIT_CH0)
    {
        PITLD0 = pst - 1;
    }
    else if (ch == PIT_CH1)
    {
        PITLD1 = pst - 1;
    }
    else if (ch == PIT_CH2)
    {
        PITLD2 = pst - 1;
    }
    else if (ch == PIT_CH3)
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

void Pit0_Callback(void (*function)(void))
{
    function_pit0 = function;
}
void Pit1_Callback(void (*function)(void))
{
    function_pit1 = function;
}
void Pit2_Callback(void (*function)(void))
{
    function_pit2 = function;
}
void Pit3_Callback(void (*function)(void))
{
    function_pit3 = function;
}

interrupt VectorNumber_Vpit0 void Vpit0_Handler(void)
{
    PITTF = PITTF_PTF0_MASK; // clear flag;
    function_pit0();
}
interrupt VectorNumber_Vpit1 void Vpit1_Handler(void)
{
    PITTF = PITTF_PTF1_MASK; // clear flag;
    function_pit1();
}
interrupt VectorNumber_Vpit2 void Vpit2_Handler(void)
{
    PITTF = PITTF_PTF2_MASK; // clear flag;
    function_pit2();
}
interrupt VectorNumber_Vpit3 void Vpit3_Handler(void)
{
    PITTF = PITTF_PTF3_MASK; // clear flag;
    function_pit3();
}

/*
    PITTF_PTF0_MASK - ch0
    PITTF_PTF1_MASK - ch1
    PITTF_PTF2_MASK - ch2
    PITTF_PTF3_MASK - ch3

    if(PITTF & PITTF_PTF1_MASK)
    {
      PITTF = PITTF_PTF1_MASK;
      SWL_TOG(SWL_GREEN);
    }

    VectorNumber_Vpit0 - ch0
    VectorNumber_Vpit1 - ch1
    VectorNumber_Vpit2 - ch2
    VectorNumber_Vpit3 - ch3

    interrupt VectorNumber_Vpit0 void Vpit0_Handler(void)
    {
        PITTF = PITTF_PTF0_MASK; //clear flag;
    }
*/