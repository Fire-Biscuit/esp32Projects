// #include <driver/gpio.h>
// #include <freertos/FreeRTOS.h>
// #include <freertos/task.h>
// #include <stdio.h>
// #include "freertos/FreeRTOS.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include <stdio.h>
#include "ssd1306.h"

#define I2C_MASTER_SCL_IO GPIO_NUM_2        /*!< gpio number for I2C master clock */
#define I2C_MASTER_SDA_IO GPIO_NUM_42        /*!< gpio number for I2C master data  */
#define I2C_MASTER_NUM I2C_NUM_1    /*!< I2C port number for master dev */
#define I2C_MASTER_FREQ_HZ 100000   /*!< I2C master clock frequency */

static ssd1306_handle_t ssd1306_dev = NULL;

void app_main(void)
{
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = (gpio_num_t)I2C_MASTER_SDA_IO;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_io_num = (gpio_num_t)I2C_MASTER_SCL_IO;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = I2C_MASTER_FREQ_HZ;
    conf.clk_flags = I2C_SCLK_SRC_FLAG_FOR_NOMAL;

    printf("conf initialised\n");

    i2c_param_config(I2C_MASTER_NUM, &conf);
    i2c_driver_install(I2C_MASTER_NUM, conf.mode, 0, 0, 0);

    printf("parms set\n");

    ssd1306_dev = ssd1306_create(I2C_MASTER_NUM, SSD1306_I2C_ADDRESS);
    ssd1306_refresh_gram(ssd1306_dev);
    //ssd1306_clear_screen(ssd1306_dev, 0x00);
    //ssd1306_fill_rectangle(ssd1306_dev,0,0,128,64,0);


    char data_str[30] = {0};



    printf("i2c connection made\n");
    int counter = 0;
    for(;;){
        counter++;
        
        sprintf(data_str, "<");
        ssd1306_draw_string(ssd1306_dev, 60, 32, (const uint8_t *)data_str, 16, 1);
        ssd1306_refresh_gram(ssd1306_dev);

        sprintf(data_str, "rpm: %d", counter);
        ssd1306_draw_string(ssd1306_dev, 40, 48, (const uint8_t *)data_str, 16, 1);
        ssd1306_refresh_gram(ssd1306_dev);

        printf("message send\n");  
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }

}
// #include <utilities.h>
// #include "esp_log.h"

// TaskHandle_t button1TaskHandle = NULL;
// TaskHandle_t button2TaskHandle = NULL;

// void button1Task(void* arg){
//     pwmBlinkPinInit(LED_RIGHT);
//     while (1)
//     {
//         printf("from button task 1\n");
//         vTaskDelay(pdMS_TO_TICKS(1000));
//         pwmBlink(LED_RIGHT);
//     }
// }
// void button2Task(void* arg){
//     pwmBlinkPinInit(LED_LEFT);
//     while (1)
//     {
//         printf("from button task 2\n");
//         vTaskDelay(pdMS_TO_TICKS(2000));
//         pwmBlink(LED_LEFT);
//     }
// }

// void app_main() {

//     xTaskCreate(button1Task, "button1Task", 4096, NULL, 10, &button1TaskHandle);
//     xTaskCreatePinnedToCore(button2Task, "button2Task", 4096, NULL, 10, &button2TaskHandle, 1);
// }