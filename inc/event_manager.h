#pragma once

typedef struct event_handler_t
{

} event_handler_t;


void poll_handlers();

/**
 * @brief Adds event handler to internal array
 * 
 * @param handler 
 */
void add_handler(event_handler_t* handler);