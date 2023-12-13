//gemaakt door Mike Schardijn it101 [500911074]
//8-12-2022
//alle pins aan
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"

int nummers[] = {GPIO_NUM_0, GPIO_NUM_1, GPIO_NUM_3, GPIO_NUM_4, GPIO_NUM_5, GPIO_NUM_6, GPIO_NUM_7, GPIO_NUM_8, GPIO_NUM_9, GPIO_NUM_10, GPIO_NUM_11, GPIO_NUM_12, GPIO_NUM_13, GPIO_NUM_14, GPIO_NUM_15, GPIO_NUM_16, GPIO_NUM_17, GPIO_NUM_18, GPIO_NUM_19, GPIO_NUM_20, GPIO_NUM_21, GPIO_NUM_30, GPIO_NUM_26, GPIO_NUM_27, GPIO_NUM_28, GPIO_NUM_29, GPIO_NUM_30, GPIO_NUM_31, GPIO_NUM_32, GPIO_NUM_33, GPIO_NUM_34, GPIO_NUM_35, GPIO_NUM_36, GPIO_NUM_37, GPIO_NUM_38, GPIO_NUM_39, GPIO_NUM_40, GPIO_NUM_41, GPIO_NUM_42, GPIO_NUM_43, GPIO_NUM_43, GPIO_NUM_45, GPIO_NUM_44, GPIO_NUM_46, GPIO_NUM_47, GPIO_NUM_48};
    
int i;    
void app_main(){
    while (1){
        printf("test");
        for (i = 0; i < 50; i++){
            gpio_set_direction(nummers[i],GPIO_MODE_OUTPUT);
            gpio_set_level(nummers[i],1) ;
            vTaskDelay(1);
        }
        vTaskDelay(999999);
    }
}

//monitor_speed = 115200
//board_build.flash_mode = dio