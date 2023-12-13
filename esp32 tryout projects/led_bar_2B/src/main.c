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
#define BUTTON_PLUS GPIO_NUM_15
#define BUTTON_MIN GPIO_NUM_16

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

    gpio_set_direction(BUTTON_PLUS , GPIO_MODE_INPUT);
    gpio_set_direction(BUTTON_MIN , GPIO_MODE_INPUT);

    gpio_set_pull_mode(BUTTON_PLUS, GPIO_PULLUP_ONLY);
    gpio_set_pull_mode(BUTTON_MIN, GPIO_PULLUP_ONLY);



    int LEDPINS[] = {LED_10, LED_9, LED_8, LED_7, LED_6, LED_5, LED_4, LED_3, LED_2, LED_1};
    int machtTWEE[] = {512, 256, 128, 64, 32, 16, 8, 4, 2, 1};

    int i;
    
    int prev_state_1 = 1;
    int cur_state_1;

    int prev_state_2 = 1;
    int cur_state_2;

    int value = 111;
    int value2;

    while (1){
        value2 = value;
        for (i = 0; i <= 9; i++){
            while (value - machtTWEE[i] >= 0){
                gpio_set_direction(LEDPINS[i],GPIO_MODE_OUTPUT);
                gpio_set_level(LEDPINS[i],1) ;
                value -= machtTWEE[i];
                break;
            	}
        }
        for ( i = 0; i < 10; i++){
                gpio_set_level(LEDPINS[i],0) ;
        }

        value = value2;
        

        

        cur_state_1 = gpio_get_level(BUTTON_PLUS);

        if((prev_state_1 != cur_state_1) && (cur_state_1 == 0)){
            value++;
            printf("Value, werkt!!: = %d\n", value) ;   
            
        }
        prev_state_1 = cur_state_1;



        cur_state_2 = gpio_get_level(BUTTON_MIN);

        if((prev_state_2 != cur_state_2) && (cur_state_2 == 0)){
            value--;
            printf("Value, werkt!!: = %d\n", value) ;   
            
        }
        prev_state_2 = cur_state_2;

    }

}
