#pragma once

#define STM32F303xE
#include "stm32f30x.h"

#include "sys/file.h"

int  open_uart( const char *path, int flags, int mode )
{


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