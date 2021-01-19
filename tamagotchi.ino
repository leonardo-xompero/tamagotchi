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
#include <cstdlib>
#include <time.h>

// Following includes for Energia only
#include <SPI.h>
#include <LCD_screen.h>
#include <LCD_screen_font.h>
#include <LCD_utilities.h>
#include <Screen_HX8353E.h>
#include <Terminal12e.h>
#include <Terminal6e.h>
#include <Terminal8e.h>
#include <OPT3001.h>
//include images of the pet
#include "pet/pet_models.h"
#include "pet/pet_music.h"
#include "variables.h"

Screen_HX8353E myScreen;
opt3001 opt3001;

//initial message
void intro(){
  myScreen.gText(5, 30, "TAMAGOTCHI", orangeColour, blackColour, 2, 2);
  myScreen.gText(60, 90, "by", orangeColour, blackColour, 1, 1);
  myScreen.gText(15, 100, "Leonardo Xompero", orangeColour, blackColour, 1, 1);
  delay(TIME_MESSAGE);
  myScreen.clear(blackColour);
}

void beep(int note, int duration)
{
  tone(buzzerPin, note, duration/2);
  delay(duration/2);
  noTone(buzzerPin);
  delay(duration/2 + 20);  
}


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


float getTemp(void)
{
  uint32_t cal30;
  uint32_t cal85;
  float calDifference;
  float tempC;
  int16_t conRes;
  uint64_t status;



  /* Initializing ADC (MCLK/1/1) with temperature sensor routed */
  ADC14_enableModule();
  ADC14_initModule(ADC_CLOCKSOURCE_MCLK, ADC_PREDIVIDER_1, ADC_DIVIDER_1,
                   ADC_TEMPSENSEMAP);

  /* Configuring ADC Memory (ADC_MEM0 A22 (Temperature Sensor) in repeat
     mode).
  */
  ADC14_configureSingleSampleMode(ADC_MEM0, true);
  ADC14_configureConversionMemory(ADC_MEM0, ADC_VREFPOS_INTBUF_VREFNEG_VSS,
                                  ADC_INPUT_A22, false);

  /* Configuring the sample/hold time for 192 */
  ADC14_setSampleHoldTime(ADC_PULSE_WIDTH_192, ADC_PULSE_WIDTH_192);

  /* Enabling sample timer in auto iteration mode and interrupts*/
  ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);
  ADC14_enableInterrupt(ADC_INT0);

  /* Setting reference voltage to 2.5 and enabling temperature sensor */
  REF_A_enableTempSensor();
  REF_A_setReferenceVoltage(REF_A_VREF2_5V);
  REF_A_enableReferenceVoltage();

  cal30 = SysCtl_getTempCalibrationConstant(SYSCTL_2_5V_REF,
          SYSCTL_30_DEGREES_C);
  cal85 = SysCtl_getTempCalibrationConstant(SYSCTL_2_5V_REF,
          SYSCTL_85_DEGREES_C);
  calDifference = cal85 - cal30;

  /* Triggering the start of the sample */
  ADC14_enableConversion();
  ADC14_toggleConversionTrigger();

  status = MAP_ADC14_getInterruptStatus();

  while ((ADC_INT0 & status) == 0) {
    status = MAP_ADC14_getInterruptStatus();
  }

  conRes = ((ADC14_getResult(ADC_MEM0) - cal30) * 55);
  tempC = (conRes / calDifference) + 30.0f;
  //tempF = tempC * 9.0f / 5.0f + 32.0f;

  /* clear out last sample */
  MAP_ADC14_clearInterruptFlag(status);


  return tempC;

}

//function for the life of the pet
void life()
{
  /*
    float objt = tmp006.readObjTempC();
    float diet = tmp006.readDieTempC();
  */
  if(life_pet>0){
    if(life_pet<LOW_LIFE) rested=false;
    sprintf(string, "Health : %03d", life_pet);
    if(whiteLight==1) myScreen.gText(30, 20, string, blackColour, greenColour, 1, 1);
    else myScreen.gText(30, 20, string, greenColour, blackColour, 1, 1);
    life_pet--;
  }
  else{
    gameOver();
  }


  /*
  fTemp = getTemp();
  sprintf(temp, "Temp : %f", fTemp);
  myScreen.gText(30, 110, temp, greenColour, 1, 1);
  */

  delay(1000);
}

