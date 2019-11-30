#include <gpioFunctions.h>

#ifndef MOVE_SENSOR_PIN

#define MOVE_SENSOR_PIN GPIO_23
#define MOVE_SENSOR_SWITCH_TIME 6

int move_sensor_set_pin();

int start_detect_movements();

void stop_detect_movements();

#endif