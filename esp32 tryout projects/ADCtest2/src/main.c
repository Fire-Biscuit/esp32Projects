#include <driver/gpio.h>
#include <driver/adc.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <stdio.h>

void app_main() {

    int value ;
    adc1_config_width(ADC_WIDTH_12Bit) ;
    adc1_config_channel_atten(ADC_CHANNEL_5,ADC_ATTEN_DB_11) ;

    while (1){
        value = adc1_get_raw(ADC1_CHANNEL_5);
        value = value / 2;
        printf("vALUE = %d\n", value) ;
        vTaskDelay(2) ;
    }

}