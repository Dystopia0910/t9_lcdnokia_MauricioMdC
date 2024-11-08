/**
 * @file
 * @brief
 * This is the source file for the MVC device driver for Kinetis K64.
 * It contains some configuration functions and runtime functions.
 * It is implemented using CMSIS Core functions.
 *
 * @authors: Mauricio Martin Del Campo
 * @date 02/10/2024
 *
 * @todo
 *
 */

#include <PIT.h>
#include "fsl_pit.h"
#include "fsl_common.h"

/** PIT interrupt flag */
static volatile bool pitSpiFlag = PIT_FLAG_OFF;

/** Initialize PIT for SPI timing */
void PIT_SPI_init()
{
    pit_config_t pitConfig;
    PIT_GetDefaultConfig(&pitConfig);
    PIT_Init(SPI_PIT_BASEADDR, &pitConfig);
    PIT_SPI_set_time(20);  // Arbitrary time setting for initialization

    /* Enable timer interrupts for SPI channel */
    PIT_EnableInterrupts(SPI_PIT_BASEADDR, PIT_SPI_CHANNEL, kPIT_TimerInterruptEnable);

    /* Enable NVIC interrupt */
    EnableIRQ(PIT1_IRQn);

    /* Start the timer */
    PIT_StartTimer(SPI_PIT_BASEADDR, PIT_SPI_CHANNEL);
}

/** Set the timer period of PIT channel for SPI */
void PIT_SPI_set_time(uint8_t time_setting)
{
    uint32_t cycles = SPI_CYCLES / time_setting;
    PIT_SetTimerPeriod(SPI_PIT_BASEADDR, PIT_SPI_CHANNEL, cycles);
}

/* PIT1 interrupt handler */
void PIT1_IRQHandler(void)
{
    /* Clear interrupt flag */
    PIT_ClearStatusFlags(SPI_PIT_BASEADDR, PIT_SPI_CHANNEL, kPIT_TimerFlag);
    pitSpiFlag = PIT_FLAG_ON;
    __DSB();  // Ensure all memory access completes
}

/** Check the interrupt status of the PIT channel for SPI */
uint8_t PIT_SPI_get_irq_status()
{
    return pitSpiFlag;
}

/** Clear the interrupt status flag */
void PIT_SPI_clear_irq_status()
{
    pitSpiFlag = PIT_FLAG_OFF;
}



