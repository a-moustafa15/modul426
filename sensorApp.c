#include <gpioFunctions.h>
#include <ledFunctions.h>
#include <tcpFunctions.h>

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(){

    int response = 0;

    response = init_gpio();

    if(response != 0){
        printf("failed init\n");
        exit(1);
    }

    response = led_set_pins();

    led_wait_for_server();

    while(connect_server() != 1);

    unexport_all_pins();

    disconnect_server();

    return 0;
}