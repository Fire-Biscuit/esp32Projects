//door Mike Schardijn it101-2 500911074


#include <driver/gpio.h>
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/adc.h>

#define LEDBAR_LED_0 GPIO_NUM_17
#define LEDBAR_LED_1 GPIO_NUM_18
#define LEDBAR_LED_2 GPIO_NUM_8
#define LEDBAR_LED_3 GPIO_NUM_6
#define LEDBAR_LED_4 GPIO_NUM_46
#define LEDBAR_LED_5 GPIO_NUM_9
#define LEDBAR_LED_6 GPIO_NUM_10
#define LEDBAR_LED_7 GPIO_NUM_11    //led is kaopt
#define LEDBAR_LED_8 GPIO_NUM_15
#define LEDBAR_LED_9 GPIO_NUM_13

void ledbar_show(int show) {

   gpio_set_level(LEDBAR_LED_0, show & 1);
   gpio_set_level(LEDBAR_LED_1, show & 2);
   gpio_set_level(LEDBAR_LED_2, show & 4);
   gpio_set_level(LEDBAR_LED_3, show & 8); 
   gpio_set_level(LEDBAR_LED_4, show & 16);
   gpio_set_level(LEDBAR_LED_5, show & 32);
   gpio_set_level(LEDBAR_LED_6, show & 64);
   gpio_set_level(LEDBAR_LED_7, show & 128);    //led is kaopt
   gpio_set_level(LEDBAR_LED_8, show & 256);
   gpio_set_level(LEDBAR_LED_9, show & 512); 

 
}

void app_main() {

    vTaskDelay(1000);
    gpio_set_direction(LEDBAR_LED_0, GPIO_MODE_OUTPUT);
    gpio_set_direction(LEDBAR_LED_1, GPIO_MODE_OUTPUT);
    gpio_set_direction(LEDBAR_LED_2, GPIO_MODE_OUTPUT);
    gpio_set_direction(LEDBAR_LED_3, GPIO_MODE_OUTPUT);
    gpio_set_direction(LEDBAR_LED_4, GPIO_MODE_OUTPUT);
    gpio_set_direction(LEDBAR_LED_5, GPIO_MODE_OUTPUT);
    gpio_set_direction(LEDBAR_LED_6, GPIO_MODE_OUTPUT);
    gpio_set_direction(LEDBAR_LED_7, GPIO_MODE_OUTPUT);
    gpio_set_direction(LEDBAR_LED_8, GPIO_MODE_OUTPUT);
    gpio_set_direction(LEDBAR_LED_9, GPIO_MODE_OUTPUT);

    adc1_config_width(ADC_WIDTH_12Bit) ;
    adc1_config_channel_atten(ADC_CHANNEL_3,ADC_ATTEN_DB_11) ;

    int i;
    int modus = 0;
    int delay;

    while(1){

        

        if (modus == 0){
            for (i = 1; i <= 512; i*=2) {
                delay = adc1_get_raw(ADC1_CHANNEL_3) ;
                delay /= 2;
                printf("delay  = %d\n", delay) ;
                printf("Waarde = %d \n", i);
                ledbar_show(i);
                vTaskDelay(delay);
                if (i == 512){
                    modus = 1;
                }
            }
            
        }
        if(modus == 1 ){
            for (i = 512; i >= 1; i/=2) {
                delay = adc1_get_raw(ADC1_CHANNEL_3) ;
                delay /= 2;
                printf("delay  = %d\n", delay) ; 
                
                printf("Waarde = %d \n", i);
                ledbar_show(i);
                vTaskDelay(delay);
                if (i == 1){
                    modus = 0;
                }
            }
        }
    }
}