#include "derivative.h"
#include "rti.h"



//This has to be declared as a global variable in rti.c
extern volatile unsigned long rtiMasterCount;

/// @brief Enables RTI Moule
/// @param  
void RTI_Init(void)
{
    RTICTL = 0b10010111;
    CRGINT |= CRGINT_RTIE_MASK;

    rtiMasterCount = 0;
}

/// @brief Enables RTI Module with callback to be used in main
/// @param function 
/*
We will implemente this function later once we cover 
function pointers
*/
void RTI_InitCallback(void(*function)(void));

/// @brief Blocking delay to be used  once the RTI MOdule is enabled
/// @param timeout 
int RTI_Delay_ms(unsigned int ms)
{
    if(ms == rtiMasterCount)
    { 
        rtiMasterCount = 0;
        return 1;
    }
    return 0;
}

void clear_flag(void)
{
    CRGFLG = CRGFLG_RTIF_MASK;
    rtiMasterCount++;
}


