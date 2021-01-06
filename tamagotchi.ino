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
Screen_HX8353E myScreen;

// Define variables and constants
uint32_t chrono;

#include "Energia_logo_100_132.h"


// Add setup code
void setup() {

}

// Add loop code
void loop() {

}


