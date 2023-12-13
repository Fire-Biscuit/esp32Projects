/**
 ***********************************************************************************
 *
 *
 * Exam of Embedded Systems 2
 * Date: November 6th 2018
 * Time: 14:30 - 17:00
 *
 * TODO: Exercise 1a
 * Student's name: 
 * Student's number: 
 *
 *
 * Preface:
 *
 * In this exam assignment you will work with a system to control the brake and
 * rear lights of a car. The brake lights are represented by the blue LED that
 * is built into the PSoC board.
 *
 * The brake pedal is the button on the board. For the normal rear lights of the
 * car you have to connect an extra LED to the board.
 *
 *
 * IMPORTANT: WHEN YOU HAVE FINISHED, DELIVER THE MAIN FOLDER CONTAINING YOUR
 *            COMPLETE PROJECT!! COPY THE smart_lock.cysdn DIRECTORY AND PASTE
 *            IT ON YOUR USB STICK!
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
 * 1a: Enter your name and student number in the lines at the beginning of this
 *     file.
 *
 * 1b: Create a new (empty) project for your exam. Make sure to check that you
 *     are using the correct target hardware (your type of board). Call this
 *     project "break_light" and look carefully where this is stored. Copy
 *     the content of this file with the exercises and code in the main.c file
 *     of your project. Build the project and see if you can run and debug it.
 *
 *
 ***********************************************************************************
 *
 * Exercise 2: Break Light
 *
 * In this assignment you will implement the basic brake light.
 *
 * 2a: Create an output pin and an input pin in your top-design. You link the 
 *     output pin to the blue LED on your board and the input pin to the button
 *     on your board (use the SW1 button in the middle of your board and not
 *     the SW3 (reset) button that is on the edge of your board!). Configure
 *     the input pin as "resistive pull-up".
 *        TODO done
 *
 * 2b: What does it mean that the input pin is configured as "resistive pull-up"?
 *    
 *       Answer:
 *            !resistive pull-up means that the floating pin state will be pulled to gpio state high
 * 2c: Complete the code of the function ButtonIsPressed() to determine whether
 *     the button is pressed or not and return that information.
 *        TODO done
 * 2d: Complete the code of the function SwitchBrakeLights() so that the LED
 *     operates as a brake light: when you press the button (the brake pedal),
 *     the LED (your brake light) must turn ON and when released it must turn
 *     OFF.
 *        TODO done
 *
 *
 ***********************************************************************************
 *
 * Exercise 3: Blink
 *
 * Now we want to add an extra functionality to attract more attention when
 * braking. Before the brake lights turn ON constantly, we want them to flash
 * for one second.
 *
 * 3a: Adjust the code of the function FlashBrakeLights() so that when you
 *     press the brake pedal, the brake light first flashes for a few
 *     milliseconds (duration) with a certain frequency (BLINK_FREQUENCY).
 *     Make sure you define a macro to set this frequency.
 *
 *     Use a for loop and a delay function for your solution approach. Test it
 *     out by setting BLINK_FREQUENCY to 5; and then calling the function with
 *     1000 ms, which causes the led to go on and off 5 times for exactly one
 *     second.
 *        TODO done
 *
 * 3b: The solution for blinking the LED in Exercise 3a (with a loop and the
 *     delay function) is not the best solution. What other solution could be
 *     there? Explain why that would be a better one.
 *
 *       Answer:
 *        !while the led is blinking the vtaskdelay() function stops the whole programs meaning the button cant be released
 *        !so it is better to do the blinking on a seperate thread which you can suspend and resume when needed.
 *
 *
 ***********************************************************************************
 *
 * Exercise 4: Rear Light
 *
 * In addition to a brake light, we also want to have a regular rear light.
 * This must of course burn less brightly than a brake light. You will use a
 * PWM for this.
 *
 * 4a: Connect another LED to your board yourself. Configure an output pin in
 *     your top-design for this LED and also indicate how you connected the
 *     LED.
 *          !I connected this led on gpio pin 1 and the ground bar on my breadboard
 *
 * 4b: Configure a PWM in your top-design, including an input clock. Connect
 *     the output of the PWM to the output pin for your LED.
 *        TODO done
 *
 * 4c: We want the LED to burn at approximately half strength without seeing a
 *     flickering in the LED. Configure the clock and PWM for this. Give the
 *     values of the following parameters that you have configured with a brief
 *     explanation:
 *
 *       Frequency of input clock:
 *       Resolution PWM:  
 *          !13 bits
 *       Period PWM: 
 *          !5000 Hertz
 *       CMP value PWM:
 *
 *     Explanation:
 *
 * 4d: Change the code of the function SwitchRearLights() so that the rear
 *     lights are turned ON at half power.
 *        TODO done
 *
 *
 ***********************************************************************************
 *
 * Exercise 5: Automatic Rear Light
 *
 * Now we want to adjust the system so that the rear lights are switched ON
 * and OFF automatically depending on whether it is light or dark outside. For
 * this we are going to use the LDR (light-dependent resistor) that is included
 * in the kit (a small round disk with a sort of spiral drawn onto it).
 *
 * If you do not have this LDR or cannot get it to work, you can also use the
 * manually adjustable resistor (does yield fewer points).
 *
 * 5a: Connect the LDR between 5 volts and an analog input pin. Draw this also
 *     in your top-design. Also install and configure an ADC converter (ADC_SAR)
 *     to convert the values ​​of the LDR into a digital value. Use the following
 *     settings for the ADC_SAR:
 *
 *       Input range: Vssa to Vdda (Single Ended)
 *       Reference: Internal Vref
 *
 *     Alternative: do not connect the LDR but the adjustable resistance.
 *
 * 5b: Complete the code of the function readDaylightSensor() so that the ADC
 *     is read. For example, use the debugger to determine the values ​​that
 *     are read when the LDR is covered and when it does catch light.
 *
 *       Covered:
 *       Uncovered:
 *
 *     Alternative: enter the min and max that you read from the adjustable
 *     resistance.
 *
 * 5c: Now adjust the code of the function DaylightIsOn() so that the rear
 *     lights switch on automatically when it gets dark (er) and go out when 
 *     it gets light (er) again. Make sure you define a macro to set the limit
 *     value. Which limit value did you use for this and why?
 *
 *       Limit value:
 *
 *     Explanation:
 *
 * 5d: Not every car is equipped with a light sensor to automatically determine
 *     whether the rear lights should be ON or OFF. Therefore, we want to adjust
 *     the code so that we can easily include or exclude this functionality in
 *     our program. Adjust the code so that we include or exclude the code in
 *     our program using macros for conditional compilation.
 *
 *
 ***********************************************************************************
 *
 * Exercise 6: Theory Questions
 *
 * 6a: Explain what the volatile modifier does and when to use it.
 *
 * 6b: Explain what the const modifier does and when to use it.
 *
 * 6c: Does the ARM processor use the stack or registers for local variables?
 *
 * 6d: What is a dangling pointer?
 *
 * 6e: Is a C enumerate type stored as text, integer or floating point?
 *
 *
 * REMINDER: Hand in the main folder ("break_light.cydsn") of your complete
 *           project!!
 *
 *
 ***********************************************************************************/

