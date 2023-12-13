#include <driver/gpio.h>
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define switch1 GPIO_NUM_15
#define switch2 GPIO_NUM_16
#define switch3 GPIO_NUM_17
#define switch4 GPIO_NUM_18

void setup(){
    gpio_set_direction(switch1, GPIO_MODE_INPUT);
    gpio_set_direction(switch2, GPIO_MODE_INPUT);
    gpio_set_direction(switch3, GPIO_MODE_INPUT);
    gpio_set_direction(switch4, GPIO_MODE_INPUT);

    gpio_set_pull_mode(switch1, GPIO_PULLDOWN_ONLY);
    gpio_set_pull_mode(switch2, GPIO_PULLDOWN_ONLY);
    gpio_set_pull_mode(switch3, GPIO_PULLDOWN_ONLY);
    gpio_set_pull_mode(switch4, GPIO_PULLDOWN_ONLY);
}

void app_main() {
    while(1){
        vTaskDelay(100);
        int switchLevel1 = gpio_get_level(switch1);
        int switchLevel2 = gpio_get_level(switch2);
        int switchLevel3 = gpio_get_level(switch3);
        int switchLevel4 = gpio_get_level(switch4);

        printf("value 1: %d, value 2: %d, value 3: %d, value 4: %d\n",switchLevel1,switchLevel2,switchLevel3,switchLevel4);
        //printf("value = %d\n", switchLevel1);
    }
}
