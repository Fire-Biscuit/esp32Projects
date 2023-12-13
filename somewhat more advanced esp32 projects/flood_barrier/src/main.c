/**
 ***********************************************************************************
 *
 *
 * Exam of Embedded Systems 2
 * Date: November 7th 2023
 * Time: 11:00 - 13:30
 *
 * TODO: Exercise 1A
 * Student's name: Mike Schardijn
 * Student's number: 500911074
 *
 *
 * Preface:
 *
 * In this exam you will simulate the behavior of a basic flood barrier system
 * to be deployed in the city. Your system will consider the following hardware
 * components:
 *
 *   Potentiometer:  A three-terminal variable resistor which simulates the
 *                   sensor for the water level.
 *   Barrier LED:    A single LED which indicates the behavior (stays low,
 *                   raising slow or raising fast) of the barrier.
 *
 * The system monitors the working behavior of a basic flood barrier system. A
 * water level sensor indicates the amount of water accumulating in the system.
 * When the water has reached a certain level (LOW/MEDIUM), the system must be
 * activated, starting to slowly close the barrier to prevent more water to
 * come in. If a second level is reached (MEDIUM/HIGH), the closing speed must
 * be incremented to avoid further damages in the city. While the barrier is
 * closing, either slow or fast, the corresponding LED indicates such operation
 * by blinking at a specific frequency.
 *
 *
 * IMPORTANT: WHEN YOU HAVE FINISHED, DELIVER THE MAIN FOLDER CONTAINING YOUR
 *            COMPLETE PROJECT!! COPY THE flood_barrier DIRECTORY AND PASTE IT
 *            ON YOUR USB STICK!
 *
 * Good luck!
 *
 *
 ***********************************************************************************
 *
 * EXERCISES:
 *
 * Exercise 1: Getting started
 *
 * 1A: Enter your name and student number in the lines at the beginning of this
 *     file.
 * 
 * 1B: Create a new (empty) project for your exam. Call this project
 *     "flood_barrier" and look carefully where this is stored. Copy the
 *     content of this file with the exercises and code in the main.c file of
 *     your project.
 *
 * 1C: If you are using the ESP32 board, you will have to provide the wiring
 *     diagram of your project using Fritzing or any other tool. The wiring
 *     diagram must be included in the project that you will deliver. Do not
 *     forget to copy it in the USB stick.
 * 
 *     If you are using the PSoC board, the wiring diagram must be completed
 *     in the top-design area of your project.
 *
 * 1D: If the water level has not changed, there is no need to do anything. 
 *     We might as well wait for a while until we check the water level
 *     again. Fill in the code in the main loop to let the program sleep for a
 *     while before we check the water level again. How long do you let the
 *     program sleep?
 * *         I let the program speel for 1 second
 *
 ***********************************************************************************
 * 
 * Exercise 2: Declarations
 * 
 * Before starting your project, you are going to declare some elements
 * (variables, structures, enumerations, etc.) that will help you to develop
 * your solution.
 *
 * 2A: Your system should recognize/handle, at least, 3 different levels for
 *     the water: LOW, MEDIUM and HIGH. Declare an enumeration to handle these
 *     three levels. Use the typedef keyword to create your own data type for
 *     the levels.
 *
 * 2B: Your system should recognize/handle, at least, 3 status for the barrier:
 *     DOWN, RAISING SLOW and RISING FAST. Define an enumeration to handle
 *     these three different barrier status. Use the typedef keyword to create
 *     your own data type for the barrier status.
 *
 * 2C: Create your own structure, called flood_barrier_t, to represent your
 *     system. This structure must contain the most important information of 
 *     your system. Explain what and why did you choose to be part of your
 *     structure.
 *
 *         Explanation:
 **              I chose to put the water_level and the barrier_state into the struct.
 *
 *
 * 2D: Define a local variable, called barrier, to represent your system.
 *     Initialize this variable with your desired information.
 *
 * 2E: Define a local variable, called cur_water_level, to represent the
 *     current level of water in the city. Initialize this variable with your
 *     desired information.
 *
 *
 ***********************************************************************************
 * 
 * Exercise 3: Water level sensing
 * 
 * The system has to sense the current water level. We simulate this with the
 * use of a variable resistor (potentiometer) from your kit. 
 *
 * 3A: Connect the variable resistor to you board (ESP32 or PSOC) such that you
 *     will be able to read its setting. Draw in your Fritzing project (or in
 *     the top-design, if you are using PSoC) how you have connected your
 *     resistor.
 *
 * 3B: Complete the code of the function readWaterSensor() to read the resistor
 *     value. 
 *
 * 3C: Complete the code of the function convertReadingIntoHeight() to convert
 *     the resistor value into a height value between 0.0 and 1.5 meters
 * 
 * 3D: Use two macros to define the amount of water that separate the LOW and
 *     the MEDIUM levels, and the MEDIUM and HIGH levels.
 *
 * 3E: Complete the code of the function obtainWaterLevel() to convert the
 *     height reading into a water level. Use the macros that you defined in
 *     the previous question.
 *
 * 3F: As mentioned in Exercise 1D, the system only works when the water level
 *     has changed (e.g., when there is a difference between the water level
 *     stored in the system and the current water level). Complete the
 *     IF-THEN-ELSE statement to ensure that the system works when the water
 *     level has changed.
 *
 * 3G: It is important to keep the system updated. Whenever the water level
 *     changes, that information must be updated in the system so the system
 *     can always work in the desired way. Ensure that the current water level
 *     is properly updated.
 *
 *
 ***********************************************************************************
 * 
 * Exercise 4: Barrier Behavior Indication
 *
 * The behavior of the barrier has to be indicated with a single LED:
 *   LED STAYS ON:    Barrier stays in low position.
 *   LED BLINKS SLOW: Barrier is raising slow.
 *   LED BLINKS FAST: Barrier is raising fast.
 *
 * The blinking rate of the LED should be controlled by a PWM module
 *
 * 4A: Connect a LED to your board (ESP32 or PSOC) to be used for the barrier
 *     indicator. Draw in your Fritzing project (or in the top-design, if you
 *     are using PSoC) how you have connected your LED.
 *
 * 4B: Configure a PWM module and connect it to your LED. Explain the choices
 *     you have made for your PWM module:
 *
 *       Fast blinking frequency and corresponding PWM duty cycle setting:  
 *    *4095(50% of the 13 bit limit so that I can tell if the pwm is working or not)
 * 
 *       Slow blinking frequency and corresponding PWM duty cycle setting:
 *    *2000 this is half of the fast blinking so that a human can clearly tell the difference
 *
 * 4C: Complete the code of the function setBarrierStatus() such that the
 *     status (behavior) of the barrier is properly updated. DO NOT modify the
 *     signature of this function.
 *
 * 4D: Complete the code of the function setBarrierIndicator() such that the 
 *     barrier indicator LED performs the correct function. DO NOT modify the
 *     signature of this function.
 *
 * 4E: Complete the code corresponding to the proper calling of the functions
 *     implemented in Exercises 4C and 4D. DO NOT modify the signature of such
 *     functions.
 *
 *
 ***********************************************************************************
 *
 * Exercise 5: Theoretical Questions
 *
 * 5A: Assume that you are compiling a program in your computer and you obtain
 *     the following error message:
 *
 *          $ gcc main.c 
 *            /tmp/ccoXhwF0.o: In function `main':
 *            main.c:(.text+0x15): undefined reference to `readActivationSensor'
 *            collect2: error: ld returned 1 exit status
 *          $
 *
 *     At which stage of the compilation process is this error recognized?
 *     What is the most probable cause for this type of errors?
 * * this happens during the linking stage of the compiling when the compiler is now
 * * giving "links" so that all functions/declarations can be properly called
 * * the most likely explaination for this error is that the function has not been devined yet.
 * * this often occurs when the function declaration happens at the bottom of the .c file while the function is used in code above that
 * * or this happens if you messed up your includes
 *
 * 5B: A difference between RISC and CISC architectures is given by the number
 *     of bits used to encode the instructions: fixed or variable. Explain this
 *     concept using your own words and how it affects the design of the
 *     processor.
 * * RISC (redusec instruction set computer)
 * * CISC (complex instruction set computer)
 *    * CISC has more operators and is more powerfull
 *    * In CISC all the instructions can handle operands (destination) in memory
 *    * CISC is complicated, often specialized instructions withmany effects
 *    * CISC has instructions encoded over a variable number of bit
 *    * CISC has less regular syntax
 *    * CISC has several and complicated addressing modes
 *
 * 5C: Assuming the following statement:
 *
 *       typedef union em2 {
 *         double num[10];
 *         char msg[20];
 *       } em2_t;
 *
 *     What will print out the instruction: printf("%ld", sizeof(em2_t))?
 *     If we change the declaration to: typedef struct em2. What will print now
 *     the previous instruction?
 * *  the code above(with typedef union) prints 80, and the code below(with typedef struct em2 instead of union) that prints out 104                                                                     TODO DO!!!!
 * 5D: Regarding structures in C. When do you use the "arrow" operator (->) and
 *     when the "dot" (.) operator.
 * * the dot (.) operator is used to acces a struct
 * * the arrow (->) operator is used to acces a struct pointer
 *
 * 5E: What does it mean "passing arguments by reference" to a C function? Why
 *     this approach consumes less memory space?
 * * instead of making a temporary variable for a function you point to an 
 * * already existing variable so that no new memory space has to be used
 *
 *
 * REMINDER: Hand in the main folder ("flood_barrier") of your complete
 *           project!!
 *
 *
 ***********************************************************************************/

