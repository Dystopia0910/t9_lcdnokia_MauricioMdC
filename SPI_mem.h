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

#ifndef SPI_MEM_H_
#define SPI_MEM_H_

#include "stdint.h"

/* Definiciones de memoria */
#define BASE_ADDR_MEMORY    0x40000U
#define MEM_READ_CMD        0x03U
#define SHIFT_TWO_BYTES     16U
#define SHIFT_ONE_BYTE      8U
#define BYTE_ZERO           0U
#define BYTE_ONE            1U
#define FOUR_BYTES          4U

uint8_t read_memory_byte(uint32_t address);

#endif /* SPI_MEM_H_ */
