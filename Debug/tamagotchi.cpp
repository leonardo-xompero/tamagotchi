#include "Energia.h"

#line 1 "C:/ti/workspace/tamagotchi/tamagotchi.ino"

#if defined(ENERGIA) 
#include "Energia.h"
#else 
#error Platform not defined
#endif


#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "HAL_I2C.h"
#include "HAL_TMP006.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>


#include <SPI.h>
#include <LCD_screen.h>
#include <LCD_screen_font.h>
#include <LCD_utilities.h>
#include <Screen_HX8353E.h>
#include <Terminal12e.h>
#include <Terminal6e.h>
#include <Terminal8e.h>

#include "images/pet_models.h"
void drawBitmap(const unsigned char *bmp);
void life();
bool menu();
void menu_pet();
void setup();
void loop();
void WDT_A_IRQHandler(void);

#line 29
Screen_HX8353E myScreen;



#define x_image 64
#define y_image 64

const int buttonOne = 33;     
const int buttonTwo = 32;     
const int ledGreen = 38;      
const int ledBlue = 37;      
const int ledRed = 39;        

const int joystickSel = 5;     
const int joystickX = 2;       
const int joystickY = 26;     


int buttonOneState = 0;         
int buttonTwoState = 0;         

int joystickSelState = 0;      
int joystickXState, joystickYState;

int life_pet = 100;
char string[10];
bool menu_step = false;
bool choice;


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


void life()
{
    sprintf(string, "Health : %03d", life_pet);
    myScreen.gText(30, 100, string, greenColour, 1, 1);
    life_pet--;
    delay(1000);
}


bool menu()
{
    
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

void menu_pet()
{
    bool choiceY;
    joystickYState = analogRead(joystickY);
    joystickYState = map(joystickYState, 0, 4096, 0, 255);
    if (joystickYState > 60)
    {
        choiceY = false;
    }
    else if (joystickYState < 10)
    {
        choiceY = true;
    }
    switch (choiceY)
    {
    case false:
        myScreen.gText(30, 5, "play", greenColour, orangeColour, 1, 1);
        myScreen.gText(30, 120, "eat", greenColour, blackColour, 1, 1);
        break;
    case true:
        myScreen.gText(30, 5, "play", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 120, "eat", greenColour, orangeColour, 1, 1);
        break;
    }
    buttonOneState = digitalRead(buttonOne);
    if (buttonOneState == LOW && !menu_step)
    {

    }
    else if (buttonOneState == LOW && menu_step)
    {

    }

}


void setup()
{
    myScreen.begin();

    pinMode(joystickSel, INPUT_PULLUP);
    
    pinMode(buttonOne, INPUT_PULLUP);

    if (menu())
    {
        myScreen.clear(blackColour);
        drawBitmap(bmp);
    }
    else
    {
        myScreen.clear(blackColour);
        drawBitmap(nc_bmp);
    }

}


void loop()
{
    life();
}

void WDT_A_IRQHandler(void)
{
    menu_pet();
}



