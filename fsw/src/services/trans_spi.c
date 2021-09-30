/* Linux Userspace SPI I/O routines */

#include "trans_spi.h"
#include "cfe_es.h"
#include "cfe_evs.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#define IO_TRANS_SPI_OPEN_FLAGS  (O_RDWR | O_NONBLOCK)

int32 IO_TransSPIInit(IO_TransSpiConfig_t *config)
{
    int32 fd = open(config->device, IO_TRANS_SPI_OPEN_FLAGS);

    if (fd < 0)
    {
        CFE_ES_WriteToSysLog("SPI: open() failed!");
        return -1;
    }

    int32 ret = ioctl(fd, SPI_IOC_WR_MODE, &config->spiMode);
    if (ret < 0)
    {
        CFE_ES_WriteToSysLog("SPI: ioctl() failed!");
        return -1;
    }

    ret = ioctl(fd, SPI_IOC_RD_MODE, &config->spiMode);
    if (ret < 0)
    {
        CFE_ES_WriteToSysLog("SPI: ioctl() failed!");
        return -1;
    }

    ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &config->bitsPerWord);
    if (ret < 0)
    {
        CFE_ES_WriteToSysLog("SPI: ioctl() failed!");
        return -1;
    }

    ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &config->bitsPerWord);
    if (ret < 0)
    {
        CFE_ES_WriteToSysLog("SPI: ioctl() failed!");
        return -1;
    }

    ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &config->spiSpeed);
    if (ret < 0)
    {
        CFE_ES_WriteToSysLog("SPI: ioctl() failed!");
        return -1;
    }

    ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &config->spiSpeed);
    if (ret < 0)
    {
        CFE_ES_WriteToSysLog("SPI: ioctl() failed!");
        return -1;
    }

    return fd;
}

int32 IO_TransSPIClose(int32 fd)
{
    close(fd);
    return 0;
}

int32 IO_TransSPIRead(int32 fd, uint8 *buffer, int32 numBytes)
{
    return read(fd, buffer, numBytes);
}

int32 IO_TransSPIWrite(int32 fd, uint8 *buffer, int32 numBytes)
{
    return write(fd, buffer, numBytes);
}

