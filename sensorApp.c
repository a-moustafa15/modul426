#include <gpioFunctions.h>
#include <ledFunctions.h>
#include <tcpFunctions.h>
#include <ctrlcHandler.h>
#include <moveSensorFunctions.h>

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

int main(){

    activate_ctrlc_handler();

    int response = 0;

    response = init_gpio();

    if(response != 0){
        printf("failed to init gpio pins\n");
        exit(1);
    }

    led_set_pins();
    move_sensor_set_pin();

    led_wait_for_server();

    
    int state = -1;
    while((state = connect_server()) != 1 && is_running());

    if(state == -1){
        unexport_all_pins();
        return 0;  
    }

    printf("connected\n");

    signal(SIGPIPE, SIG_IGN);

    led_server_connected();

    start_detect_movements();
    
    while(is_running());

    stop_detect_movements();

    unexport_all_pins();

    return 0;
}