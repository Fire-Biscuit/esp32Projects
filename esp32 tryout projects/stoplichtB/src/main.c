//gemaakt door Mike Schardijn it101 [500911074]
//7-12-2022
//stoplicht met button volgens workshop in les
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/adc.h>
#include <stdio.h>
#include "freertos/FREERTOS.h"
#include "freertos/FreeRTOS.h"
#include <driver/ledc.h>

#define R GPIO_NUM_17
#define Y GPIO_NUM_18
#define G GPIO_NUM_8
#define BUTTON GPIO_NUM_15

#define ADC GPIO_NUM_11
#define DIMMER GPIO_NUM_12

#define REDSTATE 0
#define YELLOWSTATE 1
#define GREENSTATE 2



int state = 0;
void app_main(){

    int prev_state_1 = 1;
    int cur_state_1;
    while(1){


        

        gpio_set_direction(BUTTON, GPIO_MODE_INPUT);
        gpio_set_pull_mode(BUTTON, GPIO_PULLUP_ONLY);

        gpio_set_direction(R,GPIO_MODE_OUTPUT);
        gpio_set_direction(Y,GPIO_MODE_OUTPUT);
        gpio_set_direction(G,GPIO_MODE_OUTPUT);

        cur_state_1 = gpio_get_level(BUTTON);

        if((prev_state_1 != cur_state_1) && (cur_state_1 == 0)){
            printf("Value, werkt!!") ;   
            state = GREENSTATE;
            
        }
        prev_state_1 = cur_state_1;


        switch(state){
            case REDSTATE :
                gpio_set_level(R,1);
                gpio_set_level(G,0);
                gpio_set_level(Y,0);
                break;
            case GREENSTATE :
                gpio_set_level(R,0);
                gpio_set_level(G,1);
                gpio_set_level(Y,0);
                vTaskDelay(100);
                state = YELLOWSTATE;
                break;
            case YELLOWSTATE :
                gpio_set_level(R,0);
                gpio_set_level(G,0);
                gpio_set_level(Y,1);
                vTaskDelay(100);
                state = REDSTATE;
                break;
        }
    }
}

void init_adc(){
    adc1_config_channel_atten(ADC_CHANNEL_3,ADC_ATTEN_DB_11) ;
}


void saveME(){
    gpio_set_direction(R, GPIO_MODE_OUTPUT);
    gpio_set_direction(G, GPIO_MODE_OUTPUT);
    gpio_set_direction(Y, GPIO_MODE_OUTPUT);

    gpio_set_direction(BUTTON, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON,GPIO_PULLUP_ONLY);
}


void init_pwm(){
    ledc_timer_config_t timer_config;
    ledc_channel_config_t channel_config;
    timer_config.speed_mode = LEDC_LOW_SPEED_MODE;
    timer_config.timer_num = LEDC_TIMER_0;
    timer_config.duty_resolution = LEDC_TIMER_12_BIT;
    timer_config.freq_hz = 5000;
    timer_config.clk_cfg = LEDC_AUTO_CLK;

    channel_config.gpio_num = DIMMER;
    channel_config.speed_mode = LEDC_LOW_SPEED_MODE;
    channel_config.channel = LEDC_CHANNEL_0;
    channel_config.timer_sel = LEDC_TIMER_0;
    channel_config.intr_type = LEDC_INTR_DISABLE;
    channel_config.duty = 0;
    channel_config.hpoint = 0;

    ledc_timer_config(&timer_config);
    ledc_channel_config(&channel_config);
}