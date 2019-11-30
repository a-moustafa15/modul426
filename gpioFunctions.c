#include <gpioFunctions.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

GPIO_PIN pins[MAX_PINS];

int fd_export = -1;
int fd_unexport = -1;

int init_gpio(){
    fd_export = open("/sys/class/gpio/export", O_WRONLY);
    fd_unexport = open("/sys/class/gpio/unexport", O_WRONLY);
    if (fd_export == -1) {
        return R_UNABLE_OPEN_FILE;
    }
    return R_SUCCESS;
}

int use_pin(GPIO pin, PIN_TYPE type){
    char tmp[2];

    sprintf(tmp, "%i", pin);

    int to_write = (pin < 10) ? 1 : 2;

    if (write(fd_export, &tmp, to_write) != to_write) {
        return R_UNABLE_WRITE_FILE;
    }

    char pin_file[50];
    sprintf(pin_file, "/sys/class/gpio/gpio%i/direction", pin);

    int fd = open(pin_file, O_WRONLY);
    if (fd == -1) {
        return R_UNABLE_OPEN_FILE;
    }

    to_write = (type == OUTPUT) ? 3 : 2;

    if (write(fd, (type == OUTPUT) ? "out" : "in", to_write) != to_write) {
        return R_UNABLE_WRITE_FILE;
    }

    close(fd);

    char pin_value_file[50];
    sprintf(pin_value_file, "/sys/class/gpio/gpio%i/value", pin);

    fd = open(pin_value_file, (type == OUTPUT) ? O_WRONLY : O_RDONLY);
    if (fd == -1) {
        return R_UNABLE_OPEN_FILE;
    }

    pins[pin - 2].file_descriptor = fd;
    pins[pin -2].type = type;
    pins[pin -2].pin = pin;

    return R_SUCCESS;
}

int set_pin_value(GPIO pin, int value){
    GPIO_PIN gpio = pins[pin -2];
    if(gpio.type == INPUT){
        return R_WRONG_PING_TYPE;
    }
    int fd = gpio.file_descriptor;
    
    if(fd == 0){
        return R_OPEN_PIN_FIRST;
    }

    char tmp[10];

    sprintf(tmp, "%i", value);

    int to_write = (pin < 10) ? 1 : 2;

    if (write(fd, &tmp, to_write) != to_write) {
        return R_UNABLE_WRITE_FILE;
    }

    return R_SUCCESS;
}

int get_pin_value(GPIO pin, int *value){
    GPIO_PIN gpio = pins[pin -2];

    char pin_value_file[50];
    sprintf(pin_value_file, "/sys/class/gpio/gpio%i/value", pin);
    
    int fd = gpio.file_descriptor;

    if(fd == 0){
        return R_OPEN_PIN_FIRST;
    }

    char byte;

    if(pread(fd, &byte, 1, 0) == 1){
        *value = byte == 49;
    }

    return R_SUCCESS;
}

int unexport_pin(GPIO pin){
    if (fd_unexport == -1) {
        return R_UNABLE_OPEN_FILE;
    }

    char tmp[10];

    sprintf(tmp, "%i", pin);

    if (write(fd_unexport, &tmp, (pin < 10) ? 1 : 2) != 2) {
        return R_UNABLE_WRITE_FILE;
    }

    int fd = pins[pin - 2].file_descriptor;

    if(fd != 0){
        close(fd);
    }

    return R_SUCCESS;
}

int unexport_all_pins(){
    for(int i = 0; i < MAX_PINS; i++){
        int fd = pins[i].file_descriptor;
        if(fd != 0){
            unexport_pin(i+2);
        }
    }
    close(fd_unexport);
}