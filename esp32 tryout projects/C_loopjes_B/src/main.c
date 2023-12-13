#include <driver/gpio.h>
#include <driver/adc.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <stdio.h>

void app_main() {

    int i;
    int ii;
    int iiii;

    int hoogte = 8;
    int breedte = 15;

    for (ii = 0; ii < breedte; ii++) {
            printf("#");
        }
        printf("\n");

    for (i = 0; i < hoogte - 1; i++) {
        for (iiii = 0; iiii < breedte; iiii++) {
            if (iiii == 0){
                printf("#");
            } else if (iiii == breedte - 1){
                printf("#");
            }else {
                printf(" ");
            }
            
        }
        printf("\n");
    }

    for (ii = 0; ii < breedte; ii++) {
            printf("#");
        }
        printf("\n");
}