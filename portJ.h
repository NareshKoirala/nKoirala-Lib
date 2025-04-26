//RTI Module Library
//File: portJ.h (header file)
//Processor: MC9S12XDP512
//Crystal: 16 MHz


void PortJ_Init(unsigned int enableInt, unsigned int fallingEdge, unsigned int risingEdge);
void PortJ1_Callback(void(*function)(void));
void PortJ0_Callback(void(*function)(void));
void PortJ_Callback(void (*function)(void));