//in the game over, i block everything
void gameOver(){
  game_over=true;
  goMenu=false;
  myScreen.clear(blackColour);
  if(choice) drawBitmap(bmp);
  else drawBitmap(nc_bmp);
  myScreen.gText(30, 20, "Game Over", redColour, 1, 1);
}

void light(){
  uint8_t backlight = 0;
  // Variables
  unsigned long readings;
  temp[0]='\0';
  // Read OPT3001
  readings = opt3001.readResult();  //min = 0, max = 131040
  
  backlight = map(readings,darkestLUX, brightestLUX, dimmestBacklight, brightestBacklight);  //simple linear backlight
  backlight = constrain(backlight, dimmestBacklight, brightestBacklight);  // keep value between the acceptable value of analogWrite()
  analogWrite(backlightPin, backlight);
  
  
  //sprintf(temp, "Light : %2d", readings); //doesn't work without that (don't know why, to check later)
  //myScreen.gText(30, 110, temp, greenColour, 1, 1);

  //sequence to check if there's some obstruction of the light
  if(blackLight==0 && whiteLight==1 && readings<LIGHT_LIMIT){
    myScreen.clear(blackColour);
    if(choice) drawBitmap(bmp);
    else drawBitmap(nc_bmp);
    blackLight=1;
    whiteLight=0;
  }
  else if(blackLight==1 && whiteLight==0 && readings>=LIGHT_LIMIT){
    myScreen.clear(whiteColour);
    if(choice) drawBitmap(bmp);
    else drawBitmap(nc_bmp);
    blackLight=0;
    whiteLight=1;
  }
  delay(100);
}

//initial menu for the choice, return a boolean for decide the next state
bool menu()
{
  intro();
  myScreen.gText(20, 20, "Choose your pet", yellowColour, blackColour, 1, 1);
  //stay in the loop until the user makes a decision
  for (;;)
  {
    joystickXState = analogRead(joystickX);
    joystickXState = map(joystickXState, 0, 4096, 0, 255);
    if (joystickXState < 10)
    {
      beep(NOTE_C6, 125);  
      menu_step = false;
    }
    else if (joystickXState > 60)
    {
      beep(NOTE_C6, 125); 
      menu_step = true;
    }
    switch (menu_step)
    {
      case false:
        myScreen.gText(30, 60, "pet1", myScreen.reverseColour(greenColour), blackColour, 1,
                       1);
        myScreen.gText(80, 60, "pet2", greenColour, blackColour, 1,
                       1);
        break;
      case true:
        myScreen.gText(30, 60, "pet1", greenColour, blackColour, 1,
                       1);
        myScreen.gText(80, 60, "pet2", myScreen.reverseColour(greenColour), blackColour,
                       1, 1);
        break;
    }
    buttonOneState = digitalRead(buttonOne);
    if (buttonOneState == LOW && !menu_step)
    {
      beep(NOTE_GS3, 125);  
      return true;
    }
    else if (buttonOneState == LOW && menu_step)
    {
      beep(NOTE_GS3, 125);  
      return false;
    }
  }
}


// Add setup code
void setup()
{
  //initialized the screen
  myScreen.begin();
  //initialized the sensor for the light
  opt3001.begin(); 
  
  //initialize the buzzer
  pinMode(buzzerPin,OUTPUT);

  //initialize the joystick and the button
  pinMode(joystickSel, INPUT_PULLUP);
  //pinMode(ledGreen, OUTPUT);
  pinMode(buttonOne, INPUT_PULLUP);

  if (menu())
  {
    myScreen.clear(whiteColour);
    drawBitmap(bmp);
    choice=true;
  }
  else
  {
    myScreen.clear(whiteColour);
    drawBitmap(nc_bmp);
    choice=false;
  }
  goMenu=true;
}

// Add loop code
void loop()
{
  //if the menu of the pet is not active, then i can use the light and the life
  if(!busyMenu && !game_over){
    life();
    light();
  }
}
