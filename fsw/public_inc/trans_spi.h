/* Linux Userspace SPI I/O header */

#ifndef IO_LIB_TRANS_SPI_H_
#define IO_LIB_TRANS_SPI_H_

#include "common_types.h"
#include "io_lib.h"
// #include <linux/spi/spi.h>
#include <linux/spi/spidev.h>

#define SPI_PORT_NAME_SIZE (20)

typedef struct {
    char   device[SPI_PORT_NAME_SIZE]; /* Device name (eg: "/dev/spidev0.0") */
    int32  baudRate;                   /* Baud Rate in bytes per second.     */
    uint32 spiMode;                    /* SPI_MODE_0, 1, 2, 3                */
    uint32 spiSpeed;                   /* Bits per second                    */
    uint32 bitsPerWord;                /* Bits per word                      */
} IO_TransSpiConfig_t;

int32 IO_TransSPIInit(IO_TransSpiConfig_t *config);
int32 IO_TransSPIClose(int32 fd);
int32 IO_TransSPIRead(int32 fd, uint8 *buffer, int32 numBytes);
int32 IO_TransSPIWrite(int32 fd, uint8 *msg, int32 size);

#endif // IO_LIB_TRANS_SPI_H_
