#include <gpioFunctions.h>
#include <moveSensorFunctions.h>
#include <tcpFunctions.h>
#include <timeFunctions.h>
#include <ledFunctions.h>

#include <pthread.h>

int detect_movements = 0;
int pin_state;

int move_sensor_set_pin(){
    int response;
    response = use_pin(MOVE_SENSOR_PIN, INPUT);
    return response;
}

#include <stdio.h>

void* read_movements(void *arg){
    int old_value = 0;
    int interval = 0;
    while(detect_movements){
        interval++;
        if(interval == 50){
            interval = 0;
            if(!check_server_connection())
                continue;
        }
        int value;
        get_pin_value(MOVE_SENSOR_PIN, &value);
        if(value && value != old_value){
            long time = currentMillis();
            
            led_move_detected(MOVE_SENSOR_SWITCH_TIME);

            char buffer[4];
            buffer[0] = (char)((time >> 24) & 0xFF) ;
            buffer[1] = (char)((time >> 16) & 0xFF) ;
            buffer[2] = (char)((time >> 8) & 0XFF);
            buffer[3] = (char)((time & 0XFF));
            write_to_server(buffer, 4);
        }
        old_value = value;
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