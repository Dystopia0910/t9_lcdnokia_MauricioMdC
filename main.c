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


#include "LCD_nokia.h"
#include "LCD_nokia_img.h"
#include "stdint.h"
#include "SPI.h"
#include "SPI_mem.h"
#include "PIT.h"
#include <stdbool.h>


int main(void)
{
	// Configuración inicial de SPI para LCD y memoria
	SPI_setup();
	LCD_nokia_init(); 	// Inicialización del LCD

	// Inicialización del PIT
	PIT_init();

	// Contadores y dirección base de la memoria de imágenes
	uint8_t img_index = 0U;
	uint16_t byte_pos = 0U;
	uint8_t img_buffer[IMG_LENGTH] = {0U};
	uint32_t current_mem_address = BASE_ADDR_MEMORY;
	uint8_t *ITESO_logo = ITESO_IMG();

	// Bucle infinito para visualizar continuamente las 6 imágenes
	for(;;)
	{
		if(TRUE == PIT0_get_flag())
		{
			img_index++;
			LCD_nokia_clear_screen(); // Limpia el LCD antes de mostrar nueva imagen

			if(TOTAL_IMG != img_index)
			{
				while(byte_pos < IMG_LENGTH)
				{
					img_buffer[byte_pos] = read_memory_byte(current_mem_address);
					byte_pos++;
					current_mem_address++;
				}

				byte_pos = 0U;
				LCD_nokia_display_bitmap(img_buffer);
				current_mem_address += ELEMENTS_TO_NEXT_IMG;

				if(NO_MORE_IMG_ADDRSS == current_mem_address)
				{
					current_mem_address = BASE_ADDR_MEMORY;
				}
			}
			else
			{
				LCD_nokia_display_bitmap(ITESO_logo);
				img_index = 0U;
			}

			PIT0_reset_flag();
		}
	}
	return 0;
}
