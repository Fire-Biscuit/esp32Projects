#include <driver/gpio.h>
#include <driver/adc.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <stdio.h>

void app_main() {

    int i;
    int ii;

    int hoogte = 10;            //verander hier de hoogte
    int breedte = 10;           //verander hier de breedte
    int rekenbreedte = breedte;

    for (i = 0; i < hoogte + 1; i++) {
        for (ii = 0; ii < rekenbreedte; ii++) {
            printf("  ");
        }
        for (ii = 0; ii < breedte - rekenbreedte; ii++) {
            printf(" #");
        }
        rekenbreedte -= 1;
        printf("\n");
    }
}