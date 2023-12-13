#include <stdio.h>

void app_main() {

    int i;
    int ii;
    int a = 12;
    int b = 10;
    int hoogte = 3;
    int breedte = 30;

    printf("a AND b: %d\n", a & b);
    printf("a OR b: %d\n", a | b);
    printf("a XOR b: %d\n", a ^ b);

    for (i = 0; i < hoogte; i++) {
        for (ii = 0; ii < breedte; ii++) {
            printf("#");
        }
        printf("\n");
    }
    printf("\n");
    
}