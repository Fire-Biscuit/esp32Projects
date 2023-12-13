#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LED_PIN 17

void app_main(){

  while (1) {
    gpio_set_direction(LED_PIN,GPIO_MODE_OUTPUT);
    gpio_set_level(LED_PIN,1) ;
    vTaskDelay(100) ;
    gpio_set_level(LED_PIN, 0) ;
    vTaskDelay(100) ;
  }

}