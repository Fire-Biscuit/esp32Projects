#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"

#include <pwmBlink.h>

//!broken pins: 10 46,             47  48  45  35  36  37  38  39

#define LED_LEFT GPIO_NUM_16
#define LED_RIGHT GPIO_NUM_15

#define LDR_SENSOR GPIO_NUM_14

#define BUTTON_1 GPIO_NUM_13
#define BUTTON_2 GPIO_NUM_12

#define HAL_EFFECT_SENSOR GPIO_NUM_11

#define SWITCH_NR_6 GPIO_NUM_10
#define SWITCH_NR_5 GPIO_NUM_9
#define SWITCH_NR_4 GPIO_NUM_3
#define SWITCH_NR_3 GPIO_NUM_8
#define SWITCH_NR_2 GPIO_NUM_18
#define SWITCH_NR_1 GPIO_NUM_17

#define DRIVER_PIN_1 GPIO_NUM_7
#define DRIVER_PIN_2 GPIO_NUM_6
#define DRIVER_PIN_3 GPIO_NUM_5
#define DRIVER_PIN_4 GPIO_NUM_4

#define BUZZER GPIO_NUM_21      

#define SDA undifined           //TODO
#define SCL undefined           //TODO