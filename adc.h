#include "derivative.h"

typedef enum ADC_Convertion_seq
{
    ADC_CS1 = ATD0CTL3_S1C_MASK,
    ADC_CS2 = ATD0CTL3_S2C_MASK,
    ADC_CS3 = ATD0CTL3_S2C_MASK | ATD0CTL3_S1C_MASK,
    ADC_CS4 = ATD0CTL3_S4C_MASK,
    ADC_CS5 = ATD0CTL3_S4C_MASK | ATD0CTL3_S1C_MASK,
    ADC_CS6 = ATD0CTL3_S4C_MASK | ATD0CTL3_S2C_MASK,
    ADC_CS7 = ATD0CTL3_S4C_MASK | ATD0CTL3_S2C_MASK | ATD0CTL3_S1C_MASK,
    ADC_CS8 = ATD0CTL3_S8C_MASK
}ADC_ConSeq;

typedef enum ADC_Behavior_BP
{
    ADC_Continues = 0,
    ADC_Reserved = ATD0CTL3_FRZ0_MASK,
    ADC_Finish_Freeze = ATD0CTL3_FRZ1_MASK,
    ADC_Freeze = ATD0CTL3_FRZ1_MASK | ATD0CTL3_FRZ0_MASK
}ADC_BehBP;

typedef enum ADC_Resolution
{
    ADC_10_Bit = 0b00000000,
    ADC_08_Bit = 0b10000000
}ADC_Resolution;

typedef enum ADC_Convertion
{
    ADC_AWAI = ATD0CTL2_AWAI_MASK,
    ADC_ASCIE = ATD0CTL2_ASCIE_MASK
}ADC_Con;


typedef enum ADC_Time_Select
{
    ADC_02AD = 0,
    ADC_04AD = ATD0CTL4_SMP0_MASK,
    ADC_08AD = ATD0CTL4_SMP1_MASK,
    ADC_16AD = ATD0CTL4_SMP0_MASK | ATD0CTL4_SMP1_MASK
}ADC_TimeS;


typedef enum ADC_Clock_Prescale
{
    ADC_08PS = ATD0CTL4_PRS0_MASK | ATD0CTL4_PRS1_MASK,
    ADC_10PS = ATD0CTL4_PRS2_MASK,
    ADC_20PS = ATD0CTL4_PRS3_MASK | ATD0CTL4_PRS0_MASK
}ADC_ClockPS;

typedef enum ADC_Wrap_Around
{
    ADC_Reserve =  0,
    ADC_AN1 = ATD0CTL0_WRAP0_MASK,
    ADC_AN2 = ATD0CTL0_WRAP1_MASK,
    ADC_AN3 = ATD0CTL0_WRAP1_MASK | ATD0CTL0_WRAP0_MASK,
    ADC_AN4 = ATD0CTL0_WRAP2_MASK,
    ADC_AN5 = ATD0CTL0_WRAP2_MASK | ATD0CTL0_WRAP0_MASK,
    ADC_AN6 = ATD0CTL0_WRAP2_MASK | ATD0CTL0_WRAP1_MASK,
    ADC_AN7 = ATD0CTL0_WRAP2_MASK | ATD0CTL0_WRAP1_MASK | ATD0CTL0_WRAP0_MASK
}ADC_Wrap;

typedef enum ADC_Justified_Data
{
    ADC_LEFT = 0,
    ADC_RIGHT = ATD0CTL5_DJM_MASK
}ADC_Justi;

typedef enum ADC_ConSeq_Mode
{
    ADC_SINGLE = 0,
    ADC_CONTINUOUS = ATD0CTL5_SCAN_MASK
}ADC_ConSeqM;


typedef enum ADC_MultiSample_CH_Mode
{
    ADC_ONE = 0,
    ADC_MULTI = ATD0CTL5_MULT_MASK
}ADC_MultiChM;


typedef enum ADC_Analog_Input_CHannel
{
    ADC_AN0_CH =  0,
    ADC_AN1_CH = ATD0CTL5_CA_MASK,
    ADC_AN2_CH = ATD0CTL5_CB_MASK,
    ADC_AN3_CH = ATD0CTL5_CB_MASK | ATD0CTL5_CA_MASK,
    ADC_AN4_CH = ATD0CTL5_CC_MASK,
    ADC_AN5_CH = ATD0CTL5_CC_MASK | ATD0CTL5_CA_MASK,
    ADC_AN6_CH = ATD0CTL5_CC_MASK | ATD0CTL5_CB_MASK,
    ADC_AN7_CH = ATD0CTL5_CC_MASK | ATD0CTL5_CB_MASK | ATD0CTL5_CA_MASK
}ADC_AnaInCH;

/// @brief ADC Init Function
/// @param Convertion Wait Mode / Interrupt enable
/// @param ConSeq Number of conversion per sequence
/// @param BehBp finish current conversion then freeze
/// @param Bit 10-bit, 08-bit resolution
/// @param TimeSelect A/D coversion clock periods
/// @param Prescale prescaler ADC-Clock
void ADC_Init(ADC_Con Convertion, ADC_ConSeq ConSeq, ADC_BehBP BehBp, ADC_Resolution Bit, ADC_TimeS TimeSelect, ADC_ClockPS Prescale);

/// @brief 
/// @param Justi 
/// @param MultiCH 
/// @param AnaINCH 
void ADC_Manual(ADC_Justi Justi,  ADC_MultiChM MultiCH, ADC_AnaInCH AnaINCH);

/// @brief 
/// @param WrapAround 
void ADC_Wraps(ADC_Wrap WrapAround);

/// @brief 
/// @param Justi 
/// @param ConSeqM 
/// @param MultiCH 
/// @param AnaINCH 
void ADC_Register5(ADC_Justi Justi,  ADC_ConSeqM ConSeqM, ADC_MultiChM MultiCH, ADC_AnaInCH AnaINCH);

/// @brief 
/// @param functs 
void ADC_Callback(void (*functs)(void));