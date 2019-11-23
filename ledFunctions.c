#include <gpioFunctions.h>
#include <ledFunctions.h>
#include <unistd.h>

#include <pthread.h>

int led_set_pins(){
    return use_pin(LED_RED, OUTPUT) | use_pin(LED_GREEN, OUTPUT) | use_pin(LED_BLUE, OUTPUT);
}

int led_wait_for_server(){
    return set_pin_value(LED_RED, 1) | set_pin_value(LED_BLUE, 0) | set_pin_value(LED_GREEN, 0);
}

int led_server_connected(){
    return set_pin_value(LED_RED, 0) | set_pin_value(LED_BLUE, 0) | set_pin_value(LED_GREEN, 1);
}

void *led_back(void *arg){
    usleep(1500000);
    set_pin_value(LED_BLUE, 0);
    return NULL;
}

void led_move_detected(){
    pthread_t thread;
    set_pin_value(LED_BLUE, 1);
    pthread_create(&thread, NULL, led_back, NULL);
}
