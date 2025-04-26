#include "derivative.h"
#include "rti.h"
#include "sw_led.h"

static void nothing(void) {};
static void (*function)(void) = nothing;

// This has to be declared as a global variable in rti.c
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
void RTI_InitCallback(void (*funct)(void))
{
  RTI_Init();
  function = funct;
}
void RTI_InitCallback_ms(void (*function)(void), int ms)
{
  if (RTI_NonB_Delay_ms(ms))
  {
    RTI_InitCallback(&function);
  }
}

/// @brief Blocking delay to be used  once the RTI MOdule is enabled
/// @param timeout
void RTI_Delay_ms(unsigned int ms)
{
  unsigned long start = rtiMasterCount;

  while ((rtiMasterCount - start) < ms)
  {
  };
}

int RTI_NonB_Delay_ms(unsigned int ms)
{
  if (ms <= rtiMasterCount)
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

interrupt VectorNumber_Vrti void Vrti_IRS(void)
{
  clear_flag();
  function();
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

// interrupt VectorNumber_Vsci0 void SCI_ISR(void)
// {
//    if(SCI0SR1 & SCI0SR1_RDRF_MASK)
//   {
//     //rxData = SCI0DRL;
//    // rxDataBuffer[rxDataIndex++] = SCI0DRL;
//   }

//   //receiving =1;
// }

/*
interrupt VectorNumber_Vpit0 void PIT0_ISR(void)
{
  PITTF = PITTF_PTF0_MASK; // clear
}
interrupt VectorNumber_Vpit1 void Vpit2_ISR(void)
{
  PITTF = PITTF_PTF1_MASK; // clear flag;
}

interrupt VectorNumber_Vsci0 void Vsci0_ISR(void)
{
  if (SCI0SR1 & SCI0SR1_RDRF_MASK)
  {
    data = SCI0DRL; // read character
    if (sci0_rxByte(&data))
    {
      if (data == '\r')
      {

      }
      else
      {
        myMessage[index++] = data;
      }
    }
  }
}*/

/*
    Port J initializations
  */
// Set PJ0 and PJ1 as inputs
//   DDRJ &= ~(DDRJ_DDRJ1_MASK | DDRJ_DDRJ0_MASK);
//  // //DDRJ_DDRJ1 = 0;
//  // //DDRJ_DDRJ0 = 0;

// ////Set edges for PJ0 and PJ1
// PPSJ |= PPSJ_PPSJ0_MASK;   //rising edge, RELEASE
// PPSJ &= ~PPSJ_PPSJ1_MASK;   //falling edge, PRESS

// // //Enable Interrupts for PJ1 and PJ0
// PIEJ |= PIEJ_PIEJ1_MASK | PIEJ_PIEJ0_MASK;
