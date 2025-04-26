#include "pwm.h"

// Initialize PWM for a specific channel
void PWM_Init(Clock_Prescaler prescale, unsigned int channel, PWM_ClockSource clockSource, PWM_ClockSource clock, unsigned int SAorSB, PWM_Polarity polarity, unsigned int period, unsigned int duty)
{
    PWMPRCLK |= prescale;

    if (clock == PWM_CLOCK_A && clockSource == PWM_CLOCK_SCALED)
    {
        PWMSCLA = SAorSB;
    }
    else if (clock == PWM_CLOCK_B && clockSource == PWM_CLOCK_SCALED)
    {
        PWMSCLB = SAorSB;
    }

    switch (channel)
    {
    case 0:
        if (clockSource == PWM_CLOCK_SCALED)
        {
            PWMCLK |= PWMCLK_PCLK0_MASK; // Use scaled Clock SA for PWM0
        }
        else
        {
            PWMCLK &= ~PWMCLK_PCLK0_MASK; // Use default Clock A for PWM0
        }
        break;
    case 1:
        if (clockSource == PWM_CLOCK_SCALED)
        {
            PWMCLK |= PWMCLK_PCLK1_MASK; // Use scaled Clock SA for PWM1
        }
        else
        {
            PWMCLK &= ~PWMCLK_PCLK1_MASK; // Use default Clock A for PWM1
        }
        break;
    case 2:
        if (clockSource == PWM_CLOCK_SCALED)
        {
            PWMCLK |= PWMCLK_PCLK2_MASK; // Use scaled Clock SB for PWM2
        }
        else
        {
            PWMCLK &= ~PWMCLK_PCLK2_MASK; // Use default Clock B for PWM2
        }
        break;
    case 3:
        if (clockSource == PWM_CLOCK_SCALED)
        {
            PWMCLK |= PWMCLK_PCLK3_MASK; // Use scaled Clock SB for PWM3
        }
        else
        {
            PWMCLK &= ~PWMCLK_PCLK3_MASK; // Use default Clock B for PWM3
        }
        break;
    case 4:
        if (clockSource == PWM_CLOCK_SCALED)
        {
            PWMCLK |= PWMCLK_PCLK4_MASK; // Use scaled Clock SA for PWM4
        }
        else
        {
            PWMCLK &= ~PWMCLK_PCLK4_MASK; // Use default Clock A for PWM4
        }
        break;
    case 5:
        if (clockSource == PWM_CLOCK_SCALED)
        {
            PWMCLK |= PWMCLK_PCLK5_MASK; // Use scaled Clock SA for PWM5
        }
        else
        {
            PWMCLK &= ~PWMCLK_PCLK5_MASK; // Use default Clock A for PWM5
        }
        break;
    case 6:
        if (clockSource == PWM_CLOCK_SCALED)
        {
            PWMCLK |= PWMCLK_PCLK6_MASK; // Use scaled Clock SB for PWM6
        }
        else
        {
            PWMCLK &= ~PWMCLK_PCLK6_MASK; // Use default Clock B for PWM6
        }
        break;
    case 7:
        if (clockSource == PWM_CLOCK_SCALED)
        {
            PWMCLK |= PWMCLK_PCLK7_MASK; // Use scaled Clock SB for PWM7
        }
        else
        {
            PWMCLK &= ~PWMCLK_PCLK7_MASK; // Use default Clock B for PWM7
        }
        break;
    default:
        return; // Invalid channel
    }

    if (polarity == PWM_POLARITY_HIGH)
    {
        PWMPOL |= (1 << channel); // Set polarity to HIGH for specified channel
    }
    else
    {
        PWMPOL &= ~(1 << channel); // Set polarity to LOW for specified channel
    }

    // Set period and duty cycle for the channel
    switch (channel) {
        case 0:
            PWMPER0 = period;
            PWMDTY0 = duty;
            break;
        case 1:
            PWMPER1 = period;
            PWMDTY1 = duty;
            break;
        case 2:
            PWMPER2 = period;
            PWMDTY2 = duty;
            break;
        case 3:
            PWMPER3 = period;
            PWMDTY3 = duty;
            break;
        case 4:
            PWMPER4 = period;
            PWMDTY4 = duty;
            break;
        case 5:
            PWMPER5 = period;
            PWMDTY5 = duty;
            break;
        case 6:
            PWMPER6 = period;
            PWMDTY6 = duty;
            break;
        case 7:
            PWMPER7 = period;
            PWMDTY7 = duty;
            break;
        default:
            return; // Invalid channel
    }
}

// Update the duty cycle for a specific channel
void PWM_SetDutyCycle(unsigned int channel, unsigned int duty)
{
    switch (channel)
    {
    case 0:
        PWMDTY0 = duty;
        break;
    case 1:
        PWMDTY1 = duty;
        break;
    case 2:
        PWMDTY2 = duty;
        break;
    case 3:
        PWMDTY3 = duty;
        break;
    case 4:
        PWMDTY4 = duty;
        break;
    case 5:
        PWMDTY5 = duty;
        break;
    case 6:
        PWMDTY6 = duty;
        break;
    case 7:
        PWMDTY7 = duty;
        break;
    default:
        return; // Invalid channel
    }
}

// Update the period for a specific channel
void PWM_SetPeriod(unsigned int channel, unsigned int period)
{
    switch (channel)
    {
    case 0:
        PWMPER0 = period;
        break;
    case 1:
        PWMPER1 = period;
        break;
    case 2:
        PWMPER2 = period;
        break;
    case 3:
        PWMPER3 = period;
        break;
    case 4:
        PWMPER4 = period;
        break;
    case 5:
        PWMPER5 = period;
        break;
    case 6:
        PWMPER6 = period;
        break;
    case 7:
        PWMPER7 = period;
        break;
    default:
        return; // Invalid channel
    }
}


// Enable the PWM channel using masks from derivative.h
void PWM_EnableChannel(unsigned int channel)
{
    switch (channel)
    {
    case 0:
        PWME |= PWME_PWME0_MASK;
        break;
    case 1:
        PWME |= PWME_PWME1_MASK;
        break;
    case 2:
        PWME |= PWME_PWME2_MASK;
        break;
    case 3:
        PWME |= PWME_PWME3_MASK;
        break;
    case 4:
        PWME |= PWME_PWME4_MASK;
        break;
    case 5:
        PWME |= PWME_PWME5_MASK;
        break;
    case 6:
        PWME |= PWME_PWME6_MASK;
        break;
    case 7:
        PWME |= PWME_PWME7_MASK;
        break;
    }
}

// Disable the PWM channel using masks from derivative.h
void PWM_DisableChannel(unsigned int channel)
{
    switch (channel)
    {
    case 0:
        PWME &= ~PWME_PWME0_MASK;
        break;
    case 1:
        PWME &= ~PWME_PWME1_MASK;
        break;
    case 2:
        PWME &= ~PWME_PWME2_MASK;
        break;
    case 3:
        PWME &= ~PWME_PWME3_MASK;
        break;
    case 4:
        PWME &= ~PWME_PWME4_MASK;
        break;
    case 5:
        PWME &= ~PWME_PWME5_MASK;
        break;
    case 6:
        PWME &= ~PWME_PWME6_MASK;
        break;
    case 7:
        PWME &= ~PWME_PWME7_MASK;
        break;
    }
}
