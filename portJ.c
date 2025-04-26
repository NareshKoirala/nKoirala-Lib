#include "derivative.h"
#include "portJ.h"

static void nothing(void) {};
static void (*function_pj1)(void) = nothing;
static void (*function_pj0)(void) = nothing;
static void (*function_pj)(void) = nothing;

/// @brief main Initializng for port J
/// @param enableInt is enable interrupt needed
/// @param fallingEdge Either PPSJ_PPSJ1_MASK || PPSJ_PPSJ0_MASK
/// @param risingEdge Either PPSJ_PPSJ1_MASK || PPSJ_PPSJ0_MASK
void PortJ_Init(unsigned int enableInt, unsigned int fallingEdge, unsigned int risingEdge)
{
    /*
      Port J initializations
    */
    // Set PJ0 and PJ1 as inputs
    DDRJ &= ~(DDRJ_DDRJ1_MASK | DDRJ_DDRJ0_MASK);
    // DDRJ_DDRJ1 = 0;
    // DDRJ_DDRJ0 = 0;

    // Set edges for PJ0 and PJ1
    PPSJ |= risingEdge;   // rising edge, PRESS
    PPSJ &= ~fallingEdge; // falling edge, RELEASE

    if (enableInt)
    {
        // Enable Interrupts for PJ1 and PJ0
        PIEJ |= PIEJ_PIEJ1_MASK | PIEJ_PIEJ0_MASK;
    }
}

void PortJ0_Callback(void (*function)(void))
{
    function_pj0 = function;
}

void PortJ1_Callback(void (*function)(void))
{
    function_pj1 = function;
}

void PortJ_Callback(void (*function)(void))
{
    function_pj = function;
}

interrupt VectorNumber_Vportj void Vportj_ISR(void)
{
    if (PIFJ & PIFJ_PIFJ0_MASK)
    {
        // PJ0 detected an edge
        PIFJ = PIFJ_PIFJ0_MASK; // clear flag;
        function_pj0();
    }

    if (PIFJ & PIFJ_PIFJ1_MASK)
    {
        // PJ1 detected an edge
        PIFJ = PIFJ_PIFJ1_MASK; // clear flag;
        function_pj1();
    }
    function_pj();
}

// interrupt VectorNumber_Vportj  void Vportj_ISR(void)
// {
//   if(PIFJ & PIFJ_PIFJ0_MASK)
//   {//PJ0 detected an edge
//     PIFJ = PIFJ_PIFJ0_MASK; //clear flag;
//   }

//   if(PIFJ & PIFJ_PIFJ1_MASK)
//   {//PJ1 detected an edge
//     PIFJ = PIFJ_PIFJ1_MASK; //clear flag;

//   }
// }