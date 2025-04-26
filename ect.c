#include "ect.h"

void ECT_Init(unsigned int channel, ECT_ChannelMode mode, unsigned int actionOrEdge, unsigned int ticks)
{
    if (mode == ECT_MODE_OUTPUT_COMPARE)
    {
        TIOS |= (1 << channel);

        switch (channel)
        {
        case 0:
            TC0 = ticks;
            break;
        case 1:
            TC1 = ticks;
            break;
        case 2:
            TC2 = ticks;
            break;
        case 3:
            TC3 = ticks;
            break;
        case 4:
            TC4 = ticks;
            break;
        case 5:
            TC5 = ticks;
            break;
        case 6:
            TC6 = ticks;
            break;
        case 7:
            TC7 = ticks;
            break;
        default:
            break; // Invalid channel
        }

        // Set the action for Output Compare
        ECT_SetActionOrEdge(channel, actionOrEdge, &TCTL2, &TCTL1);
    }
    else if (mode == ECT_MODE_INPUT_CAPTURE)
    {
        TIOS &= ~(1 << channel);

        // Set the edge detection for Input Capture
        ECT_SetActionOrEdge(channel, actionOrEdge, &TCTL4, &TCTL3);
    }
}

// Helper function to set action for Output Compare or edge detection for Input Capture
void ECT_SetActionOrEdge(unsigned int channel, unsigned int actionOrEdge, volatile unsigned char *tctlLow, volatile unsigned char *tctlHigh)
{
    if (channel < 4)
    {
        *tctlLow = (*tctlLow & ~(0b11 << (channel * 2))) | (actionOrEdge << (channel * 2));
    }
    else
    {
        *tctlHigh = (*tctlHigh & ~(0b11 << ((channel - 4) * 2))) | (actionOrEdge << ((channel - 4) * 2));
    }
}

void ECT_InitLegacy(ECT_Prescale prescale)
{
    TSCR1 &= ~TSCR1_PRNT_MASK;
    TSCR2 |= prescale;
}

void ECT_InitPrecision(unsigned int prescaleValue)
{
    TSCR1 |= TSCR1_PRNT_MASK;
    PTPSR = prescaleValue - 1;
}
void ECT_InitCh7(void)
{
    TSCR2 |= TSCR2_TCRE_MASK; // ENABLE TO RESET TIMER WITH CHANNEL 7
}
// Clear flag for a channel
void ECT_ClearFlag(unsigned int channel)
{
    if (channel > 7)
        return;             // Validate channel
    TFLG1 = (1 << channel); // Write '1' to clear the flag
}

// Start the ECT timer
void ECT_StartTimer(void)
{
    TSCR1 |= TSCR1_TEN_MASK; // Enable timer
}

// Stop the ECT timer
void ECT_StopTimer(void)
{
    TSCR1 &= ~TSCR1_TEN_MASK; // Disable timer
}

// Enable interrupt for a channel
void ECT_EnableInterrupt(unsigned int channel)
{
    if (channel > 7)
        return; // Validate channel
    TIE |= (1 << channel);
}

// Disable interrupt for a channel
void ECT_DisableInterrupt(unsigned int channel)
{
    if (channel > 7)
        return; // Validate channel
    TIE &= ~(1 << channel);
}

// Enable or disable fast flag clearing
void ECT_SetFastFlagClearing(unsigned int enable)
{
    if (enable)
    {
        TSCR1 |= TSCR1_TFFCA_MASK; // Enable fast flag clearing
    }
    else
    {
        TSCR1 &= ~TSCR1_TFFCA_MASK; // Disable fast flag clearing
    }
}

void ECT_ConfigureOC7(ECT_OC7M_Mask mask, ECT_OC7M_Mask data)
{
    // Configure the OC7M register to select channels affected by TC7
    OC7M |= mask; // Enable the corresponding channels for TC7 events

    // Configure the OC7D register to set HIGH (1) or LOW (0) for the selected channels
    OC7D = (OC7D & ~mask) | (data & mask); // Update only the selected channels
}
