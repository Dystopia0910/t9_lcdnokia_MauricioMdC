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

#ifndef SPI_H_
#define SPI_H_

#define LCD_SPI_CLK_RATE      1000000U  /*!< LCD clock rate in Hz */
#define MEMORY_SPI_CLK_RATE   2000000U  /*!< Memory clock rate in Hz */

#define LCD_TRANSFER_SIZE     64U       /*!< LCD Transfer Size */
#define MEMORY_TRANSFER_SIZE  64U       /*!< Memory Transfer Size */

/* Pin definitions */
#define SPI_PIN0_IDX          0U        /*!< Port D pin 0 */
#define SPI_PIN1_IDX          1U        /*!< Port D pin 1 */
#define SPI_PIN2_IDX          2U        /*!< Port D pin 2 */
#define SPI_PIN3_IDX          3U        /*!< Port C pin 3 */
#define SPI_PIN16_IDX         16U       /*!< Port C pin 16 */
#define SPI_PIN17_IDX         17U       /*!< Port C pin 17 */

void configureSPI(void);

#endif /* SPI_H_ */
