#include "derivative.h"
#include "sci.h"
#include "clock.h"


//SCI0 - Normal mode: RDX0-> PS0 (PIN 89), TDX0-> PS1 (PIN 90)
// set baud, returns actual baud
unsigned long sci0_Init(unsigned long ulBaudRate, int iRDRF_Interrupt )
{
  SCI0CR1 = 0;

  if(iRDRF_Interrupt)
    SCI0CR2 = SCI0CR2_TE_MASK | SCI0CR2_RE_MASK | SCI0CR2_RIE_MASK;
  else
    SCI0CR2 = SCI0CR2_TE_MASK | SCI0CR2_RE_MASK;
  
  SCI0BD = mathSCI(busspeed , ulBaudRate);
}

// blocking byte read
// waits for a byte to arrive and returns it
unsigned char sci0_bread(void)
{
  unsigned char data;
  
  while(!(SCI0SR1 & SCI0SR1_RDRF_MASK))
    data = SCI0DRL;
  
  return data;
}

// read a byte, non-blocking
// returns 1 if byte read, 0 if not
unsigned char sci0_rxByte(unsigned char * pData)
{
  if (SCI0SR1 & SCI0SR1_RDRF_MASK)
  {
    *pData = SCI0DRL;
    return 1;
  }
  return 0;
}

// send a byte over SCI
void sci0_txByte (unsigned char data)
{
  while(!(SCI0SR1_TDRE))
    SCI0DRL = data;
}

// send a null-terminated string over SCI
void sci0_txStr (char const * straddr)
{   
  int i ;
  for (i=0; straddr[i] != 0; i++)
  {
    while(!(SCI0SR1 & SCI0SR1_TDRE_MASK));
    SCI0DRL = straddr[i];
  }
}


int mathSCI(unsigned long bus, unsigned long buadRate)
{
    return (int)((bus / (buadRate*16))+0.5);
}