#include <stdio.h>                  //printf()
#include <driver/adc.h>             //adc config and get
#include <freertos/FreeRTOS.h>      //freertos/task library
#include "freertos/task.h"          //vtaskDelay()
#include "driver/ledc.h"            // set configs and update the ledc(pwm) output value
#include "esp_err.h"                //ESP_ERROR_CHECK(

#define MAX_HEIGHT 1.5


/* TODO: Exercise 3D
 * Define two macros to differentiate the water levels.
 */
#define LEVEL_MEDIUM 0.6
#define LEVEL_HIGH 1.2

#define MAX_SENSOR_WATER_LEVEL_HEIGHT 4095

/* TODO: Exercise 2A
 * Declare en enumeration (using typedef) to handle the water levels.
 * Beware, this is an enumeration NOT a variable.
 */
typedef enum waterLevel{
    waterLevel_LOW,
    waterLevel_MEDIUM,
    waterLevel_HIGH
} waterLevel_t;


/* TODO: Exercise 2B
 * Declare en enumeration (using typedef) to handle the status of the barrier.
 * Beware, this is an enumeration NOT a variable.
 */
typedef enum barrierStatus{
    barrierStatus_DOWN,
    barrierStatus_RISING_SLOW,
    barrierStatus_RISING_FAST
} barrierStatus_t;



