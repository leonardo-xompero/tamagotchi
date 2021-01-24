// Define variables and constants

#define LIGHT_LIMIT 80		//limit of light value to change background
#define LIFE_PET 100		//life of the pet

#define CHOICE_INF 0    //lower limit of the choices
#define CHOICE_SUP 5    //unper bound of the choice (the value is #choices-1)

#define TIME_MESSAGE 3000   //variable for the delay for showing the message

#define BAR_LIMIT 18	//limit of the bar game (the value was obtained with a long sequence of trial & error)
#define TIME_BAR  500  //time of delay for the loading of the bar
#define TIME_SLEEP 60 //how much time the pet need to sleep
#define TIME_EAT 1000 //time to eat

#define LOW_LIFE 30 //the minimum amout of life for make the pet sleep
#define LIFE 1000 //duration of a unit of life

#define MIN_TEMP 20 //min temperature before it's considered cold
#define MAX_TEMP 30 //max temperature before it's considered hot

int tempOutside; //flag to check the temperature outside

char bar[BAR_LIMIT];  //array of char to simulate the bar loading
int bar_loaded=0;     //contator for the loading
int randOrientation;  //variable generated randomly, needed for the random inclination of the bar (not implemented)
bool winGame=false;   //booleab to check if the player won the game

const int redLED= 39; // assign red LED to Pin #9
const int greenLED= 38;// assign green LED to Pin #10
const int blueLED= 37; // assign blueLED to Pin #12

const int xpin = 23; // x-axis of the accelerometer
const int ypin = 24; // y-axis
const int zpin = 25; // z-axis (only on 3-axis models)

const int buttonOne = 33;     // the number of the pushbutton pin
const int buttonTwo = 32;     // the number of the pushbutton pin
const int ledGreen = 38;      // the number of the LED pin
const int ledBlue = 37;      // the number of the LED pin
const int ledRed = 39;        // the number of the LED pin

const int joystickSel = 5;     // the number of the joystick select pin
const int joystickX = 2;       // the number of the joystick X-axis analog
const int joystickY = 26;     // the number of the joystick Y-axis analog

const int mic = 6;    //pin for the microphone

// variables will change:
int buttonOneState = 0;         // variable for reading the pushbutton #1 status
int buttonTwoState = 0;         // variable for reading the pushbutton #2 status

int joystickSelState = 0;      // variable for reading the joystick sel status
int joystickXState, joystickYState;		//state if the joystick

int life_pet = LIFE_PET;	//assign the pet life to a variable
char string[10];
//choice of the firs menu
bool menu_step = false;
//choice of the pet
bool choice;

//variables for the light sensor
const uint8_t backlightPin = 39; //PWM-capable pin tied to backlight
const uint16_t darkestLUX = 0; 
const uint16_t brightestLUX = 4000;
const uint8_t dimmestBacklight = 55;
const uint8_t brightestBacklight = 254;


int buzzerPin = 40;		//pin for the buzzer

//float fTemp;
char temp[8];

//variable for the temperature
float tempReading = 0;

//variables for checking the background
int blackLight=0;
int whiteLight=1;

bool rested=false; //boolean to check if the pet is rested
int sleep;    //time to sleep

bool goMenu=false;		//boolen to make pet_menu start

bool busyMenu=false;		//semaphore to stop the life for the menu

bool game_over=false; //boolean for the gameover

int choiceX=0;	//variable for the choice in the pet menu

//velocity
int tempo = 114;
int notes = sizeof(melody) / sizeof(melody[0]) / 2;
// this calculates the duration of a whole note in ms
int wholenote = (60000 * 4) / tempo;
int divider = 0, noteDuration = 0;
