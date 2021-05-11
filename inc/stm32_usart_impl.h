#pragma once

#define STM32F303xE
#include "stm32f30x.h"



int  open_uart( struct _reent* r, const char *path, int flags, int mode )
{
    return 0;
}

int  close_uart( struct _reent* r, int fd )
{
    return 0;
}

long write_uart( struct _reent* r, int fd, const char *ptr, int len )
{
    return 0;
}

long read_uart( struct _reent* r, int fd, char *ptr, int len )
{
 return 0;
}