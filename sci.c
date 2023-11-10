#include "derivative.h"
#include "sci.h"




//SCI0 - Normal mode: RDX0-> PS0 (PIN 89), TDX0-> PS1 (PIN 90)
// set baud, returns actual baud
unsigned long sci0_Init(unsigned long ulBaudRate, int budspeed)
{
  SCI0CR1 = 0;
  SCI0CR2 = SCI0CR2_TE_MASK | SCI0CR2_RE_MASK;

  SCI0BD = mathSCI(budspeed, ulBaudRate);
}

// blocking byte read
// waits for a byte to arrive and returns it
unsigned char sci0_bread(void);

// read a byte, non-blocking
// returns 1 if byte read, 0 if not
unsigned char sci0_rxByte(unsigned char * pData);

// send a byte over SCI
void sci0_txByte (unsigned char data)
{
  if(SCI0SR1 & SCI0SR1_TDRE_MASK)
    SCI0DRL = data;
}

// send a null-terminated string over SCI
void sci0_txStr (char const * straddr);


int mathSCI(unsigned long bus, unsigned long buadRate)
{
    return round((bus / (buadRate*16))+0.5);
}
