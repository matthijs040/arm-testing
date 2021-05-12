#pragma once

#define STM32F303xE
#include "stm32f30x.h"

#include "sys/file.h"

int  open_uart( const char *path, int flags, int mode )
{
    switch (flags)
    {
    case O_RDONLY:
        /* Initialize uart in a read mode.*/
        break;
    
    case O_WRONLY:
        /* Initialize uart in a write mode.*/
        break;

    case O_RDWR:
        break;

    default:
        errno = EINVAL;
        return -1;
        break;
    }
    
    return 0;
}

int  close_uart( int fd )
{
    return 0;
}

long write_uart( int fd, const char *ptr, int len )
{
    
    return 0;
}

long read_uart( int fd, char *ptr, int len )
{
    return 0;
}