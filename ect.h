#include "derivative.h"

typedef enum ECT_TypePrescale
{
    ECT_PRESCALE_1 = 0,                                                 // Prescaler factor 1
    ECT_PRESCALE_2 = TSCR2_PR0_MASK,                                    // Prescaler factor 2
    ECT_PRESCALE_4 = TSCR2_PR1_MASK,                                    // Prescaler factor 4
    ECT_PRESCALE_8 = TSCR2_PR1_MASK | TSCR2_PR0_MASK,                   // Prescaler factor 8
    ECT_PRESCALE_16 = TSCR2_PR2_MASK,                                   // Prescaler factor 16
    ECT_PRESCALE_32 = TSCR2_PR2_MASK | TSCR2_PR0_MASK,                  // Prescaler factor 32
    ECT_PRESCALE_64 = TSCR2_PR2_MASK | TSCR2_PR1_MASK,                  // Prescaler factor 64
    ECT_PRESCALE_128 = TSCR2_PR2_MASK | TSCR2_PR1_MASK | TSCR2_PR0_MASK // Prescaler factor 128
} ECT_Prescale;

typedef enum ECT_Type
{
    ECT_LEGACY = 0,
    ECT_PRECISION = 1
} ECT_Type;

// Modes for channels
typedef enum ECT_ChannelModeType
{
    ECT_MODE_OUTPUT_COMPARE,
    ECT_MODE_INPUT_CAPTURE
} ECT_ChannelMode;

// Actions for Output Compare
typedef enum
{
    ECT_ACTION_DISCONNECT = 0b00,
    ECT_ACTION_TOGGLE = 0b01,
    ECT_ACTION_CLEAR = 0b10,
    ECT_ACTION_SET = 0b11
} ECT_OutputAction;

// Edge detection for Input Capture
typedef enum
{
    ECT_EDGE_RISING = 0b01,
    ECT_EDGE_FALLING = 0b10,
    ECT_EDGE_BOTH = 0b11
} ECT_EdgeDetection;

typedef enum {
    
    ECT_OC7M_LOW = 0,               // Mask for channel Low
    ECT_OC7M_CH0 = OC7M_OC7M0_MASK, // Mask for channel 0
    ECT_OC7M_CH1 = OC7M_OC7M1_MASK, // Mask for channel 1
    ECT_OC7M_CH2 = OC7M_OC7M2_MASK, // Mask for channel 2
    ECT_OC7M_CH3 = OC7M_OC7M3_MASK, // Mask for channel 3
    ECT_OC7M_CH4 = OC7M_OC7M4_MASK, // Mask for channel 4
    ECT_OC7M_CH5 = OC7M_OC7M5_MASK, // Mask for channel 5
    ECT_OC7M_CH6 = OC7M_OC7M6_MASK, // Mask for channel 6
    ECT_OC7M_CH7 = OC7M_OC7M7_MASK  // Mask for channel 7
} ECT_OC7M_Mask;


void ECT_InitLegacy(ECT_Prescale prescale);

void ECT_InitPrecision(unsigned int prescaleValue);

void ECT_Init(unsigned int channel, ECT_ChannelMode mode, unsigned int actionOrEdge, unsigned int ticks);

void ECT_SetActionOrEdge(unsigned int channel, unsigned int actionOrEdge, volatile unsigned char *tctlLow, volatile unsigned char *tctlHigh);

void ECT_EnableInterrupt(unsigned int channel);
void ECT_DisableInterrupt(unsigned int channel);
void ECT_ClearFlag(unsigned int channel);
void ECT_StartTimer(void);
void ECT_StopTimer(void);
void ECT_SetFastFlagClearing(unsigned int enable);
void ECT_InitCh7(void);


/**
 * @brief Configure OC7M and OC7D registers for TC7 compare events.
 *
 * @param mask A combination of `ECT_OC7M_Mask` values (e.g., `ECT_OC7M_CH0 | ECT_OC7M_CH1`) for selecting affected channels.
 * @param data A combination of `ECT_OC7M_Mask` values to specify HIGH (1) or LOW (0) for each channel.
 */
void ECT_ConfigureOC7(ECT_OC7M_Mask mask, ECT_OC7M_Mask data);