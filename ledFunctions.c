#include <gpioFunctions.h>
#include <ledFunctions.h>

int led_set_pins(){
    return use_pin(LED_RED, OUTPUT) | use_pin(LED_GREEN, OUTPUT) | use_pin(LED_BLUE, OUTPUT);
}

int led_wait_for_server(){
    return set_pin_value(LED_RED, 1) | set_pin_value(LED_BLUE, 0) | set_pin_value(LED_GREEN, 0);
}

int led_server_connected(){
    return set_pin_value(LED_RED, 0) | set_pin_value(LED_BLUE, 0) | set_pin_value(LED_GREEN, 1);
}