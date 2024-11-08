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
#ifndef DEFINES_H_
#define DEFINES_H_

#define size_array_sine 160U
#define size_array_triangle 160U
#define size_array_sawtooth 82U
#define ZERO 0U
#define ONE 1U
#define TWO 2U
#define CYCLES 7000U
#define CYCLES_SECOND_FREQ 50U
#define CYCLES_THIRD_FREQ 1U

#define DAC_BASE_ADDRESS 0x400CC000U
#define OSCILLATOR_FREQ 1335000U

#endif /* DEFINES_H_ */
