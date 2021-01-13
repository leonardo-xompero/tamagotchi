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
#define CHOICE_INF 0
#define CHOICE_SUP 2
int choiceX=0;

//function for return the previous menu
void return_menu(){
  myScreen.clear(blackColour);
  drawBitmap(bmp);
}

//menu for the choice of the action of the pet
bool menu_pet()
{  
  joystickYState = analogRead(joystickY);
  joystickYState = map(joystickYState, 0, 4096, 0, 255);
  if (joystickYState > 60)
  {
    beep(NOTE_C6, 125);  
    //choiceX = 0;
    if(choiceX>CHOICE_INF){
      choiceX--;
      delay(10);
    }
  }
  else if (joystickYState < 10)
  {
    beep(NOTE_C6, 125); 
    //choiceX = 1;
    if(choiceX<CHOICE_SUP){
      choiceX++;
      delay(10);
    }
  }
  switch (choiceX)
  {
    case 0:
        myScreen.gText(30, 30, "walk", greenColour, orangeColour, 1, 1);
        myScreen.gText(30, 50, "sleep", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 70, "exit", greenColour, blackColour, 1, 1);
        break;
    case 1:
        myScreen.gText(30, 30, "walk", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 50, "sleep", greenColour, orangeColour, 1, 1);
        myScreen.gText(30, 70, "exit", greenColour, blackColour, 1, 1);
        break;
        
    case 2:
        myScreen.gText(30, 30, "walk", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 50, "sleep", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 70, "exit", greenColour, orangeColour, 1, 1);
        break;      
  }
  
  buttonOneState = digitalRead(buttonOne);
    
  if(buttonOneState==LOW){
    switch (choiceX)
    {
      case 0:
          break;
      case 1:
          break;
          
      case 2:
          beep(NOTE_GS3, 125);  
          return_menu();
          choiceX=0;
          busyMenu=false;
          return false;
          break;          
    }
  }
    
  return true;
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
    
    //life();
    buttonTwoState=digitalRead(buttonTwo);
    if(buttonTwoState==LOW){
      busyMenu=true;
      myScreen.clear(blackColour);
      //continuos cycle in the menu until a function is selected or exited
      while(menu_pet());
    }
  }
}
