//gemaakt door Mike Schardijn it101 [500911074]
//1-12-2022
//stoplicht met button
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>

#define R GPIO_NUM_17
#define Y GPIO_NUM_18
#define G GPIO_NUM_8
#define BUTTON GPIO_NUM_15

void app_main() {
    gpio_set_direction(G , GPIO_MODE_OUTPUT);
    gpio_set_direction(Y , GPIO_MODE_OUTPUT);
    gpio_set_direction(R , GPIO_MODE_OUTPUT);

    gpio_set_direction(BUTTON , GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON, GPIO_PULLUP_ONLY);
    
    int mode = 0;
    int prev_state_1 = 1;
    int cur_state_1;
    printf("test");
    while(1){

        if (mode == 0){
            gpio_set_level(R , 1);
        }

        cur_state_1 = gpio_get_level(BUTTON);

        if((prev_state_1 != cur_state_1) && (cur_state_1 == 0)){
            printf("werkt!!: = %d\n", mode);   
            mode = 1;
        }
        prev_state_1 = cur_state_1;


        if (mode == 1){
            vTaskDelay(400);
            gpio_set_level(G, 1);
            gpio_set_level(R, 0);
            vTaskDelay(400);
            gpio_set_level(Y, 1);
            gpio_set_level(G, 0);
            vTaskDelay(400);
            gpio_set_level(Y, 0);
            mode = 0;
        }



    }
}