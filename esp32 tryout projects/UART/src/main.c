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

static const char* TAG = "uart_select_example";

char naam[999];
int letter = 0;

int startMain = 0;

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

void app_main(void)
{
    xTaskCreate(uart_select_task, "uart_select_task", 4*1024, NULL, 5, NULL);
    printf("breakmain werkt!\n");
    for (size_t i = 0; i < letter; i++)
        {
        printf("%c",naam[i]);                       
        }
}
