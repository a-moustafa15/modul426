#ifndef R_SUCCESS

#define R_SUCCESS 0
#define R_INIT_FIRST 1
#define R_UNABLE_OPEN_FILE 2
#define R_UNABLE_WRITE_FILE 3
#define R_OPEN_PIN_FIRST 4
#define R_WRONG_PING_TYPE 5
#define R_MOVEMENT_SENSOR_READED_ALREADY 6

#define MAX_PINS 26


typedef enum e_pin_type{
    OUTPUT,
    INPUT
}PIN_TYPE;

typedef enum e_gpio{
    GPIO_2 = 2,
    GPIO_3,
    GPIO_4,
    GPIO_5,
    GPIO_6,
    GPIO_7,
    GPIO_8,
    GPIO_9,
    GPIO_10,
    GPIO_11,
    GPIO_12,
    GPIO_13,
    GPIO_14,
    GPIO_15,
    GPIO_16,
    GPIO_17,
    GPIO_18,
    GPIO_19,
    GPIO_20,
    GPIO_21,
    GPIO_22,
    GPIO_23,
    GPIO_24,
    GPIO_25,
    GPIO_26,
    GPIO_27
}GPIO;

typedef struct s_gpio_pin{
    GPIO pin;
    int file_descriptor;
    PIN_TYPE type;
}GPIO_PIN;

int init_gpio();

int use_pin(GPIO pin, PIN_TYPE type);

int set_pin_value(GPIO pin, int value);

int get_pin_value(GPIO pin, int *value);

int unexport_pin(GPIO pin);

int unexport_all_pins();

#endif