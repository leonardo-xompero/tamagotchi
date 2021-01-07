// Core library for code-sense
#if defined(ENERGIA) // LaunchPad MSP430, Stellaris and Tiva, Experimeter Board FR5739 specific
#include "Energia.h"
#else // error
#error Platform not defined
#endif

// Library for simplekit
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "HAL_I2C.h"
#include "HAL_TMP006.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Following includes for Energia only
#include <SPI.h>
#include <LCD_screen.h>
#include <LCD_screen_font.h>
#include <LCD_utilities.h>
#include <Screen_HX8353E.h>
#include <Terminal12e.h>
#include <Terminal6e.h>
#include <Terminal8e.h>
// Define variables and constants
//size of the image
#define x_image 64
#define y_image 64
int choiceY;

void menu_pet_y()
{

    joystickYState = analogRead(joystickY);
    joystickYState = map(joystickYState, 0, 4096, 0, 255);
    if (joystickYState > 60)
    {
        choiceY = 0;
    }
    else if (joystickYState < 10)
    {
        choiceY = 1;
    }
    else
        choiceY = 2;
    switch (choiceY)
    {
    case 0:
        myScreen.gText(30, 5, "play", greenColour, orangeColour, 1, 1);
        myScreen.gText(30, 120, "eat", greenColour, blackColour, 1, 1);
        break;
    case 1:
        myScreen.gText(30, 5, "play", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 120, "eat", greenColour, orangeColour, 1, 1);
        break;
    case 2:
        myScreen.gText(30, 5, "play", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 120, "eat", greenColour, blackColour, 1, 1);
        break;
    }
    buttonOneState = digitalRead(buttonOne);
    if (buttonOneState == LOW && menu_step != 0)
    {

    }
    else if (buttonOneState == LOW && menu_step == 1)
    {

    }

}

// Add setup code
void menu_pet_y_setup()
{

}

// Add loop code
void menu_pet_y_loop()
{
    menu_pet_y();
}