#include <stdio.h>
#include <driver/gpio.h>
#include <driver/adc.h>
#include <driver/ledc.h>
#include <freertos/FreeRTOS.h>
#include "freertos/task.h"
#include "esp_err.h"

#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_OUTPUT_IO          (GPIO_NUM_1) // Output GPIO
#define LEDC_CHANNEL            LEDC_CHANNEL_0
#define LEDC_DUTY_RES           LEDC_TIMER_13_BIT // Set duty resolution to 13 bits
#define LEDC_DUTY               (4095) // Set duty to 50%. ((2 ** 13) - 1) * 50% = 4095
#define LEDC_FREQUENCY          (5000) // Frequency in Hertz. Set frequency at 5 kHz

#define BUTTON GPIO_NUM_4
#define BREAKLIGHT GPIO_NUM_21
#define REARLIGHT GPIO_NUM_1
/* TODO: Exercise 5c
 * Define a macro to set the dark/light limit.
 */
#define DAYLIGHT_THRESHOLD 3800

#define BUTTON_RELEASED 0
#define BUTTON_PRESSED  1

#define BRAKE_OFF 0
#define BRAKE_BLINK 1
#define BRAKE_ON 2

#define REAR_OFF 0
#define REAR_ON 1

/* TODO: Exercise 3a
 * Define a macro to set the blink frequency.
 */
#define BLINK_FREQUENCY 5

int button_mode = BUTTON_RELEASED;
int brake_mode = BRAKE_OFF;
int rear_mode = REAR_OFF;
int value;

static void ledc_init(void){    //TODO done
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
}

