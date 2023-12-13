#include <driver/gpio.h>
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_intr_alloc.h>


#define BUTTON1_PIN GPIO_NUM_12
#define BUTTON2_PIN GPIO_NUM_13

TaskHandle_t ISR_button_1 = NULL;
TaskHandle_t ISR_button_2 = NULL;

void IRAM_ATTR button2_isr_handler(void *arg){
    xTaskResumeFromISR(ISR_button_2);
}


void button2task(void *arg){
    printf("hello from task 2");
    int counter = 0;
    while(1){
        vTaskSuspend(NULL); //this delay is to account for button bounce
        //vTaskDelay(5);
        if(gpio_get_level(BUTTON2_PIN) == 1){
            counter++;
        printf("---------------Button 2 pressed, counter = %d------------\n",counter);
        }
    }
}

void IRAM_ATTR button1_isr_handler(void *arg){
    xTaskResumeFromISR(ISR_button_1);
}




void button1task(void *arg){
    printf("hello from task 1");
    int counter = 0;
    while(1){
        vTaskSuspend(NULL); //this delay is to account for button bounce
        //vTaskDelay(5);
        if(gpio_get_level(BUTTON1_PIN) == 1){
            counter++;
        printf("---------------Button 1 pressed, counter = %d------------\n",counter);
        }
    }
}

void app_main() {

    gpio_install_isr_service(ESP_INTR_FLAG_EDGE);

    gpio_pad_select_gpio(BUTTON1_PIN);
    gpio_set_direction(BUTTON1_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON1_PIN, GPIO_PULLUP_ONLY);

    gpio_set_intr_type(BUTTON1_PIN, GPIO_INTR_POSEDGE);
    gpio_isr_handler_add(BUTTON1_PIN, button1_isr_handler, NULL);

    xTaskCreate(button1task, "button task", 4096, NULL, 10, &ISR_button_1);

    gpio_pad_select_gpio(BUTTON2_PIN);
    gpio_set_direction(BUTTON2_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON2_PIN, GPIO_PULLUP_ONLY);

    gpio_set_intr_type(BUTTON2_PIN, GPIO_INTR_POSEDGE);
    gpio_isr_handler_add(BUTTON2_PIN, button2_isr_handler, NULL);
    
    xTaskCreate(button2task, "button task", 4096, NULL, 10, &ISR_button_2);

    while(1){
        
        vTaskDelay(100);
        printf("-----------------------------CYCLE, counter = ------------------------------\n");
    }
}