#include <gpioFunctions.h>
#include <moveSensorFunctions.h>

#include <pthread.h>

int detect_movements = 0;
int pin_state;

int move_sensor_set_pin(){
    int response;
    response = use_pin(MOVE_SENSOR_PIN, INPUT);
    return response;
}

void* read_movements(void *arg){
    int old_value = 0;
    while(detect_movements){
        int value;
        get_pin_value(MOVE_SENSOR_PIN, &value);
        old_value = value;
        if(value && value != old_value){
            //send to tcp socket
        }
    }
}

int start_detect_movements(){
    if(detect_movements){
        return R_MOVEMENT_SENSOR_READED_ALREADY;
    }

    if(pin_state != R_SUCCESS){
        return pin_state;
    }

    pthread_t thread;
    detect_movements = 1;
    pthread_create(&thread, NULL, read_movements, NULL); 
}

void stop_detect_movements(){
    detect_movements = 0;
}