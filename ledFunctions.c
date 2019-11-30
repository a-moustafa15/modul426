#include <gpioFunctions.h>
#include <ledFunctions.h>

#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

int led_set_pins(){
    return use_pin(LED_RED, OUTPUT) | use_pin(LED_GREEN, OUTPUT) | use_pin(LED_BLUE, OUTPUT);
}

int led_wait_for_server(){
    return set_pin_value(LED_RED, 1) | set_pin_value(LED_BLUE, 0) | set_pin_value(LED_GREEN, 0);
}

int led_server_connected(){
    return set_pin_value(LED_RED, 0) | set_pin_value(LED_BLUE, 0) | set_pin_value(LED_GREEN, 1);
}

#include <stdio.h>

void *led_back(void *arg){
    int *switch_time;
    switch_time = arg;
    sleep(*switch_time);
    free(arg);
    return (void *) set_pin_value(LED_BLUE, 0);
}

int led_move_detected(int switch_time){
    pthread_t thread;
    int response = set_pin_value(LED_BLUE, 1);
    int *time;
    time = malloc(sizeof(int));
    *time = switch_time;
    
    if(response != R_SUCCESS){
        return response;
    }

    pthread_create(&thread, NULL, led_back, (void*)time);
}
