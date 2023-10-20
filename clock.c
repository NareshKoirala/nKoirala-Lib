#include "derivative.h"
#include "clock.h"





/// @brief Enable output specifying divider for it
/// @param  ClockOutDiv
void Clock_EnableOutput(ClockOutDiv);

/// @brief Set clock to 8MHZ(default, disable pll)
/// @param  
void Clock_Set8MHZ(void); 

/// @brief Set clock to 20MHZ using PLL
/// @param  void
void Clock_Set20MHZ(void)
{
    
}

/// @brief Set clock to 24MHZ using PLL
/// @param void 
void Clock_Set24MHZ(void);

/// @brief Set clock to 40MHZ using PLL (optional)
/// @param void 
void Clock_Set40MHZ(void); //Set clock to 40MHZ using PLL

/// @brief Get current clock speed
/// @param  void
/// @return current BUS speed
unsigned long Clock_GetBusSpeed(void);