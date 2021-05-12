#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include <string.h>
#include <errno.h>
#include <sys/types.h>

/** typedef for specific stub implementors **/
typedef struct
{
    const char *name;
    int  (*open_r  )( const char *path,int flags, int mode );
    int  (*close_r )( int fd );
    long (*write_r )( int fd, const char *ptr, int len );
    long (*read_r  )( int fd, char *ptr, int len );
} devoptab_t;

/** includes for the stub implementors **/
#include "stm32_usart.h"

/** Global newlib stub implementations **/

// exit:
void _exit(int status) { while(true); }

// malloc:
void _sbrk(int incr) 
{
    fputs("malloc() is not supported!", stderr); 
    exit(EXIT_FAILURE); 
}

// Parse file?
void _lseek() { }

// File status?
int _fstat(char *file) { 
    return 0;
}

// Is a terminal?
void _isatty() { }



const devoptab_t *devoptab_list[] = 
{
    &usart_dev,     /* standard input */
    &usart_dev,     /* standard output */
    &usart_dev,     /* standard error */
    NULL            /* terminates the list */
};

long _write_r ( int fd, const void *buf, size_t cnt )
{
    return devoptab_list[fd]->write_r( fd, (const char*)buf, cnt );
}


long _read_r ( int fd, const void *buf, size_t cnt )
{
    return devoptab_list[fd]->read_r( fd, (char*)buf, cnt );
}

int _open_r ( const char *file , int flags, int mode )
{
    (void)flags;
    (void)mode;
    // Flags and mode are ignored.

    int which_devoptab = 0;
    int fd = -1;    
    
    /* search for "file" in dotab_list[].name */
    do
    {
        if( strcmp( devoptab_list[which_devoptab]->name, file ) == 0 ) 
        { 
            fd = which_devoptab;
            break; 
        } 
    } 
    while( devoptab_list[which_devoptab++] );
    
    /* if we found the requested file/device,then invoke the device’s open_r() method */
    if( fd != -1 ) 
        devoptab_list[fd]->open_r( file, flags, mode );
    /* it doesn’t exist! */

        
    return fd;
}

long _close_r ( int fd ) 
{
    return devoptab_list[fd]->close_r( fd );
}