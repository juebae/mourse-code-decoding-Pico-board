// Sources: https://www.educative.io/answers/what-is-clockspersec-in-c

// libraries
#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "includes/seven_segment.h"
#include <time.h>

// initialising global variables:

// this is to store the morse code for a single string representing a letter.
char letter[5] = "";

// this is a constant array which does not change. It is morse code representing all letters of the English alphabet.
const char *alphabet[] = {
    ".-",   "-...", "-.-.", "-..",  ".",   "..-.", "--.",  "....",
    "..",   ".---", "-.-",  ".-..", "--",  "-.",   "---",  ".--.",
    "--.-", ".-.", "...",   "-", "..-", "...-", ".--",  "-..-",
    "-.--", "--.."
};

// defines the button pin so we can get the boolean value whether it is being pressed or not later.
#define BUTTON_PIN 16 // Pin 21 (GPIO 16)

// initialises clock variables which will be used in button pressed time calculations
clock_t press_start;
clock_t press_end;
clock_t current_time;

// integer counter which increments by 1 after every checkButton() call.
// This is initalised at 0 because there has to be at least one character in the letter variable.
int counter = 0;
// boolean variable used for error handling later
bool matched = false;

// both used to store delta time in double format
double time_since_pressed;
double time_pressed;

// initalising functions
// decodes morse code into letter
void decoder(char morse);

// check if the button press is a dot or a dash
void checkButton(double time);

// main method
int main() {
    stdio_init_all();
    // print welcome message
    printf("\nWelcome to Group 20's Morse Code Project\n");
    // Initialise the seven segment display.
    seven_segment_init();
    // Turn the seven segment display off when the program starts.
    seven_segment_off();
    // turns on middle segment
    gpio_put(SEGMENT_G, false);
    // 2 sec delay
    sleep_ms(2000);
    // turns display off
    seven_segment_off();
    // Initialize the button's GPIO pin.
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    // Pull the button pin towards ground (with an internal pull-down resistor).
    gpio_pull_down(BUTTON_PIN);

    // infinite loop
    while (true) {
        // this loops until the button is pressed
        while (!gpio_get(BUTTON_PIN)) {
            // stores clock time at this point as press_start. As the condition for this while loop is !gpio_get(BUTTON_PIN), this while loop runs repeatedly
            // until the button is pressed, so the clock() value in press_start is repeatedly overwritten to get the clock value at the start of button press.
            press_start = clock();

            // this if statement happens if one full loop of the outer while loop has been complete, where checkButton() function has been called at least once.
            if (counter > 0) {
                // stores the current value of the clock into current_time
                current_time = clock();
                // calculates delta time by subtracting the last time the button was released from the current time.
                // The macro 'CLOCKS_PER_SEC' which is a constant value is used to get the double value in seconds. Multiplies by 1000 to convert to milliseconds.
                time_since_pressed = ((double)(current_time - press_end) / CLOCKS_PER_SEC) * 1000.0;
                // after 700 milliseconds of not pressing the button, the following will be executed
                if (time_since_pressed > 700) {
                    // passes the letter as an argument of the decoder function
                        decoder(letter[5]);
                        // counter is reset to 0 to prevent decoder from being called infinitely while the button is unpressed.
                        counter = 0;
                    // resets value in letter variable
                    strcpy(letter,"");
                }
            }
        }
       // initalised boolean as true
        bool pressed = true;
        // while pressed is true, this loop will continue
        while (pressed){
            // stores the clock time while the button is pressed into press_end. This will be overwritten repeatedely until the button is released.
            press_end = clock();
            // equation
            // calculates delta time by subtracting time the button was first pressed from the time it was released.
            // The macro 'CLOCKS_PER_SEC' which is a constant value is used to get the double value in seconds. Multiplies by 1000 to convert to milliseconds.
            time_pressed = ((double)(press_end - press_start) / CLOCKS_PER_SEC) * 1000.0;
            // stores the status of the button into pressed. If the button is released, it will store false, hence ending the while loop.
            // this allows us to store the clock time when the button is released.
            pressed = gpio_get(BUTTON_PIN);
        }
        // the time of button pressed is passed into checkButton() to identify if it's a dot or dash
        checkButton(time_pressed);
    }
}

