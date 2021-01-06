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
void drawBitmap(const unsigned char *bmp);
void setup();
void loop();

#line 27
Screen_HX8353E myScreen;


uint32_t chrono;

#include "Energia_logo_100_132.h"
#include "images/pet_models.h"

#define x_image 128
#define y_image 128

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


void setup() {
    myScreen.begin();
}


void loop() {
    drawBitmap(bmp);
}





