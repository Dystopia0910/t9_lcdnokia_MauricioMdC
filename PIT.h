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

#ifndef PIT_H_
#define PIT_H_

#include "stdint.h"

#define PIT_FLAG_OFF 0U
#define PIT_FLAG_ON 1U

#define PIT_SPI_CHANNEL kPIT_Chnl_1
#define SECONDS_TO_MICROSECONDS (1000000U)
#define SPI_PIT_BASEADDR PIT
#define SPI_CYCLES 20000000U

void PIT_SPI_init(void);
void PIT_SPI_set_time(uint8_t time_setting);
void PIT_SPI_start(void);
uint8_t PIT_SPI_get_irq_status(void);
void PIT_SPI_clear_irq_status(void);

#endif /* PIT_H_ */
