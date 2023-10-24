#include "derivative.h"
#include "clock.h"
#include "sw_led.h"


/// @brief Enable output specifying divider for it
/// @param  ClockOutDiv
void Clock_EnableOutput(ClockOutDiv div)
{
    ECLKCTL &= ~ECLKCTL_NECLK_MASK; //Activate clock output 
    ECLKCTL |= ECLKCTL_EDIV1_MASK | div;//clock divide by what user desier 
}

/// @brief Set clock to 8MHZ(default, disable pll)
/// @param  
void Clock_Set8MHZ(void)
{
    CLKSEL &= ~CLKSEL_PLLSEL_MASK;
}

/// @brief Set clock to 20MHZ using PLL
/// @param  void
void Clock_Set20MHZ(void)
{
    clock_set(4,3);
}

/// @brief Set clock to 24MHZ using PLL
/// @param void 
void Clock_Set24MHZ(void)
{
    clock_set(2,1);
}

/// @brief Set clock to 40MHZ using PLL (optional)
/// @param void 
void Clock_Set40MHZ(void)//Set clock to 40MHZ using PLL
{
    clock_set(4, 1);
}

/// @brief Get current clock speed
/// @param  void
/// @return current BUS speed
unsigned long Clock_GetBusSpeed(void);

void clock_set(int synr, int refd)
{
    SYNR = synr;
    REFDV = refd;

    PLLCTL = PLLCTL_PLLON_MASK | PLLCTL_AUTO_MASK;

    while(!(CRGFLG & CRGFLG_LOCK_MASK));

    CLKSEL |= CLKSEL_PLLSEL_MASK;
}

//enable rti
//make rti to 1ms
void Enable_RTI(void)
{
    RTICTL = 0b10010111;
    CRGINT |= CRGINT_RTIE_MASK;
}

void clear_flag(void)
{
    CRGFLG = CRGFLG_RTIF_MASK;
}



