//door Mike Schardijn it101-2 500911074

#include <driver/gpio.h>
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/adc.h>

#define LED GPIO_NUM_17

void app_main() {
    
    gpio_set_direction(LED,GPIO_MODE_OUTPUT);

    while(1){

        vTaskDelay(30);
        gpio_set_level(LED,1);
        vTaskDelay(30);
        gpio_set_level(LED,0);

    }

}