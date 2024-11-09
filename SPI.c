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

#include "SPI.h"
#include "fsl_dspi.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "fsl_clock.h"
#include "clock_config.h"

void configureSPI(void)
{
    uint32_t clockSource_LCD;
    uint32_t clockSource_Memory;

    CLOCK_SetSimSafeDivs();

    dspi_master_config_t lcdSPIConfig;
    dspi_master_config_t memorySPIConfig;

    /* Enable clocks for ports C and D */
    CLOCK_EnableClock(kCLOCK_PortC);
    CLOCK_EnableClock(kCLOCK_PortD);

    /* Configure LCD SPI pins */
    PORT_SetPinMux(PORTD, SPI_PIN0_IDX, kPORT_MuxAlt2);  /*!< PORTD0 configured as SPI0_PCS0 */
    PORT_SetPinMux(PORTD, SPI_PIN1_IDX, kPORT_MuxAlt2);  /*!< PORTD1 configured as SPI0_SCK */
    PORT_SetPinMux(PORTD, SPI_PIN2_IDX, kPORT_MuxAlt2);  /*!< PORTD2 configured as SPI0_SOUT */

    /* Configure Memory SPI pins */
    PORT_SetPinMux(PORTC, SPI_PIN3_IDX, kPORT_MuxAlt2);  /*!< PORTC3 configured as SPI0_PCS1 */
    PORT_SetPinMux(PORTD, SPI_PIN3_IDX, kPORT_MuxAlt2);  /*!< PORTD3 configured as SPI0_SOUT */

    /* LCD SPI Master Configuration */
    lcdSPIConfig.whichCtar = kDSPI_Ctar0;
    lcdSPIConfig.ctarConfig.baudRate = LCD_SPI_CLK_RATE;
    lcdSPIConfig.ctarConfig.bitsPerFrame = 8U;
    lcdSPIConfig.ctarConfig.cpol = kDSPI_ClockPolarityActiveHigh; /*!< SPI Mode 0 */
    lcdSPIConfig.ctarConfig.cpha = kDSPI_ClockPhaseFirstEdge;
    lcdSPIConfig.ctarConfig.direction = kDSPI_MsbFirst;
    lcdSPIConfig.ctarConfig.pcsToSckDelayInNanoSec = 1000000000U / LCD_SPI_CLK_RATE;
    lcdSPIConfig.ctarConfig.lastSckToPcsDelayInNanoSec = 1000000000U / LCD_SPI_CLK_RATE;
    lcdSPIConfig.ctarConfig.betweenTransferDelayInNanoSec = 1000000000U / LCD_SPI_CLK_RATE;

    lcdSPIConfig.whichPcs = kDSPI_Pcs0;
    lcdSPIConfig.pcsActiveHighOrLow = kDSPI_PcsActiveLow;
    lcdSPIConfig.enableContinuousSCK = false;
    lcdSPIConfig.enableRxFifoOverWrite = false;
    lcdSPIConfig.enableModifiedTimingFormat = false;
    lcdSPIConfig.samplePoint = kDSPI_SckToSin0Clock;

    clockSource_LCD = CLOCK_GetFreq(kCLOCK_BusClk);
    DSPI_MasterInit(SPI0, &lcdSPIConfig, clockSource_LCD);

    /* Memory SPI Master Configuration */
    memorySPIConfig.whichCtar = kDSPI_Ctar1;
    memorySPIConfig.ctarConfig.baudRate = MEMORY_SPI_CLK_RATE;
    memorySPIConfig.ctarConfig.bitsPerFrame = 8U;
    memorySPIConfig.ctarConfig.cpol = kDSPI_ClockPolarityActiveLow; /*!< SPI Mode 3 */
    memorySPIConfig.ctarConfig.cpha = kDSPI_ClockPhaseSecondEdge;
    memorySPIConfig.ctarConfig.direction = kDSPI_MsbFirst;
    memorySPIConfig.ctarConfig.pcsToSckDelayInNanoSec = 0;
    memorySPIConfig.ctarConfig.lastSckToPcsDelayInNanoSec = 0;
    memorySPIConfig.ctarConfig.betweenTransferDelayInNanoSec = 1000000000U / MEMORY_SPI_CLK_RATE;

    memorySPIConfig.whichPcs = kDSPI_Pcs1;
    memorySPIConfig.pcsActiveHighOrLow = kDSPI_PcsActiveLow;
    memorySPIConfig.enableContinuousSCK = false;
    memorySPIConfig.enableRxFifoOverWrite = false;
    memorySPIConfig.enableModifiedTimingFormat = false;
    memorySPIConfig.samplePoint = kDSPI_SckToSin0Clock;

    clockSource_Memory = CLOCK_GetFreq(DSPI0_CLK_SRC);
    DSPI_MasterInit(SPI0, &memorySPIConfig, clockSource_Memory);
}

