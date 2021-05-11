#pragma once

/** typedef for specific stub implementors 
typedef struct 
{
    const char *name;
    int  (*open_r  )( struct _reent *r, const char *path,int flags, int mode );
    int  (*close_r )( struct _reent *r, int fd );
    long (*write_r )( struct _reent *r, int fd, const char *ptr, int len );
    long (*read_r  )( struct _reent *r, int fd, char *ptr, int len );
} devoptab_t;   **/

int  open_uart( struct _reent* r, const char *path, int flags, int mode )
{

}

int  close_uart( struct _reent* r, int fd )
{

}

long write_uart( struct _reent* r, int fd, const char *ptr, int len )
{

}

long read_uart( struct _reent* r, int fd, char *ptr, int len )
{

}