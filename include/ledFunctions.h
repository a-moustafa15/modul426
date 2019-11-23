#include <gpioFunctions.h>

#ifndef LED_RED

#define LED_RED GPIO_14
#define LED_GREEN GPIO_15
#define LED_BLUE GPIO_18

int led_set_pins();

int led_wait_for_server();

int led_server_connected();

void led_move_detected();

#endif