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
 *
 * 2b: What does it mean that the input pin is configured as "resistive pull-up"?
 *
 *       Answer:
 *
 * 2c: Complete the code of the function ButtonIsPressed() to determine whether
 *     the button is pressed or not and return that information.
 *
 * 2d: Complete the code of the function SwitchBrakeLights() so that the LED
 *     operates as a brake light: when you press the button (the brake pedal),
 *     the LED (your brake light) must turn ON and when released it must turn
 *     OFF.
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
 *
 * 3b: The solution for blinking the LED in Exercise 3a (with a loop and the
 *     delay function) is not the best solution. What other solution could be
 *     there? Explain why that would be a better one.
 *
 *       Answer:
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
 *
 * 4b: Configure a PWM in your top-design, including an input clock. Connect
 *     the output of the PWM to the output pin for your LED.
 *
 * 4c: We want the LED to burn at approximately half strength without seeing a
 *     flickering in the LED. Configure the clock and PWM for this. Give the
 *     values of the following parameters that you have configured with a brief
 *     explanation:
 *
 *       Frequency of input clock:
 *       Resolution PWM:
 *       Period PWM:
 *       CMP value PWM:
 *
 *     Explanation:
 *
 * 4d: Change the code of the function SwitchRearLights() so that the rear
 *     lights are turned ON at half power.
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

#include "project.h"

/* TODO: Exercise 5c
 * Define a macro to set the dark/light limit.
 */
#define DAYLIGHT_THRESHOLD XXX

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
#define BLINK_FREQUENCY XXX

int button_mode = BUTTON_RELEASED;
int brake_mode = BRAKE_OFF;
int rear_mode = REAR_OFF;
int value;

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

int ButtonIsPressed(void) {

  /* TODO: Exercise 2c
   * Determine whether the button is pressed or not and return that information.
   */


  /* Temporary return value */
  return 1;

}

void SwitchBrakeLights(int mode) {

  /* TODO: Exercise 2d
   * Turn the brake lights ON/OFF depending on the mode.
   */


}

void FlashBrakeLights(int duration) {

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

void SwitchRearLights(int mode) {

  /* TODO: Exercise 4d
   * Set the rear lights ON at half of the power.
   */

}

int readDaylightSensor(void) {

  /* TO_DO: Exercise 5b  
   * Read the value from the LDR and return it.
   */

  return 0;

}

int DaylightIsOn(void) {

  /* TODO: Exercise 5c
   * Determine if it is light or dark and return that.
   */
  value = readDaylightSensor();
    
  /* Temporary return value */
  return 1;

}

int main(void) {

  /* Enable global interrupts */
  CyGlobalIntEnable;

  /* Place your initialization/startup code here */

  for(;;) {

    /* Check if de user button is pressed */
    if (ButtonIsPressed()) {
            
      /* The button had not yet been pressed */
      if (GetButtonMode() == BUTTON_RELEASED) {

        SetButtonMode(BUTTON_PRESSED);
        SetBrakeMode(BRAKE_ON);

        /* TODO: Exercise 3a
         * Uncomment this line when solving Exercise 3a
         */
        //FlashBrakeLights(XXXX);
        SwitchBrakeLights(BRAKE_ON);

      }
    
    }
    else {

      /* The button had just been pressed */
      if (GetButtonMode() == BUTTON_PRESSED) {
  
        SetButtonMode(BUTTON_RELEASED);
        SetBrakeMode(BRAKE_OFF);
        SwitchBrakeLights(BRAKE_OFF);

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

