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

#ifndef LCD_NOKIA_H_
#define LCD_NOKIA_H_

#include "stdint.h"

// Definiciones del tamaño de la pantalla
#define LCD_WIDTH 84
#define LCD_HEIGHT 48

// Definiciones para comandos y datos
#define LCD_COMMAND 0
#define LCD_DATA 1

// Pines y puertos para control del LCD
#define PORT_DC_PIN PORTB
#define GPIO_DC_PIN GPIOB
#define DC_PIN 5
#define RESET_PIN 6
#define PORT_RST_PIN PORTB
#define GPIO_RST_PIN GPIOB
#define CE_PIN 7

// Prototipos de funciones
void LCD_nokia_init(void);
void LCD_nokia_send_byte(uint8_t data_or_command, uint8_t data);
void LCD_nokia_clear_screen(void);
void LCD_nokia_set_cursor(uint8_t x, uint8_t y);
void LCD_nokia_draw_bitmap(const uint8_t *bitmap);
void LCD_nokia_print_char(uint8_t character);
void LCD_nokia_print_string(const uint8_t *str);
void LCD_nokia_delay(void);

#endif /* LCD_NOKIA_H_ */