void SetButtonMode(int mode) {
  button_mode = mode;
}

int GetButtonMode(void) {
  return button_mode;
}

void SetBrakeMode(int mode) {
  brake_mode = mode;
}

int GetBrakeMode(void) {
  return brake_mode;
}

void SetRearMode(int mode) {
  rear_mode = mode;
}

int GetRearMode(void) {
  return rear_mode;
}

int ButtonIsPressed(void) {   //TODO done

  /* TODO: Exercise 2c
   * Determine whether the button is pressed or not and return that information.
   */


  /* Temporary return value */
  return gpio_get_level(BUTTON);

}

void SwitchBrakeLights(int mode) {    //TODO done
  if(mode == BRAKE_ON){
    gpio_set_level(BREAKLIGHT,1);
  } else {
    gpio_set_level(BREAKLIGHT,0);
  }
}

void FlashBrakeLights(int duration) {    //TODO done
  printf("blink ");
  for (size_t i = 0; i < BLINK_FREQUENCY; i++)
  {
    gpio_set_level(BREAKLIGHT,1);
    vTaskDelay(duration/portTICK_PERIOD_MS);
    gpio_set_level(BREAKLIGHT,0);
    vTaskDelay(duration/portTICK_PERIOD_MS);
  }
  
  /* TODO: Exercise 3a
   * Flash the brake lights ON/OFF for a certain time in milliseconds (duration)
   * with a BLINK_FREQUENCY frequency.
   *
   * for (int i = ...; i...; i++) {
   *   ...
   *   delayMilliseconds();
   *   ...
   * }
   */

}

void SwitchRearLights(int mode) {    //TODO done

  /* TODO: Exercise 4d
   * Set the rear lights ON at half of the power.
   */
  if (mode == REAR_ON) {
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LEDC_DUTY));
  } else {
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, 0));
  }
  // Update duty to apply the new value
  ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));
  
}

int readDaylightSensor(void) {    //TODO done

  /* TO_DO: Exercise 5b  
   * Read the value from the LDR and return it.
   */
  int toReturn;
  adc2_get_raw(ADC2_CHANNEL_3,ADC_ATTEN_DB_11,&toReturn);
  printf("value = %d\n",toReturn);
  return toReturn;
}

int DaylightIsOn(void) {

  /* TODO: Exercise 5c
   * Determine if it is light or dark and return that.
   */
  value = readDaylightSensor();
  if (value <= DAYLIGHT_THRESHOLD)
  {
    return 0;
  }
  
  /* Temporary return value */
  return 1;

}

int app_main(void) {

  /* Enable global interrupts */

  /* Place your initialization/startup code here */
  gpio_set_direction(BREAKLIGHT,GPIO_MODE_OUTPUT);
  gpio_set_direction(BUTTON , GPIO_MODE_INPUT);
  gpio_set_pull_mode(BUTTON, GPIO_PULLUP_ONLY);
  adc2_config_channel_atten(ADC_CHANNEL_3,ADC_ATTEN_DB_11) ;

  ledc_init();

  ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, 500));
  // Update duty to apply the new value
  ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));

  for(;;) {
    vTaskDelay(2);

    /* Check if de user button is pressed */
    if (ButtonIsPressed()) {
            
      /* The button had not yet been pressed */
      if (GetButtonMode() == BUTTON_RELEASED) {
        
        FlashBrakeLights(50);

        SetButtonMode(BUTTON_PRESSED);
        SetBrakeMode(BRAKE_ON);

        /* TODO: Exercise 3a
         * Uncomment this line when solving Exercise 3a
         */
        SwitchBrakeLights(BRAKE_ON);
        printf("pressed");
        SwitchRearLights(REAR_ON);

      }
    
    }
    else {

      /* The button had just been pressed */
      if (GetButtonMode() == BUTTON_PRESSED) {
  
        SetButtonMode(BUTTON_RELEASED);
        SetBrakeMode(BRAKE_OFF);
        SwitchBrakeLights(BRAKE_OFF);
        printf("pressed\n");
      SwitchRearLights(REAR_OFF);
      }

    }

    if ((!DaylightIsOn()) && GetRearMode() == REAR_OFF) {

      SwitchRearLights(REAR_ON);
      SetRearMode(REAR_ON);

    }
    else if (DaylightIsOn() && GetRearMode() == REAR_ON) {

      SwitchRearLights(REAR_OFF);
      SetRearMode(REAR_OFF);

    }

  }

}

/* [] END OF FILE */

