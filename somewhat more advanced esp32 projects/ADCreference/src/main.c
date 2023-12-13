#include <driver/gpio.h>
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "driver/adc.h"

void app_main() {

    adc1_config_width(ADC_WIDTH_BIT_DEFAULT);
    adc1_config_channel_atten(ADC1_CHANNEL_3, ADC_ATTEN_DB_0);

    while (1)
    {
        int value = adc1_get_raw(ADC1_CHANNEL_3);
        printf("%i \n",(value/4));
        vTaskDelay(10);
    }
    
}