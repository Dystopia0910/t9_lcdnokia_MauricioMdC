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

/** Archivos de cabecera incluidos */
#include "SPI_mem.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "SPI.h"
#include "stdint.h"
#include "fsl_dspi.h"

/** Función para leer un byte desde la memoria */
uint8_t read_memory_byte(uint32_t address)
{
    /*
     * Configuración de transferencia en modo half-duplex.
     * La memoria requiere comunicación bidireccional:
     */
    dspi_half_duplex_transfer_t transferConfig;

    /** Comando de lectura (0x03) y la dirección dividida en bytes: */
    uint8_t cmd_and_address[] = {MEM_READ_CMD, (address >> SHIFT_TWO_BYTES),
                                 ((address & 0x0FF00) >> SHIFT_ONE_BYTE), address & 0x000FF};
    uint8_t data_buffer[1] = {0};

    transferConfig.txData       = cmd_and_address;
    transferConfig.rxData       = data_buffer;
    transferConfig.txDataSize   = FOUR_BYTES;
    transferConfig.rxDataSize   = BYTE_ONE;
    transferConfig.configFlags  = kDSPI_MasterCtar1 | kDSPI_MasterPcs1 | kDSPI_MasterPcsContinuous;
    transferConfig.isPcsAssertInTransfer = true;
    transferConfig.isTransmitFirst       = true;

    DSPI_MasterHalfDuplexTransferBlocking(SPI0, &transferConfig);

    return data_buffer[0];
}
