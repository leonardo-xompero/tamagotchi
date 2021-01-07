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
//include images of the pet
#include "images/pet_models.h"
Screen_HX8353E myScreen;

// Define variables and constants
//size of the image
#define x_image 64
#define y_image 64

const int buttonOne = 33;     // the number of the pushbutton pin
const int buttonTwo = 32;     // the number of the pushbutton pin
const int ledGreen = 38;      // the number of the LED pin
const int ledBlue = 37;      // the number of the LED pin
const int ledRed = 39;        // the number of the LED pin

const int joystickSel = 5;     // the number of the joystick select pin
const int joystickX = 2;       // the number of the joystick X-axis analog
const int joystickY = 26;     // the number of the joystick Y-axis analog

// variables will change:
int buttonOneState = 0;         // variable for reading the pushbutton #1 status
int buttonTwoState = 0;         // variable for reading the pushbutton #2 status

int joystickSelState = 0;      // variable for reading the joystick sel status
int joystickXState, joystickYState;

int life_pet = 100;
char string[10];
bool menu_step = false;
bool choice;

//function for printing the images from an array of char
void drawBitmap(const unsigned char *bmp)
{

    uint32_t p;
    uint16_t c;
    uint16_t x00 = 0;
    uint16_t y00 = 0;
    uint16_t i00 = 0;
    uint16_t j00 = 0;

    if ((myScreen.screenSizeX() > x_image))
    {
        x00 = (myScreen.screenSizeX() - x_image) / 2;
    }
    else
    {
        i00 = (x_image - myScreen.screenSizeX()) / 2;
    }
    if ((myScreen.screenSizeY() > y_image))
    {
        y00 = (myScreen.screenSizeY() - y_image) / 2;
    }
    else
    {
        j00 = (y_image - myScreen.screenSizeY()) / 2;
    }

    uint16_t ca;
    unsigned char cu;
    unsigned char cl;
    uint16_t x = x_image;
    uint16_t y = y_image;
    for (uint16_t j = 0; j < y; j++)
    {
        for (uint16_t i = 0; i < x; i++)
            if ((x00 + i < myScreen.screenSizeX())
                    && (y00 + j < myScreen.screenSizeY()))
            {
                {
                    cu = bmp[(j * 2) * x + 5 + (i * 2)];
                    cl = bmp[(j * 2) * x + 5 + (i * 2) + 1];
                    c = cu;
                    c = c << 8;
                    c |= 0x00FF;
                    ca = cl;
                    ca |= 0xFF00;
                    c &= ca;
                    myScreen.point(x00 + i - i00, y00 + j - j00, c);
                }
            }
    }
}

//function for the life of the pet
void life()
{
    life_pet--;
    sprintf(string, "%d", life_pet);
    myScreen.gText(30, 120, string, greenColour, orangeColour, 1, 1);
    delay(1000);
}

//initial menu for the choice, return a boolean for decide the next state
bool menu()
{
    //stay in the loop until the user makes a decision
    for (;;)
    {
        joystickYState = analogRead(joystickY);
        joystickYState = map(joystickYState, 0, 4096, 0, 255);
        if (joystickYState > 60)
        {
            menu_step = false;
        }
        else if (joystickYState < 10)
        {
            menu_step = true;
        }
        switch (menu_step)
        {
        case false:
            myScreen.gText(30, 5, "colored pet", greenColour, orangeColour, 1,
                           1);
            myScreen.gText(30, 20, "uncolored pet", greenColour, blackColour, 1,
                           1);
            break;
        case true:
            myScreen.gText(30, 5, "colored pet", greenColour, blackColour, 1,
                           1);
            myScreen.gText(30, 20, "uncolored pet", greenColour, orangeColour,
                           1, 1);
            break;
        }
        buttonOneState = digitalRead(buttonOne);
        if (buttonOneState == LOW && !menu_step)
        {
            return true;
        }
        else if (buttonOneState == LOW && menu_step)
        {
            return false;
        }
    }
}

// Add setup code
void setup()
{
    myScreen.begin();

    pinMode(joystickSel, INPUT_PULLUP);
    //pinMode(ledGreen, OUTPUT);
    pinMode(buttonOne, INPUT_PULLUP);

    if (menu())
    {
        myScreen.clear(blackColour);
        choice = true;
    }
    else
    {
        myScreen.clear(blackColour);
        choice = false;
    }

}

// Add loop code
void loop()
{
    life();
    if (choice)
    {
        drawBitmap(bmp);
    }
    else
    {
        drawBitmap(nc_bmp);
    }
}

