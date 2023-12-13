//Mike Schardijn
//2-12-2022
#include <driver/gpio.h>
#include <driver/adc.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>

#define LED_1 GPIO_NUM_17
#define LED_2 GPIO_NUM_18
#define LED_3 GPIO_NUM_8
#define LED_4 GPIO_NUM_4
#define LED_5 GPIO_NUM_46
#define LED_6 GPIO_NUM_9
#define LED_7 GPIO_NUM_10
#define LED_8 GPIO_NUM_11       //doet het niet
#define LED_9 GPIO_NUM_6
#define LED_10 GPIO_NUM_13

void app_main( ) {
    gpio_set_direction(LED_1 , GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_2 , GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_3 , GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_4 , GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_5 , GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_6 , GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_7 , GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_8 , GPIO_MODE_OUTPUT);       //doet het niet
    gpio_set_direction(LED_9 , GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_10 , GPIO_MODE_OUTPUT);

    int LEDPINS[] = {LED_10, LED_9, LED_8, LED_7, LED_6, LED_5, LED_4, LED_3, LED_2, LED_1};
    int machtTWEE[] = {512, 256, 128, 64, 32, 16, 8, 4, 2, 1};

    int i;

    int value = 0;
    int value2 = value;
    while (1){
        for (i = 0; i <= 9; i++){
            while (value - machtTWEE[i] >= 0){
                gpio_set_direction(LEDPINS[i],GPIO_MODE_OUTPUT);
                gpio_set_level(LEDPINS[i],1) ;
                value -= machtTWEE[i];
                break;
            }
        }

        vTaskDelay(10);
        for ( i = 0; i < 10; i++){
            gpio_set_level(LEDPINS[i],0) ;
        }

        value2 += 1;
        value = value2;
    }
}