/* TODO: Exercise 2C
 * Declare an structure called flood_barrier_t (using typedef) to represent
 * your system. Beware, this is a structure NOT a variable.
 */
struct flood_barrier_t{
  waterLevel_t water_level;
  barrierStatus_t barrier;
}flood_barrier_t;

void initComponents();
int readwaterSensor();
waterLevel_t obtainWaterLevel();
void setBarrierStatus();
int setBarrierIndicator();
static void pwm_init();

#define FAST_BLINKING 4095 // Set duty to 50%. ((2 ** 13) - 1) * 50% = 4095
#define SLOW_BLINKING 2000 // I made this number up, it has no real meaning other than that its a difference(from fast blinking) a human can see

#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_OUTPUT_IO          GPIO_NUM_1
#define LEDC_CHANNEL            LEDC_CHANNEL_0
#define LEDC_DUTY_RES           LEDC_TIMER_13_BIT // Set duty resolution to 13 bits
#define LEDC_DUTY               FAST_BLINKING
#define LEDC_FREQUENCY          (5000) // Frequency in Hertz. Set frequency at 5 kHz


void app_main() {

  
   struct flood_barrier_t flood_barrier;

  /* TODO: Exercise 2D
   * Define a variable called: barrier, with data type: flood_barrier_t, to
   * represent your system. Initialize its information as you wish.
   */
  flood_barrier.barrier = barrierStatus_DOWN;

  /* TODO: Exercise 2E
   * Define a variable called: cur_water_level, with data type: Exercise 2A, to
   * represent the current water level of the city. Initialize its information
   * as you wish.
   */
  flood_barrier.water_level= waterLevel_MEDIUM;

  
  /* Initialize/Startup your components */
  initComponents();

  for (;;) {

    /* Obtain the current water level */
    waterLevel_t cur_water_Level = obtainWaterLevel();
    printf(" current water level: %d", cur_water_Level);
    
    /* TODO: Exercise 3F
     * Establish the comparison between the water levels: the one stored on the
     * system and the current water level.
     */
    if (cur_water_Level != flood_barrier.water_level) {
      printf("changed in water level!!!!!!!!!!!!!!\n");

      /* TODO: Exercise 4E
       * Complete the function calling according to the function's signature.
       */
      setBarrierStatus(cur_water_Level, &flood_barrier.barrier);
      setBarrierIndicator(&flood_barrier.barrier);
      printf("barrierlevel = %d", flood_barrier.barrier);

      /* TODO: Exercise 3G
       * Update the current water level in the system.
       */
       flood_barrier.water_level = cur_water_Level;

    }

    /* The water level has not changed, sleep for a while */
    else { 

      /* TODO: Exercise 1D
       * Let the program sleep for a while.
       */
      
      printf("no changed in water level\n");
      vTaskDelay(1000/portTICK_PERIOD_MS);

    }

  }

}