// decoder function used to convert letter variable which stores the morse code into an actual letter of the alphabet on the terminal and 7-segment display
void decoder(char morse) {
    // used to iterate through alphabet array
    int i;
    for (i = 0; i < 26; i++) {
        // checks if the input exists in the array
        if (strcmp(letter, alphabet[i]) == 0) {
            // changes matched boolean to true as we found a match.
            matched = true;
            // switch case for every letter for alphabet. Their respective sequences of segments are added in each case, and their letters are printed.
            // there is also a 2 second delay after the segments are on, before turning them off.
            switch(i) {
                case 0://A
                    printf("A");
                    gpio_put(SEGMENT_F,false);  
                    gpio_put(SEGMENT_E,false);
                    gpio_put(SEGMENT_B,false);
                    gpio_put(SEGMENT_C,false);
                    gpio_put(SEGMENT_A,false);
                    gpio_put(SEGMENT_G,false);
                    sleep_ms(2000);
                    seven_segment_off();
                    break;
                case 1://B
                    printf("B");
                    gpio_put(SEGMENT_E,false);
                    gpio_put(SEGMENT_F,false);
                    gpio_put(SEGMENT_C,false);
                    gpio_put(SEGMENT_D,false);
                    gpio_put(SEGMENT_G,false);
                    sleep_ms(2000);
                    seven_segment_off();
                    break;
                case 2://C
                    printf("C");
                    gpio_put(SEGMENT_F,false);
                    gpio_put(SEGMENT_E,false);
                    gpio_put(SEGMENT_D,false);
                    gpio_put(SEGMENT_A,false);
                    sleep_ms(2000);
                    seven_segment_off();
                    break;
                case 3://D
                    printf("D");
                    gpio_put(SEGMENT_D,false);
                    gpio_put(SEGMENT_E,false);
                    gpio_put(SEGMENT_B,false);
                    gpio_put(SEGMENT_C,false);
                    gpio_put(SEGMENT_G,false);
                    sleep_ms(2000);
                    seven_segment_off();
                    break;
                case 4://E
                    printf("E");
                    gpio_put(SEGMENT_E,false);
                    gpio_put(SEGMENT_F,false);
                    gpio_put(SEGMENT_A,false);
                    gpio_put(SEGMENT_G,false);
                    gpio_put(SEGMENT_D,false);
                    sleep_ms(2000);
                    seven_segment_off();
                    break;
                case 5://F
                    printf("F");
                    gpio_put(SEGMENT_E,false);
                    gpio_put(SEGMENT_F,false);
                    gpio_put(SEGMENT_A,false);
                    gpio_put(SEGMENT_G,false);
                    sleep_ms(2000);
                    seven_segment_off();
                    break;
                case 6://G
                    printf("G");
                    gpio_put(SEGMENT_A,false);
                    gpio_put(SEGMENT_B,false);
                    gpio_put(SEGMENT_C,false);
                    gpio_put(SEGMENT_D,false);
                    gpio_put(SEGMENT_F,false);
                    gpio_put(SEGMENT_G,false);
                    sleep_ms(2000);
                    seven_segment_off();
                    break;
                case 7://H
                    printf("H");
                    gpio_put(SEGMENT_E,false);
                    gpio_put(SEGMENT_F,false);
                    gpio_put(SEGMENT_B,false);
                    gpio_put(SEGMENT_C,false);
                    gpio_put(SEGMENT_G,false);
                    sleep_ms(2000);
                    seven_segment_off();
                    break;
                case 8://I
                    printf("I");
                    gpio_put(SEGMENT_F,false);
                    gpio_put(SEGMENT_E,false);
                    sleep_ms(2000);
                    seven_segment_off();
                    break;
                case 9://J
                    printf("J");
                    gpio_put(SEGMENT_B,false);
                    gpio_put(SEGMENT_C,false);
                    gpio_put(SEGMENT_D,false);
                    gpio_put(SEGMENT_E,false);
                    sleep_ms(2000);
                    seven_segment_off();
                    break;
                case 10://K
                    printf("K");
                    gpio_put(SEGMENT_E,false);
                    gpio_put(SEGMENT_F,false);
                    gpio_put(SEGMENT_B,false);
                    gpio_put(SEGMENT_C,false);
                    gpio_put(SEGMENT_G,false);
                    sleep_ms(2000);
                    seven_segment_off();
                    break;
                case 11://L
                    printf("L");
                    gpio_put(SEGMENT_E,false);
                    gpio_put(SEGMENT_F,false);
                    gpio_put(SEGMENT_D,false);
                    sleep_ms(2000);
                    seven_segment_off();
                    break;
                case 12://M
                    printf("M");
                    gpio_put(SEGMENT_A,false);
                    gpio_put(SEGMENT_E,false);
                    gpio_put(SEGMENT_C,false);
                    sleep_ms(2000);
                    seven_segment_off();
                    break;
                case 13://N
                    printf("N");
                    gpio_put(SEGMENT_E,false);
                    gpio_put(SEGMENT_C,false);
                    gpio_put(SEGMENT_G,false);
                    sleep_ms(2000);
                    seven_segment_off();
                    break;
                case 14://O
                    printf("O");
                    gpio_put(SEGMENT_E,false);
                    gpio_put(SEGMENT_F,false);
                    gpio_put(SEGMENT_B,false);
                    gpio_put(SEGMENT_C,false);
                    gpio_put(SEGMENT_A,false);
                    gpio_put(SEGMENT_D,false);
                    sleep_ms(2000);
                    seven_segment_off();
                    break;
                case 15://P
                    printf("P");
                    gpio_put(SEGMENT_E,false);
                    gpio_put(SEGMENT_F,false);
                    gpio_put(SEGMENT_B,false);
                    gpio_put(SEGMENT_A,false);
                    gpio_put(SEGMENT_G,false);
                    sleep_ms(2000);
                    seven_segment_off();
                    break;
                case 16://Q
                    printf("Q");
                    gpio_put(SEGMENT_F,false);
                    gpio_put(SEGMENT_B,false);
                    gpio_put(SEGMENT_C,false);
                    gpio_put(SEGMENT_A,false);
                    gpio_put(SEGMENT_G,false);
                    sleep_ms(2000);
                    seven_segment_off();
                    break;
                case 17://R
                    printf("R");
                    gpio_put(SEGMENT_E,false);
                    gpio_put(SEGMENT_G,false);
                    sleep_ms(2000);
                    seven_segment_off();
                    break;
                case 18://S
                    printf("S");
                    gpio_put(SEGMENT_F,false);
                    gpio_put(SEGMENT_C,false);
                    gpio_put(SEGMENT_A,false);
                    gpio_put(SEGMENT_D,false);
                    gpio_put(SEGMENT_G,false);
                    sleep_ms(2000);
                    seven_segment_off();
                    break;
                case 19://T
                    printf("T");
                    gpio_put(SEGMENT_E,false);
                    gpio_put(SEGMENT_F,false);
                    gpio_put(SEGMENT_G,false);
                    gpio_put(SEGMENT_D,false);
                    sleep_ms(2000);
                    seven_segment_off();
                    break;
                case 20://U
                    printf("U");
                    gpio_put(SEGMENT_E,false);
                    gpio_put(SEGMENT_F,false);
                    gpio_put(SEGMENT_B,false);
                    gpio_put(SEGMENT_C,false);
                    gpio_put(SEGMENT_D,false);
                    sleep_ms(2000);
                    seven_segment_off();
                    break;
                case 21://V
                    printf("V");
                    gpio_put(SEGMENT_E,false);
                    gpio_put(SEGMENT_C,false);
                    gpio_put(SEGMENT_D,false);
                    sleep_ms(2000);
                    seven_segment_off();
                    break;
                case 22://W
                    printf("W");
                    gpio_put(SEGMENT_B,false);
                    gpio_put(SEGMENT_D,false);
                    gpio_put(SEGMENT_F,false);
                    sleep_ms(2000);
                    seven_segment_off();
                    break;
                case 23://X
                    printf("X");
                    gpio_put(SEGMENT_E,false);
                    gpio_put(SEGMENT_F,false);
                    gpio_put(SEGMENT_B,false);
                    gpio_put(SEGMENT_C,false);
                    gpio_put(SEGMENT_G,false);
                    sleep_ms(2000);
                    seven_segment_off();
                    break;
                case 24://Y
                    printf("Y");
                    gpio_put(SEGMENT_D,false);
                    gpio_put(SEGMENT_F,false);
                    gpio_put(SEGMENT_B,false);
                    gpio_put(SEGMENT_C,false);
                    gpio_put(SEGMENT_G,false);
                    sleep_ms(2000);
                    seven_segment_off();
                    break;
                case 25://Z
                    printf("Z");
                    gpio_put(SEGMENT_A,false);
                    gpio_put(SEGMENT_E,false);
                    gpio_put(SEGMENT_B,false);
                    gpio_put(SEGMENT_D,false);
                    gpio_put(SEGMENT_G,false);
                    sleep_ms(2000);
                    seven_segment_off();
                    break;
                default:
                    }
        }
    }

    // this is only executed if matched is false, so given that we haven't gone through the if statement before the switch case which checks if our input
    // exists in the alphabet array.

    // outputs error in terminal and displays number 8 with a 2 second delay, then turns display off.
    if (!matched) {
        printf("\nError. Inputted Morse code does not match with any letter of the English alphabet.\n");
        gpio_put(SEGMENT_A,false);
        gpio_put(SEGMENT_B,false);
        gpio_put(SEGMENT_C,false);
        gpio_put(SEGMENT_D,false);
        gpio_put(SEGMENT_E,false);
        gpio_put(SEGMENT_F,false);
        gpio_put(SEGMENT_G, false);
        // 2 sec delay
        sleep_ms(2000);
        // turns display off
        seven_segment_off();
    }
    matched = false;
}

// checkButton function to identify if input is a dot or dash
void checkButton(double time) {
    // if less than 250, it is a dot, otherwise a dash. Presses for more than 700 are given an error message and nothing is stored.
    if (time < 250.00) {
        strcat(letter, ".");
    } else if (time >= 250.00 && time < 700.00) {
        strcat(letter, "-");
    } else{
        printf("\nERROR. Pressed button for too long.\n");
    }
    // counter is incremented by 1 so that the program knows that at least one character is in the letter variable, so the decoder() function will be usable.
    counter += 1;
}