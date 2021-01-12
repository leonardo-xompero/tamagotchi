#include <OPT3001.h>



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
//include images of the pet
#include "pet/pet_models.h"
#include "pet/pet_music.h"

Screen_HX8353E myScreen;
opt3001 opt3001;

// Define variables and constants
//size of the image
#define x_image 64
#define y_image 64
//limit of light value to change background
#define LIGHT_LIMIT 50

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

//variables for the light sensor
const uint8_t backlightPin = 39; //PWM-capable pin tied to backlight
const uint16_t darkestLUX = 0; 
const uint16_t brightestLUX = 4000;
const uint8_t dimmestBacklight = 55;
const uint8_t brightestBacklight = 254;

//pin for the buzzer
int buzzerPin = 40;

float fTemp;
char temp[10];

//variables for checking the background
int blackLight=1;
int whiteLight=0;


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
  sprintf(string, "Health : %03d", life_pet);
  myScreen.gText(30, 100, string, greenColour, 1, 1);


  /*
  fTemp = getTemp();
  sprintf(temp, "Temp : %f", fTemp);
  myScreen.gText(30, 110, temp, greenColour, 1, 1);
  */

  life_pet--;
  delay(1000);
}

void light(){
  uint8_t backlight = 0;
  // Variables
  unsigned long readings;
     
  // Read OPT3001
  readings = opt3001.readResult();  //min = 0, max = 131040
  
  backlight = map(readings,darkestLUX, brightestLUX, dimmestBacklight, brightestBacklight);  //simple linear backlight
  backlight = constrain(backlight, dimmestBacklight, brightestBacklight);  // keep value between the acceptable value of analogWrite()
  analogWrite(backlightPin, backlight);
  
  
  sprintf(temp, "Light : %03d", readings);
  myScreen.gText(30, 110, temp, greenColour, 1, 1);

  //sequence to check if there's some obstruction of the light
  if(blackLight==1 && whiteLight==0 && readings<LIGHT_LIMIT){
    myScreen.clear(whiteColour);
    if(choice) drawBitmap(bmp);
    else drawBitmap(nc_bmp);
    blackLight=0;
    whiteLight=1;
  }
  else if(blackLight==0 && whiteLight==1 && readings>=LIGHT_LIMIT){
    myScreen.clear(blackColour);
    if(choice) drawBitmap(bmp);
    else drawBitmap(nc_bmp);
    blackLight=1;
    whiteLight=0;
  }
  delay(100);
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
      beep(NOTE_C6, 125);  
      menu_step = false;
    }
    else if (joystickYState < 10)
    {
      beep(NOTE_C6, 125); 
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
    myScreen.clear(blackColour);
    drawBitmap(bmp);
    choice=true;
  }
  else
  {
    myScreen.clear(blackColour);
    drawBitmap(nc_bmp);
    choice=false;
  }
}

// Add loop code
void loop()
{
  //tmp006.begin();
  life();
  light();
}
