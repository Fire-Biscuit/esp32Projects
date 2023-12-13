#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "ssd1306.h"

#include "oled.h"
#include "pinNumbers.h"
#include "gpioStuff.h"
#include "pwmStuff.h"

void app_main(void)
{
    ssd1306_handle_t Oled = oledSetup();
    char data_str[30] = {0};

    sprintf(data_str, "Car off");
    ssd1306_draw_string(Oled, 40, 30, (const uint8_t *)data_str, 16, 1);
    ssd1306_refresh_gram(Oled);

    ldrUntilActivated();

    ClearScreen(Oled);

    sprintf(data_str, "Vroem");
    ssd1306_draw_string(Oled, 20, 30, (const uint8_t *)data_str, 16, 1);
    ssd1306_refresh_gram(Oled);
    vTaskDelay(500 / portTICK_PERIOD_MS);

    sprintf(data_str, "Vroem");
    ssd1306_draw_string(Oled, 70, 30, (const uint8_t *)data_str, 16, 1);
    ssd1306_refresh_gram(Oled);
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    ClearScreen(Oled);

    carState_t carState = carState_OFF;
    carDir_t carDir = carDir_NONE;

    carPinsSetup();
    setupMotorInputADCPin();

    int motorspeed = 0;

    TaskHandle_t ISR_PWM = NULL;
    xTaskCreate(pwm_main, "pwm task", 4096, NULL, 10, &ISR_PWM);

    
    gpio_set_level(LED_LEFT,1);
    gpio_set_level(LED_RIGHT,1);
    vTaskDelay(1000);

    updateDir(carDir_BOTH);
    vTaskDelay(100);
    updateDir(carDir_LEFT);
    vTaskDelay(100);
    updateDir(carDir_RIGHT);
    vTaskDelay(100);
    updateDir(carDir_NONE);
    vTaskDelay(100);


    for(;;){
        carDir_t tempCarDir;
        carState_t tempCarState;
        if (checkCarState(&tempCarState,&tempCarDir) != carState_ERROR){
            carState = tempCarState;
            carDir = tempCarDir;
        }
        
        updateDir(carDir);

        switch (carState)
        {
        case carState_DRIVE:
            motorspeed = getMotorInputADCPin();
            printf("\n carDir = %d\n",carDir);
            break;
        case carState_BACK:
            motorspeed = defaultMotorSpeedForBackwards;
            break;
        
        default:
            motorspeed = 0;
            break;
        }
        
        

        sprintf(data_str, "%s",carStateSTRINGS[carState]);
        ssd1306_draw_string(Oled, 60, 24, (const uint8_t *)data_str, 16, 1);

        if(carState == carState_DRIVE || carState == carState_BACK){
            sprintf(data_str,"speed: %d",motorspeed);
            ssd1306_draw_string(Oled, 30, 50, (const uint8_t *)data_str, 16, 1);
        } else {
            sprintf(data_str,"speed: 0000");
            ssd1306_draw_string(Oled, 30, 50, (const uint8_t *)data_str, 16, 1);
        }

        ssd1306_refresh_gram(Oled);
        
        vTaskDelay(250 / portTICK_PERIOD_MS);
    }

}