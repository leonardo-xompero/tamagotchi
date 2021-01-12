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
int choiceX;

void menu_pet()
{

    joystickXState = analogRead(joystickX);
    joystickXState = map(joystickXState, 0, 4096, 0, 255);
    if (joystickXState < 10)
    {
        choiceX = 0;
    }
    else if (joystickXState > 60)
    {
        choiceX = 1;
    }
    else
        choiceX = 2;
    switch (choiceX)
    {
    case 0:
        myScreen.gText(20, 110, "walk", greenColour, orangeColour, 1, 1);
        myScreen.gText(70, 110, "sleep", greenColour, blackColour, 1, 1);
        break;
    case 1:
        myScreen.gText(20, 110, "walk", greenColour, blackColour, 1, 1);
        myScreen.gText(70, 110, "sleep", greenColour, orangeColour, 1, 1);
        break;
    case 2:
        myScreen.gText(20, 110, "walk", greenColour, blackColour, 1, 1);
        myScreen.gText(70, 110, "sleep", greenColour, blackColour, 1, 1);
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
void menu_pet_setup()
{
    
}

// Add loop code
void menu_pet_loop()
{
  //if i made the choice in the menu, then i can start the task
  if(goMenu){
    menu_pet();
  }
}
