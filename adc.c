#include "adc.h"
#include "derivative.h"

static void nothings(void) {};
static void (*functions)(void) = nothings;

void ADC_Callback(void (*functs)(void))
{
  RTI_Init();
  functions = functs;
}

void ADC_Init(ADC_Con Convertion, ADC_ConSeq ConSeq, ADC_BehBP BehBp, ADC_Resolution Bit, ADC_TimeS TimeSelect, ADC_ClockPS Prescale)
{
  ATD0CTL2 = ATD0CTL2_ADPU_MASK | ATD0CTL2_AFFC_MASK | Convertion;

  ATD0CTL3 = ConSeq | BehBp;

  ATD0CTL4 = Bit | TimeSelect | Prescale;
}

void ADC_Wraps(ADC_Wrap WrapAround)
{
  ATD0CTL0 = WrapAround;
}

void ADC_Register5(ADC_Justi Justi, ADC_ConSeqM ConSeqM, ADC_MultiChM MultiCH, ADC_AnaInCH AnaINCH)
{
  ATD0CTL5 = Justi | MultiCH | ConSeqM | AnaINCH;
}

void ADC_Manual(ADC_Justi Justi, ADC_MultiChM MultiCH, ADC_AnaInCH AnaINCH)
{
  ATD0CTL5 = Justi | MultiCH | AnaINCH;
  while (!(ATD0STAT0 & ATD0STAT0_SCF_MASK))
    ;
}

interrupt VectorNumber_Vatd0 void Vatd0_ISR(void)
{
  ATD0STAT0 = ATD0STAT0_SCF_MASK; // flag clearing, not necessary here
  functions();
}