#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// Program exit:
void _exit(int status) { while(true); }

// malloc:
void _sbrk(int incr) 
{ exit(EXIT_FAILURE); }

int _write(int file, char *ptr, int len) { 
    return -1;
}

int _read() { return 0; }

void _lseek() { }

int _fstat(char *file) { 
    return 0;
}

void _isatty() { }

int _close() { return -1; }