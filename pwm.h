#include "derivative.h"  // Include derivative definitions

// Enum for clock source selection
typedef enum PWM_TypeClockSource
{
    PWM_CLOCK_DEFAULT = 0,   // Default Clock (Clock A or Clock B)
    PWM_CLOCK_SCALED = 1 ,   // Scaled Clock (Clock SA or Clock SB)
    PWM_CLOCK_A = 2,
    PWM_CLOCK_B = 3 
} PWM_ClockSource;

// Enum for polarity configuration
typedef enum PWM_TypePolarity
{
    PWM_POLARITY_LOW = 0, // Starts LOW
    PWM_POLARITY_HIGH = 1 // Starts HIGH
} PWM_Polarity;

typedef enum Clock_TypePrescaler
{
    CLOCK_A_DIV_1   = 0,                                                    // PCKA = 000
    CLOCK_A_DIV_2   = PWMPRCLK_PCKA0_MASK,                                  // PCKA = 001
    CLOCK_A_DIV_4   = PWMPRCLK_PCKA1_MASK,                                  // PCKA = 010
    CLOCK_A_DIV_8   = PWMPRCLK_PCKA1_MASK | PWMPRCLK_PCKA0_MASK,            // PCKA = 011
    CLOCK_A_DIV_16  = PWMPRCLK_PCKA2_MASK,                                  // PCKA = 100
    CLOCK_A_DIV_32  = PWMPRCLK_PCKA2_MASK | PWMPRCLK_PCKA0_MASK,            // PCKA = 101
    CLOCK_A_DIV_64  = PWMPRCLK_PCKA2_MASK | PWMPRCLK_PCKA1_MASK,            // PCKA = 110
    CLOCK_A_DIV_128 = PWMPRCLK_PCKA2_MASK | PWMPRCLK_PCKA1_MASK | PWMPRCLK_PCKA0_MASK,  // PCKA = 111
    CLOCK_B_DIV_1   = 0,                                                    // PCKB = 000
    CLOCK_B_DIV_2   = PWMPRCLK_PCKB0_MASK,                                  // PCKB = 001
    CLOCK_B_DIV_4   = PWMPRCLK_PCKB1_MASK,                                  // PCKB = 010
    CLOCK_B_DIV_8   = PWMPRCLK_PCKB1_MASK | PWMPRCLK_PCKB0_MASK,            // PCKB = 011
    CLOCK_B_DIV_16  = PWMPRCLK_PCKB2_MASK,                                  // PCKB = 100
    CLOCK_B_DIV_32  = PWMPRCLK_PCKB2_MASK | PWMPRCLK_PCKB0_MASK,            // PCKB = 101
    CLOCK_B_DIV_64  = PWMPRCLK_PCKB2_MASK | PWMPRCLK_PCKB1_MASK,            // PCKB = 110
    CLOCK_B_DIV_128 = PWMPRCLK_PCKB2_MASK | PWMPRCLK_PCKB1_MASK | PWMPRCLK_PCKB0_MASK  // PCKB = 111
} Clock_Prescaler;

// Function Prototypes

/**
 * @brief Initializes a PWM channel with specified prescaler, clock source, polarity, period, and duty cycle.
 *
 * @param prescale    Clock prescaler for frequency division.
 * @param channel     PWM channel to configure (0-7).
 * @param clockSource Selects default or scaled clock for PWM (e.g., `PWM_CLOCK_DEFAULT`, `PWM_CLOCK_SCALED`).
 * @param clock       Primary clock (Clock A or Clock B) for the PWM channel.
 * @param SAorSB      Scaling factor for scaled clock (SA or SB) if `clockSource` is `PWM_CLOCK_SCALED`.
 * @param polarity    Initial polarity of the PWM signal (`PWM_POLARITY_HIGH` or `PWM_POLARITY_LOW`).
 * @param period      PWM signal period in timer ticks.
 * @param duty        PWM signal duty cycle in timer ticks (high time within one period).
 */
void PWM_Init(Clock_Prescaler prescale, unsigned int channel, PWM_ClockSource clockSource, PWM_ClockSource clock, unsigned int SAorSB, PWM_Polarity polarity, unsigned int period, unsigned int duty);

/**
 * @brief Set the duty cycle of a specific PWM channel.
 * 
 * @param channel PWM channel number (0-7).
 * @param duty New duty cycle value.
 */
void PWM_SetDutyCycle(unsigned int channel, unsigned int duty);

/**
 * @brief Enable a specific PWM channel.
 * 
 * @param channel PWM channel number (0-7).
 */
void PWM_EnableChannel(unsigned int channel);


/**
 * @brief Update the period for a specific PWM channel.
 *
 * @param channel The PWM channel to update (0-7).
 * @param period The new period value in timer ticks.
 */
void PWM_SetPeriod(unsigned int channel, unsigned int period);

/**
 * @brief Disable a specific PWM channel.
 * 
 * @param channel PWM channel number (0-7).
 */
void PWM_DisableChannel(unsigned int channel);