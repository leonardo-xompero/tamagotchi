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
void setup();
void loop();

#line 27
Screen_HX8353E myScreen;


uint32_t chrono;

#include "Energia_logo_100_132.h"



void setup() {

}


void loop() {

}





