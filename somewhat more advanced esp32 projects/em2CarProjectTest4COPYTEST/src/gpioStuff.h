//#include <driver/gpio.h>
#include <driver/adc.h>//used to set up and interact with an adc pin
#include <freertos/FreeRTOS.h>//vtaskdelay() used to sleep
//#include <freertos/task.h>
//#include <stdio.h>

#define ldrActivationThreshold 3800

//enumeration typedef to define the cars state
typedef enum carState {
  carState_OFF,
  carState_PARK,
  carState_DRIVE,
  carState_BACK,
  carState_ERROR
} carState_t;

typedef enum carDir{
    carDir_LEFT,
    carDir_RIGHT,
    carDir_NONE,
    carDir_BOTH
} carDir_t;


// this makes a string array that matches the array above
const char *carStateSTRINGS[] = {"-", "P", "D","R","E"};

#define SWITCH_CAR_PARK SWITCH_NR_1
#define SWITCH_CAR_DRIVE SWITCH_NR_2
#define SWITCH_CAR_BACK SWITCH_NR_3

#define SWITCH_CAR_LEFT SWITCH_NR_4
#define SWITCH_CAR_RIGHT SWITCH_NR_5

#define defaultMotorSpeedForBackwards 2000

/// @brief waits until the LDR output value gets
/// below a certain point than returns
void ldrUntilActivated(){
    int value ;
    adc2_config_channel_atten(ADC_CHANNEL_3,ADC_ATTEN_DB_11) ;

    while (1){
        adc2_get_raw(ADC2_CHANNEL_3,ADC_WIDTH_12Bit,&value);
        printf("Value = %d\n", value);
        vTaskDelay(300 / portTICK_PERIOD_MS);
        if (value <= ldrActivationThreshold)
        {
            break;
        }
    }
}


void carPinsSetup(){
    gpio_set_direction(SWITCH_CAR_PARK,GPIO_MODE_INPUT);
    gpio_set_direction(SWITCH_CAR_DRIVE,GPIO_MODE_INPUT);
    gpio_set_direction(SWITCH_CAR_BACK,GPIO_MODE_INPUT);

    gpio_set_direction(SWITCH_CAR_LEFT,GPIO_MODE_INPUT);
    gpio_set_direction(SWITCH_CAR_RIGHT,GPIO_MODE_INPUT);

    gpio_set_pull_mode(SWITCH_CAR_PARK, GPIO_PULLDOWN_ONLY);
    gpio_set_pull_mode(SWITCH_CAR_DRIVE, GPIO_PULLDOWN_ONLY);
    gpio_set_pull_mode(SWITCH_CAR_BACK, GPIO_PULLDOWN_ONLY);

    gpio_set_pull_mode(SWITCH_CAR_LEFT, GPIO_PULLDOWN_ONLY);
    gpio_set_pull_mode(SWITCH_CAR_RIGHT, GPIO_PULLDOWN_ONLY);


}

void updateDir(carDir_t dir){
    switch (dir)
            {
            case carDir_LEFT:
                gpio_set_level(LED_LEFT,1);
                gpio_set_level(LED_RIGHT,0);
                printf("left");
                break;
            case carDir_RIGHT:
                gpio_set_level(LED_LEFT,0);
                gpio_set_level(LED_RIGHT,1);
                printf("right");
                break;
            case carDir_BOTH:
                gpio_set_level(LED_LEFT,1);
                gpio_set_level(LED_RIGHT,1);
                printf("both");
                break;
            
            default:
                gpio_set_level(LED_LEFT,0);
                gpio_set_level(LED_RIGHT,0);
                printf("right");
                break;
            }
}

carState_t checkCarState(carState_t* outputState, carDir_t* outputDir){
    int park = gpio_get_level(SWITCH_CAR_PARK);
    int drive = gpio_get_level(SWITCH_CAR_DRIVE);
    int back = gpio_get_level(SWITCH_CAR_BACK);
    int left = gpio_get_level(SWITCH_CAR_LEFT);
    int right = gpio_get_level(SWITCH_CAR_RIGHT);
    int activePins = 0;
    int activeDirs = 0;
    carState_t stateToReturn = carState_ERROR;
    carDir_t carDir = carDir_NONE;

    printf("park: %d    drive:%d    back:%d\n",park,drive,back);

    if(left == 1 && right == 1){
        activeDirs = 2;
    }

    if(park == 1){
        stateToReturn = carState_PARK;
        carDir = carDir_NONE;
        activePins++;
    }

    if (drive == 1){
        stateToReturn = carState_DRIVE;
        if (left == 1 && right != 1){
            carDir = carDir_LEFT;
        }else if (left != 1 && right == 1){
            carDir =  carDir_RIGHT;
        }
        activePins++;
    }

    if (back == 1){
        stateToReturn = carState_BACK;
        activePins++;
        carDir = carDir_BOTH;
    }

    if (activePins > 1){
        stateToReturn = carState_ERROR;
    }else if (activePins == 0){
        stateToReturn = carState_OFF;
    }
    
    *outputDir = carDir;
    *outputState = stateToReturn;
    return stateToReturn;
}

void setupMotorInputADCPin(){
    adc1_config_width(ADC_WIDTH_12Bit) ;
    adc1_config_channel_atten(ADC_CHANNEL_5,ADC_ATTEN_DB_11) ;
}

int getMotorInputADCPin(){
    int value = adc1_get_raw(ADC1_CHANNEL_5);
    printf("value: %d\n",value);
    return value;
}