/**
 ******************************************************
 *
 * IMPLEMENTATION
 * 
 * Please, implement your functions here.
 *
 * Attention: Under no circumstances, NEVER!!!, move this section to a
 * different part of the file.
 *
 * Additionally, as mentioned in class. DO NOT USE GLOBAL VARIABLES!
 *
 ******************************************************
 */

static void pwm_init(void){
    // Prepare and then apply the LEDC PWM timer configuration
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_MODE,
        .timer_num        = LEDC_TIMER,
        .duty_resolution  = LEDC_DUTY_RES,
        .freq_hz          = LEDC_FREQUENCY,  // Set output frequency at 5 kHz
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // Prepare and then apply the LEDC PWM channel configuration
    ledc_channel_config_t ledc_channel = {
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL,
        .timer_sel      = LEDC_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LEDC_OUTPUT_IO,
        .duty           = 0, // Set duty to 0%
        .hpoint         = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
    //sets the pwm led to off.
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, 0));
    // Update duty to apply the new value
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));
    vTaskDelay(10/ portTICK_PERIOD_MS);
}

void initComponents(void) {
  pwm_init();
  adc1_config_width(ADC_WIDTH_12Bit) ;
  adc1_config_channel_atten(ADC_CHANNEL_5,ADC_ATTEN_DB_11) ;
  /* Put here the initialization code of your components */
}

int readWaterSensor() {

  /* Temporary initialization for debugging purposes */
  int sensor_reading = 0;

  /* TODO: Exercise 3B
   * Fill in the code for this function to simulate the sensing of the water
   * level by reading the resistor value.
   */
  sensor_reading = adc1_get_raw(ADC1_CHANNEL_5);
    printf("pot: %d\n",sensor_reading);

  return sensor_reading;

}

float convertReadingIntoHeight() {

  int sensor_reading = readWaterSensor();

  /* TODO: Exercise 3C
   * Fill in the code for this function to convert the reading from the
   * potentiometer into a water level (height) value between 0.0 and 1.5 meter.
   */
  float sensor_reading_float = ((float)sensor_reading/(float)MAX_SENSOR_WATER_LEVEL_HEIGHT) * 1.5;
  printf("float: %f", sensor_reading_float);

  return sensor_reading_float;

}

waterLevel_t obtainWaterLevel() {

  /* Temporary initialization for debugging purposes */

  float height;
  height = convertReadingIntoHeight();

  /* TODO: Exercise 3D
   * Fill in the code for this function to determine the current water level
   * according to the measured height.
   */
  waterLevel_t waterLevelToReturn = waterLevel_LOW;
  if (height >= (float)LEVEL_HIGH){
    waterLevelToReturn = waterLevel_HIGH;
  } else if(height >= (float)LEVEL_MEDIUM){
    waterLevelToReturn = waterLevel_MEDIUM;
  }

  return waterLevelToReturn;

}

void setBarrierStatus(waterLevel_t curwater_level,barrierStatus_t *barrier){

  /* TODO: Exercise 4C
   * Write the code for this function to setup the proper barrier behavior
   * depending on the measured water level.
   */
  switch (curwater_level)
  {
  case waterLevel_HIGH:
    *barrier = barrierStatus_RISING_FAST;
    break;
  
  case waterLevel_MEDIUM:
    *barrier = barrierStatus_RISING_SLOW;
    break;
  
  default:
    *barrier = barrierStatus_DOWN;
    break;
  }


}

int setBarrierIndicator(barrierStatus_t *barrier) {
  printf("updating barrier led\n");

  /* TODO: Exercise 4D
   * Write the code for this function to light up the barrier led indicating
   * its behavior as follows:
   *   LED STAYS ON:    Barrier stays in low position.
   *   LED BLINKS SLOW: Barrier is raising slow.
   *   LED BLINKS FAST: Barrier is raising fast.
   */
  barrierStatus_t barrierState = *barrier;
  switch (barrierState)
  {
  case barrierStatus_RISING_SLOW:
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, SLOW_BLINKING));
    break;
  case barrierStatus_RISING_FAST:
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, FAST_BLINKING));
    break;
  default:
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, 0));
    break;
  }

  // Update duty to apply the new value
  ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));

  return 0;

}


/* [] END OF FILE */
