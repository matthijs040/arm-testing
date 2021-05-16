#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>

#define STM32F303xE
#include "stm32f30x.h"



// typedef volatile uint32_t register_t;

#define CR1_OFFSET  0x00
#define CR2_OFFSET  0X04
#define CR3_OFFSET  0X08
#define BRR_OFFSET  0x0C
#define GTPR_OFFSET 0X10
#define RTOR_OFFSET 0x14
#define RQR_OFFSET  0x18
#define ISR_OFFSET  0x1C
#define ICR_OFFSET  0x20
#define RDR_OFFSET  0x24     
#define TDR_OFFSET  0x28

#define CR1_ADDR    ( USART2_BASE + CR1_OFFSET  )  
#define CR2_ADDR    ( USART2_BASE + CR2_OFFSET  )  
#define CR3_ADDR    ( USART2_BASE + CR3_OFFSET  )  
#define BRR_ADDR    ( USART2_BASE + BRR_OFFSET  )  
#define GTPR_ADDR   ( USART2_BASE + GTPR_OFFSET ) 
#define RTOR_ADDR   ( USART2_BASE + RTOR_OFFSET ) 
#define RQR_ADDR    ( USART2_BASE + RQR_OFFSET  )  
#define ISR_ADDR    ( USART2_BASE + ISR_OFFSET  )  
#define ICR_ADDR    ( USART2_BASE + ICR_OFFSET  )  
#define RDR_ADDR    ( USART2_BASE + RDR_OFFSET  )
#define TDR_ADDR    ( USART2_BASE + TDR_OFFSET  )

#define USART_CR1_M0 (uint32_t)0x00001000           // Left bit in word length.
#define USART_CR1_M1 (uint32_t)0x10000000           // Right bit in word length.
#define USART_CR1_MB (USART_CR1_M0 | USART_CR1_M1)  // Both bits in word length.

// The stm32f303 has a base clock frequency of 72MHz
#define fCLK 72000000


// Enum specifying the allowed stop bit configurations.
typedef enum {
    h1,
    h2,   
    h3,
    h4,
} stopbits_t;

typedef enum {
    s1d8,
    s1d9,
    s1d7
} wordlength_t;

typedef enum {
    none,
    odd,
    even
}parity_t;

typedef enum {
    br2400,
    br9600,
    br19200,
    br38400,
    br57600,
    br115200,
    br230400,
    br460800,
    br921600,
    br2000000
} baudrate_t;

// Sets the bits in mask in the register.
#define set_register(reg, mask)     { *(register_t*)reg |= mask; }
// Clears the bits set in mask from the register.
#define clear_register(reg, mask)   { *(register_t*)reg &= ~mask; }
#define are_bits_set(reg, mask)        ( *(register_t*)reg & mask)


#define bitsof(T) (sizeof(T)*8)
#define lsb_mask(bits) (UINT32_MAX >> ( bitsof(register_t) - bits ) )  
#define shift_lsbs(reg, bits, shift) { register_t temp = reg;\
                                       clear_register(temp, lsb_mask(bits) );\
                                       temp >>= shift;\
                                       clear_register   (reg, ~lsb_mask(bits));\
                                       set_register     (reg, temp); }
static void uart_init()
{
    // Default configuration:
    stopbits_t stopbits     = h2;
    wordlength_t wordlength = s1d8;
    parity_t parity         = none;
    baudrate_t baudrate     = br115200;
    bool over8 = false;

    // stop usart:
    clear_register(CR1_ADDR, USART_CR1_UE);

    // Word length:
    clear_register(CR1_ADDR, USART_CR1_M);
    switch (wordlength)
    {
        case s1d7: set_register(CR1_ADDR, USART_CR1_M1);    break;
        case s1d8: clear_register(CR1_ADDR, USART_CR1_M);   break;
        case s1d9: set_register(CR1_ADDR, USART_CR1_M0);    break;
        default:   clear_register(CR1_ADDR, USART_CR1_M);   break;
    }

    clear_register(CR2_ADDR, USART_CR2_STOP);
    switch (stopbits)
    {
        case h1: set_register(CR2_ADDR, USART_CR2_STOP_0); break;
        case h2: clear_register(CR2_ADDR, USART_CR2_STOP); break;
        case h3: set_register(CR2_ADDR, USART_CR2_STOP);   break;
        case h4: set_register(CR2_ADDR, USART_CR2_STOP_1); break;
        default: clear_register(CR2_ADDR, USART_CR2_STOP); break;
    }

    // Parity bits:
    clear_register(CR1_ADDR, USART_CR1_PCE); //disable parity.
    switch (parity)
    {
        case none:  clear_register(CR1_ADDR, USART_CR1_PCE);                                        break;
        case odd:   set_register(CR1_ADDR, USART_CR1_PCE); set_register(CR1_ADDR, USART_CR1_PS)     break;
        case even:  set_register(CR1_ADDR, USART_CR1_PCE); clear_register(CR1_ADDR, USART_CR1_PS)   break;
        default:    clear_register(CR1_ADDR, USART_CR1_PCE);                                        break;
    }

    switch ((int)over8)
    {
        case true:  set_register(CR1_ADDR, USART_CR1_OVER8);    break;
        case false: clear_register(CR1_ADDR, USART_CR1_OVER8);  break;
        default:    clear_register(CR1_ADDR, USART_CR1_OVER8);  break;
    }

    /** Baud rate calculation 
     *  Page 901 of the user manual:
     * 
     * In case of oversampling by 16, the equation is:
     *                   fCK
     *   Tx/Rx baud = ---------
     *                 USARTDIV
     * 
     * 
     * In case of oversampling by 8, the equation is:
     *                 2 x fCK*
*
*
*
     *   Tx/Rx baud = ---------
     *                 USARTDIV
     * */

    uint16_t USART_div = 0;
    switch (baudrate)
    {
        case br2400:    USART_div = fCLK / 2400;    break;
        case br9600:    USART_div = fCLK / 9600;    break;
        case br19200:   USART_div = fCLK / 19200;   break;
        case br38400:   USART_div = fCLK / 38400;   break;
        case br57600:   USART_div = fCLK / 57600;   break;
        case br115200:  USART_div = fCLK / 115200;  break;
        case br230400:  USART_div = fCLK / 230400;  break;
        case br460800:  USART_div = fCLK / 460800;  break;
        case br921600:  USART_div = fCLK / 921600;  break;
        case br2000000: USART_div = fCLK / 2000000; break;
        default:        USART_div = fCLK / 115200;  break;
    }

    if(over8)
        USART_div = USART_div * 2;
    
    set_register(BRR_ADDR, USART_div );
    
    if(over8)
        shift_lsbs(BRR_ADDR, 3, 1);

} 


static int uart_put(char c, FILE* f)
{
    (void)f;
    if( are_bits_set(ISR_ADDR, USART_ISR_TXE) )
    {
        set_register(TDR_ADDR, c);
        return 1;
    }

    return 0; 
}

static int uart_get(FILE* f)
{ 
    (void)f;
    return 0; 
}

static int uart_flush(FILE* f)
{ 
    (void)f;
    return 0; 
}

static FILE usart2_stdio = FDEV_SETUP_STREAM(uart_put, uart_get, uart_flush, _FDEV_SETUP_RW);
struct __file *const __iob[] = {
    &usart2_stdio,
    &usart2_stdio,
    &usart2_stdio
};
