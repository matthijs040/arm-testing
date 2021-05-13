#include <stdio.h>
#include "inc/stm32_usart.h"

int main(void)
{  
    uart_init();
    while (true)
    {
        fputs("Hello world!", stdout);
    }
    

    
    return 0;
}