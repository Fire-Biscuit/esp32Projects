

/* UART Select Example
   This example code is in the Public Domain (or CC0 licensed, at your option.)
   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

//door Mike Schardijn IT101 500911074 18-1-2023

#include <stdio.h>
#include <sys/fcntl.h>
#include <sys/errno.h>
#include <sys/unistd.h>
#include <sys/select.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_vfs.h"
#include "esp_vfs_dev.h"
#include "driver/uart.h"
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

static const char* TAG = "uart_select_example";

#define LEDBAR_LED_0 GPIO_NUM_17
#define LEDBAR_LED_1 GPIO_NUM_18
#define LEDBAR_LED_2 GPIO_NUM_37
#define LEDBAR_LED_3 GPIO_NUM_4
#define LEDBAR_LED_4 GPIO_NUM_7
#define LEDBAR_LED_5 GPIO_NUM_9
#define LEDBAR_LED_6 GPIO_NUM_10
#define LEDBAR_LED_7 GPIO_NUM_36    //kaput
#define LEDBAR_LED_8 GPIO_NUM_12
#define LEDBAR_LED_9 GPIO_NUM_13

#define BUTTON GPIO_NUM_15

//de gobal variables
char naam[999];
int letter = 0;

int startMain = 0;


//binair laten zien op de ledbar
void ledbar_show(int show) {
   gpio_set_level(LEDBAR_LED_0, show & 1);
   gpio_set_level(LEDBAR_LED_1, show & 2);
   gpio_set_level(LEDBAR_LED_2, show & 4);
   gpio_set_level(LEDBAR_LED_3, show & 8); 
   gpio_set_level(LEDBAR_LED_4, show & 16);
   gpio_set_level(LEDBAR_LED_5, show & 32);
   gpio_set_level(LEDBAR_LED_6, show & 64);
   gpio_set_level(LEDBAR_LED_7, show & 128);    //kaput
   gpio_set_level(LEDBAR_LED_8, show & 256);
   gpio_set_level(LEDBAR_LED_9, show & 512); 
}

//dit print de spelere's naam uit
void spelerNaam(){
    for (size_t i = 0; i < letter; i++)
    {
        printf("%c",naam[i]);                                
    }  
}

//dit laat de 5 led's knipperen met het aantal levens dat je hebt
void show_echte_levens(int levens){
    
    #define LED_0 GPIO_NUM_45
    #define LED_1 GPIO_NUM_5
    #define LED_2 GPIO_NUM_6
    #define LED_3 GPIO_NUM_39
    #define LED_4 GPIO_NUM_38

    int LEDPINS[] = {LED_0,LED_1,LED_2,LED_3,LED_4};
    for (size_t i = 0; i < 4; i++){
        gpio_set_direction(LEDPINS[i], GPIO_MODE_OUTPUT);
        gpio_set_level(LEDPINS[i],0);
    }
    for (size_t i = 0; i < levens; i++){
        gpio_set_level(LEDPINS[i],1);
    }
}

//dit is voor als het spel voorbij is, je krijgt je naam, punten en de levens-lampjes knipperen
void gameOver(int lives, int punten){
    if (lives == 0){
        while (1){
            printf("spel voorbij\n ");
            vTaskDelay(100);
            spelerNaam();
            printf("'s behaalde punten: %u \n", punten);
            ledbar_show(punten);
            while (1){
                show_echte_levens(0);
                vTaskDelay(30);
                show_echte_levens(5);
                vTaskDelay(30);
            }
        }
    }
}

//dit laat even snel je score in binair op de ledbar zien
void show_levens(int score){      
    ledbar_show(score);
    vTaskDelay(20);
    ledbar_show(0);
}

//dit is het pong spel
void pong() {

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

    gpio_set_direction(BUTTON , GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON, GPIO_PULLUP_ONLY);

    int i;
    int modus = 0;

    int delay = 50;
    int prev_state = 1;
    int cur_state;

    int prev_state1 = 1;
    int cur_state1;
    int punten = 0;
    int levens = 5;
    int ingedrukt = 0;

    show_levens(punten);
    show_echte_levens(levens);

    while(1){
        
        if((punten < 0 ) && (delay > 15)){
            delay -= punten;
        }
        if (modus == 0){
            ingedrukt = 0;
            for (i = 1; i <= 512; i*=2) {
                int X = i;
                ledbar_show(i);
                printf("i: = %d\n", i);
                for (size_t ii = 0; ii < delay; ii++)
                {
                    

                    cur_state1 = gpio_get_level(BUTTON);
                    vTaskDelay(1);

                    if((prev_state1 != cur_state1) && (cur_state1 == 0)){
                        if (X != 1){
                            show_echte_levens(levens);
                            levens -= 1;
                            printf("OOPS:   i is nu op %u, je levens zijn: %u \n", i, levens);
                        }
                        if (X == 1){
                            punten += 1;
                            show_levens(levens);
                            ingedrukt = 1;
                            printf("WELL DONE:   i is nu op %u, je punten zijn: %u \n", i, punten);
                        }
                        if (X == 512){
                            punten += 1;
                            show_levens(levens);
                            printf("WELL DONE:  i is nu op %u, je punten zijn: %u \n", i, punten);
                            ingedrukt = 1;

                        }
                    }
                    prev_state1 = cur_state1;

                    gameOver(levens, punten);
                }
                if (i == 2){
                    modus = 1;
                    if (ingedrukt == 0){
                        ingedrukt = 1;
                        show_echte_levens(levens);
                        levens -= 1;
                        printf("TOO SLOW:   i is nu op %u, je levens zijn: %u \n", i, levens);
                    }
                    if (ingedrukt == 1){
                        ingedrukt = 0;
                    }
                }
            }
        }
        
        if(modus == 1 ){
            ingedrukt = 0;
            for (i = 512; i >= 1; i/=2) {
                int X = i;
                ledbar_show(i);
                printf("i: = %d\n", i);
                for (size_t ii = 0; ii < delay; ii++)
                {
                    
                    cur_state = gpio_get_level(BUTTON);
                    vTaskDelay(1);

                    if((prev_state != cur_state) && (cur_state == 0) && ((X != 512) || (X != 1))){
                        if (X != 512){
                            show_echte_levens(levens);
                            levens -= 1;
                            printf("OOPS:   i is nu op %u, je levens zijn: %u \n", i, levens);
                        }
                        if (X == 512){
                            punten += 1;
                            show_levens(levens);
                            ingedrukt = 1;
                            printf("WELL DONE:  i is nu op %u, je punten zijn: %u \n", i, punten);
                        }
                        if (X == 1){
                            punten += 1;
                            show_levens(levens);
                            ingedrukt = 1;
                            printf("WELL DONE:   i is nu op %u, je punten zijn: %u \n", i, punten);
                        }
                    }
                    prev_state = cur_state;

                    gameOver(levens, punten);
                }
                if (i == 256){
                    modus = 0;
                    if (ingedrukt == 0){
                        ingedrukt = 1;
                        show_echte_levens(levens);
                        levens -= 1;
                        printf("TOO SLOW:   i is nu op %u, je levens zijn: %u \n", i, levens);
                    }
                    if (ingedrukt == 1){
                        ingedrukt = 0;
                    }
                }
            }
        }
    }
}

//hier wordt via uart je naam uitgelezen en het spel gestart als je op P drukt
static void uart_select_task(void *arg){
    
    if (uart_driver_install(UART_NUM_0, 2*1024, 0, 0, NULL, 0) != ESP_OK) {
        ESP_LOGE(TAG, "Driver installation failed");
        vTaskDelete(NULL);
    }

    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_XTAL,
    };
    

    uart_param_config(UART_NUM_0, &uart_config);

    while (1) {
        int fd;

        if ((fd = open("/dev/uart/0", O_RDWR)) == -1) {
            ESP_LOGE(TAG, "Cannot open UART");
            vTaskDelay(5000 / portTICK_PERIOD_MS);
            continue;
        }

        // We have a driver now installed so set up the read/write functions to use driver also.
        esp_vfs_dev_uart_use_driver(0);

        while (1) {
            int s;
            fd_set rfds;
            struct timeval tv = {
                .tv_sec = 5,
                .tv_usec = 0,
            };

            FD_ZERO(&rfds);
            FD_SET(fd, &rfds);

            s = select(fd + 1, &rfds, NULL, NULL, &tv);

            if (s < 0) {
                ESP_LOGE(TAG, "Select failed: errno %d", errno);
                break;
            } else if (s == 0) {
                ESP_LOGI(TAG, "Timeout has been reached and nothing has been received");
            } else {
                if (FD_ISSET(fd, &rfds)) {
                    char buf;
                    if (read(fd, &buf, 1) > 0) {
                        ESP_LOGI(TAG, "Received: %c", buf);
                        switch(buf){
                        case 'a':
                            naam[letter] = buf;
                            printf("\n %ue letter is %c \n",letter + 1, naam[letter]);
                            letter = letter + 1;
                            break;
                        case 'b':
                            naam[letter] = buf;
                            printf("\n %ue letter is %c \n",letter + 1, naam[letter]);
                            letter = letter + 1;
                            break;
                        case 'c':
                            naam[letter] = buf;
                            printf("\n %ue letter is %c \n",letter + 1, naam[letter]);
                            letter = letter + 1;
                            break;
                        case 'd':
                            naam[letter] = buf;
                            printf("\n %ue letter is %c \n",letter + 1, naam[letter]);
                            letter = letter + 1;
                            break;
                        case 'e':
                            naam[letter] = buf;
                            printf("\n %ue letter is %c \n",letter + 1, naam[letter]);
                            letter = letter + 1;
                            break;
                        case 'f':
                            naam[letter] = buf;
                            printf("\n %ue letter is %c \n",letter + 1, naam[letter]);
                            letter = letter + 1;
                            break;
                        case 'g':
                            naam[letter] = buf;
                            printf("\n %ue letter is %c \n",letter + 1, naam[letter]);
                            letter = letter + 1;
                            break;
                        case 'h':
                            naam[letter] = buf;
                            printf("\n %ue letter is %c \n",letter + 1, naam[letter]);
                            letter = letter + 1;
                            break;
                        case 'i':
                            naam[letter] = buf;
                            printf("\n %ue letter is %c \n",letter + 1, naam[letter]);
                            letter = letter + 1;
                            break;
                        case 'j':
                            naam[letter] = buf;
                            printf("\n %ue letter is %c \n",letter + 1, naam[letter]);
                            letter = letter + 1;
                            break;
                        case 'k':
                            naam[letter] = buf;
                            printf("\n %ue letter is %c \n",letter + 1, naam[letter]);
                            letter = letter + 1;
                            break;
                        case 'l':
                            naam[letter] = buf;
                            printf("\n %ue letter is %c \n",letter + 1, naam[letter]);
                            letter = letter + 1;
                            break;
                        case 'm':
                            naam[letter] = buf;
                            printf("\n %ue letter is %c \n",letter + 1, naam[letter]);
                            letter = letter + 1;
                            break;
                        case 'n':
                            naam[letter] = buf;
                            printf("\n %ue letter is %c \n",letter + 1, naam[letter]);
                            letter = letter + 1;
                            break;
                        case 'o':
                            naam[letter] = buf;
                            printf("\n %ue letter is %c \n",letter + 1, naam[letter]);
                            letter = letter + 1;
                            break;
                        case 'p':
                            naam[letter] = buf;
                            printf("\n %ue letter is %c \n",letter + 1, naam[letter]);
                            letter = letter + 1;
                            break;
                        case 'q':
                            naam[letter] = buf;
                            printf("\n %ue letter is %c \n",letter + 1, naam[letter]);
                            letter = letter + 1;
                            break;
                        case 'r':
                            naam[letter] = buf;
                            printf("\n %ue letter is %c \n",letter + 1, naam[letter]);
                            letter = letter + 1;
                            break;
                        case 's':
                            naam[letter] = buf;
                            printf("\n %ue letter is %c \n",letter + 1, naam[letter]);
                            letter = letter + 1;
                            break;
                        case 't':
                            naam[letter] = buf;
                            printf("\n %ue letter is %c \n",letter + 1, naam[letter]);
                            letter = letter + 1;
                            break;
                        case 'u':
                            naam[letter] = buf;
                            printf("\n %ue letter is %c \n",letter + 1, naam[letter]);
                            letter = letter + 1;
                            break;
                        case 'v':
                            naam[letter] = buf;
                            printf("\n %ue letter is %c \n",letter + 1, naam[letter]);
                            letter = letter + 1;
                            break;
                        case 'w':
                            naam[letter] = buf;
                            printf("\n %ue letter is %c \n",letter + 1, naam[letter]);
                            letter = letter + 1;
                            break;
                        case 'x':
                            naam[letter] = buf;
                            printf("\n %ue letter is %c \n",letter + 1, naam[letter]);
                            letter = letter + 1;
                            break;
                        case 'y':
                            naam[letter] = buf;
                            printf("\n %ue letter is %c \n",letter + 1, naam[letter]);
                            letter = letter + 1;
                            break;
                        case 'z':
                            naam[letter] = buf;
                            printf("\n %ue letter is %c \n",letter + 1, naam[letter]);
                            letter = letter + 1;
                            break;


                        case 'P':
                            printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!ENTER TEST!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                            for (size_t i = 0; i < letter; i++)
                            {
                                printf("%c",naam[i]);
                                
                            }
                            printf("\n");
                            startMain = 1;
                            pong();
                            break;
                            
                        default:
                            printf("karakter niet herkent, geef een een letter, GEEN HOOFDLETTERS");
                            break;
                        }
                        if (startMain == 1){
                            break;
                        }

                        // Note: Only one character was read even the buffer contains more. The other characters will
                        // be read one-by-one by subsequent calls to select() which will then return immediately
                        // without timeout.
                    if (startMain == 1){
                        break;
                    }
                    } else {
                        ESP_LOGE(TAG, "UART read error");
                        break;
                    }
                    
                if (startMain == 1){
                    break;
                }                    
                } else {
                    ESP_LOGE(TAG, "No FD has been set in select()");
                    break;
                }

                
            }
        }
        if (startMain == 1){
            break;
        }
        close(fd);
    }
    vTaskDelete(NULL);
}

//dit is de main die de rest aanroept
void app_main(void)
{
    xTaskCreate(uart_select_task, "uart_select_task", 4*1024, NULL, 5, NULL);
    printf("breakmain werkt!\n");
    for (size_t i = 0; i < letter; i++)
        {
        printf("%c",naam[i]);                       
        }
}