#pragma once

#include <stdio.h>

#define STM32F303xE
#include "stm32f30x.h"

typedef uint32_t register_t;

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

// Enum specifying the allowed stop bit configurations.
typedef enum {
    zero5   = 0x0001
  , one     = 0x0000
  , one5    = 0x0003 
  , two     = 0x0002
} stopbits_t;

// Sets the bits in mask in the register.
#define set_register(reg, mask) { *(register_t*)reg |= mask; }

// Clears the bits set in mask from the register.
#define clear_register(reg, mask) { *(register_t*)reg &= ~mask; }

static void uart_init()
{
    clear_register(CR1_ADDR, USART_CR1_UE);

    clear_register(CR2_ADDR, USART_CR2_STOP);
    
} 

static const int uart_put(char c, FILE* f)
{ 
    return 0; 
}

static const int uart_get(FILE* f)
{ 
    return 0; 
}

static const int uart_flush(FILE* f)
{ 
    return 0; 
}

static FILE usart2_stdio = FDEV_SETUP_STREAM(uart_put, uart_get, uart_flush, _FDEV_SETUP_RW);
struct __file *const __iob[] = {
    &usart2_stdio,
    &usart2_stdio,
    &usart2_stdio
};
