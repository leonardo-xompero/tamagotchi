//function for return the previous menu
bool return_menu(){
  if(blackLight==1)myScreen.clear(blackColour);
  else myScreen.clear(whiteColour);  
  if(life_pet>=LOW_LIFE){
      if(choice) drawBitmap(pet1_calm,64,64);
      else drawBitmap(pet2_calm,64,64);
  }else{
    if(choice) drawBitmap(pet1_weak,64,64);
    else drawBitmap(pet2_weak,64,64);
  }
  choiceX=0;
  busyMenu=false;
  return false;
}

int checkOutside(){
  int tempOk;
  float temp=temperature();
  if(temp<MIN_TEMP) tempOk=-1;
  else if(temp>MAX_TEMP) tempOk=1;
  else tempOk=0;
  delay(TIME_MESSAGE);
  if(tempOk==0){
    myScreen.gText(10,90,"The pet wants to" , greenColour);
    myScreen.gText(10,100,"go outside!" , greenColour);
    delay(TIME_MESSAGE);
  }
  myScreen.clear(blackColour);
  return tempOk;
}

void initDance(){  
  myScreen.gText(10, 40, "Listen to the song", yellowColour, blackColour, 1, 1);
  myScreen.gText(10, 50, "OR", yellowColour, blackColour, 1, 1);
  myScreen.gText(10, 60, "press button 2", yellowColour, blackColour, 1, 1);
  myScreen.gText(10, 70, "to skip.", yellowColour, blackColour, 1, 1);
  delay(TIME_MESSAGE);
  myScreen.clear(blackColour);
}

void initWalk(){
  bar_loaded=0;
  //initialize the bar
  for(int x=0;x<11;x++) bar[x]='-';
  bar[0]='|';
  randOrientation=3;
  winGame=false;
  myScreen.gText(10, 10, "Tilt the board", yellowColour, blackColour, 1, 1);
  myScreen.gText(10, 20, "to the top", yellowColour, blackColour, 1, 1);
  myScreen.gText(10, 30, "to refill the bar.", yellowColour, blackColour, 1, 1);
  myScreen.gText(10, 60, "Press button 2", redColour, blackColour, 1, 1);
  myScreen.gText(10, 70, "to exit.", redColour, blackColour, 1, 1);
  delay(TIME_MESSAGE);
  myScreen.clear(blackColour);
}
void initFood(){
  bar_loaded=0;
  //initialize the bar
  for(int x=0;x<BAR_LIMIT;x++) bar[x]='-';
  bar[0]='|';
  randOrientation=0;
  winGame=false;
  myScreen.gText(10, 20, "Wait", yellowColour, blackColour, 1, 1);
  myScreen.gText(10, 30, "to refill the bar.", yellowColour, blackColour, 1, 1);
  myScreen.gText(10, 60, "Press button 2", redColour, blackColour, 1, 1);
  myScreen.gText(10, 70, "to exit.", redColour, blackColour, 1, 1);
  delay(TIME_MESSAGE);
  myScreen.clear(blackColour);
}

void initPlay(){
  //drawBitmap(bmp,64,64);
  //myScreen.gText(5, 20, "Play with your pet!", blueColour, blackColour, 1, 1);
  bar_loaded=0;
  //initialize the bar
  for(int x=0;x<BAR_LIMIT;x++) bar[x]='-';
  bar[0]='|';
  
  //srand(time(0));   //use the time for the seed  
  //randOrientation= rand() % 3;  //set a random orienation for the game
  randOrientation=0;
  winGame=false;
  myScreen.gText(10, 10, "Tilt the board", yellowColour, blackColour, 1, 1);
  myScreen.gText(10, 20, "to the right", yellowColour, blackColour, 1, 1);
  myScreen.gText(10, 30, "to refill the bar.", yellowColour, blackColour, 1, 1);
  myScreen.gText(10, 60, "Press button 2", redColour, blackColour, 1, 1);
  myScreen.gText(10, 70, "to exit.", redColour, blackColour, 1, 1);
  delay(TIME_MESSAGE);
  myScreen.clear(blackColour);
}

//show the message after the action, the points may vary from the action performed
void showMessage(int points){  
    char sPoints[10];
    sprintf(sPoints, "by %d", points); 
    myScreen.clear(blackColour);
    myScreen.gText(30, 50, "The pet life", yellowColour, blackColour, 1, 1);
    myScreen.gText(30, 60, "is increased", yellowColour, blackColour, 1, 1);
    myScreen.gText(30, 70, sPoints, yellowColour, blackColour, 1, 1);
    delay(TIME_MESSAGE);
    //check the limit
    if( life_pet+points<999)
      life_pet+=points;
}

//the random variables decides the axys of the screen
bool petPlay(){
    myScreen.setOrientation(randOrientation);
    myScreen.gText(50, 5, "Play!", yellowColour, blackColour, 1, 1);
    myScreen.gText(10,10,"0",greenColour,blackColour,1,1);
    myScreen.gText(115,10,"F",greenColour,blackColour,1,1);
    myScreen.gText(10,20,bar,greenColour,blackColour,1,1);
    analogReadResolution(12);
    //foor the accelerometer, we need 12 bit, so we set it 
    int analogValue;
    //check the orientation generated
    if(randOrientation == 0){
      // CHECK X AXIS (red) 
      digitalWrite(redLED,HIGH);
      analogValue = analogRead(xpin); // read Y axis 
      if(analogValue >2048){ // check if tilting on x axis in positive direction
         if(bar_loaded<BAR_LIMIT){
            bar[bar_loaded]='|';
            bar_loaded++;
         }else{
            winGame=true;
            digitalWrite(redLED,LOW);
            digitalWrite(greenLED,HIGH);
         }
         delay(TIME_BAR);
      } 
      else { // check if tilting on x axis in negative direction 
          if(bar_loaded>0){            
            bar_loaded--;
            bar[bar_loaded]='-';
          }
      }      
      
    }
  //now we need to set the default value for msp432
  analogReadResolution(10);
  buttonTwoState=digitalRead(buttonTwo);
  if(buttonTwoState==LOW || winGame) {
    myScreen.setOrientation(0);
    return false;
  }
  else return true;
}

bool petSleep(){
  char bed_time[20];
  sprintf(bed_time, "TIME RESTED : %03d", sleep);
  myScreen.gText(5, 10, bed_time, yellowColour, blackColour, 1, 1);
  sprintf(bed_time, "GOAL : %03d", TIME_SLEEP);
  myScreen.gText(5, 20, bed_time, yellowColour, blackColour, 1, 1);
  if(sleep>=TIME_SLEEP) rested=true;
  else sleep++;
  delay(1000);
  buttonTwoState=digitalRead(buttonTwo);
  if(buttonTwoState==LOW || rested) return false;
  else return true;
}

bool petWalk(){
  myScreen.setOrientation(randOrientation);
  myScreen.gText(30,10,bar,greenColour,blackColour,1,1);
  myScreen.gText(30,110,bar,greenColour,blackColour,1,1);
  int analogValue;
  analogReadResolution(12);
  analogValue = analogRead(ypin); // read Y axis 
  if(analogValue >2048){ // check if tilting on y axis in positive direction
       if(bar_loaded<11){
          bar[bar_loaded]='|';
          bar_loaded++;
       }else{
          winGame=true;
          digitalWrite(redLED,LOW);
          digitalWrite(greenLED,HIGH);
       }
       delay(500);
    } 
    else { // check if tilting on y axis in negative direction 
        if(bar_loaded>0){            
          bar_loaded--;
          bar[bar_loaded]='-';
        }
    }   
  analogReadResolution(10);
  buttonTwoState=digitalRead(buttonTwo);
  if(buttonTwoState==LOW || winGame) {
    myScreen.setOrientation(0);
    return false;
  }
  else return true;
}

bool petEat(){
  myScreen.gText(10,100,bar,greenColour,blackColour,1,1);
  if(bar_loaded<BAR_LIMIT){
      bar[bar_loaded]='|';
      bar_loaded++;          
      delay(TIME_EAT);
   }else{
      winGame=true;
      digitalWrite(redLED,LOW);
      digitalWrite(greenLED,HIGH);
   }  
  
  buttonTwoState=digitalRead(buttonTwo);
  if(buttonTwoState==LOW || winGame) {
    myScreen.setOrientation(0);
    return false;
  }
  else return true;
}

//function for the event "dance"
bool petDance(){  
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzerPin, melody[thisNote], noteDuration * 0.9);

    // Wait for the special duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(buzzerPin);

    //check if the user pressed the button 2
    buttonTwoState=digitalRead(buttonTwo);
    if(buttonTwoState==LOW) break;
  }
  return false;
}

//menu for the choice of the action of the pet
bool menu_pet()
{  
  joystickYState = analogRead(joystickY);
  joystickYState = map(joystickYState, 0, 4096, 0, 255);
  if (joystickYState > 60)
  {
    beep(NOTE_C6, 125);
    if(choiceX>CHOICE_INF){
      choiceX--;
      delay(10);
    }
  }
  else if (joystickYState < 10)
  {
    beep(NOTE_C6, 125); 
    if(choiceX<CHOICE_SUP){
      choiceX++;
      delay(10);
    }
  }
  switch (choiceX)
  {
    case 0:
        myScreen.gText(30, 10, "1 - Dance", greenColour, orangeColour, 1, 1);
        myScreen.gText(30, 30, "2 - Walk", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 50, "3 - Sleep", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 70, "4 - Eat", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 90, "5 - Play", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 110,"6 - Exit", greenColour, blackColour, 1, 1);
        break;
        
    case 1:
        myScreen.gText(30, 10, "1 - Dance", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 30, "2 - Walk", greenColour, orangeColour, 1, 1);
        myScreen.gText(30, 50, "3 - Sleep", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 70, "4 - Eat", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 90, "5 - Play", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 110,"6 - Exit", greenColour, blackColour, 1, 1);
        break;
        
    case 2:
        myScreen.gText(30, 10, "1 - Dance", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 30, "2 - Walk", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 50, "3 - Sleep", greenColour, orangeColour, 1, 1);
        myScreen.gText(30, 70, "4 - Eat", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 90, "5 - Play", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 110,"6 - Exit", greenColour, blackColour, 1, 1);
        break;
        
    case 3:
        myScreen.gText(30, 10, "1 - Dance", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 30, "2 - Walk", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 50, "3 - Sleep", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 70, "4 - Eat", greenColour, orangeColour, 1, 1);
        myScreen.gText(30, 90, "5 - Play", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 110,"6 - Exit", greenColour, blackColour, 1, 1);
        break;      

    case 4:
        myScreen.gText(30, 10, "1 - Dance", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 30, "2 - Walk", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 50, "3 - Sleep", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 70, "4 - Eat", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 90, "5 - Play", greenColour, orangeColour, 1, 1);
        myScreen.gText(30, 110,"6 - Exit", greenColour, blackColour, 1, 1);
        break; 

    case 5:
        myScreen.gText(30, 10, "1 - Dance", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 30, "2 - Walk", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 50, "3 - Sleep", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 70, "4 - Eat", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 90, "5 - Play", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 110,"6 - Exit", greenColour, orangeColour, 1, 1);
        break; 
  }
  
  buttonOneState = digitalRead(buttonOne);
    
  if(buttonOneState==LOW){
    switch (choiceX)
    {
      case 0: //dance
          beep(NOTE_B5, 125);
          myScreen.clear(blackColour);
          initDance();
          if(choice) drawBitmap(pet1_dance,64,64);
          else drawBitmap(pet2_dance,64,64);
          myScreen.gText(5, 10, "The pet is dancing!", yellowColour, blackColour, 1, 1);
          while(petDance());
          if(choice) drawBitmap(pet1_happy,64,64);
          else drawBitmap(pet2_happy1,64,64);
          myScreen.gText(15, 110, "The pet had fun!", greenColour, blackColour, 1, 1);
          delay(TIME_MESSAGE);
          showMessage(50);
          return return_menu();         
          break;
          
      case 1: //walk
          beep(NOTE_B5, 125);
          myScreen.clear(blackColour);
          tempOutside=checkOutside();
          if(tempOutside==0){
            initWalk();
            if(choice) drawBitmap(pet1_walk,64,64);
            else drawBitmap(pet2_walk,64,64);
            myScreen.gText(5, 10, "The pet is walking!", yellowColour, blackColour, 1, 1);
            while(petWalk());          
            if(winGame) {
              if(choice) drawBitmap(pet1_happy,64,64);
              else drawBitmap(pet2_happy1,64,64);
              myScreen.gText(15, 110, "The pet had fun!", greenColour, blackColour, 1, 1);
            }
            else {
              if(choice) drawBitmap(pet1_sad,64,64);
              else drawBitmap(pet2_sad1,64,64);
              myScreen.gText(15, 110, "The pet is sad!", redColour, blackColour, 1, 1);
            }
            delay(TIME_MESSAGE);
            digitalWrite(redLED,LOW);
            digitalWrite(greenLED,LOW);
            if(winGame) showMessage(80);
          }
          else if(tempOutside<0){
            myScreen.gText(15, 30, "It's too COLD!", blueColour, blackColour, 1, 1);
            myScreen.gText(15, 50, "The pet ", blueColour, blackColour, 1, 1);
            myScreen.gText(15, 60, "doesn't want", blueColour, blackColour, 1, 1);
            myScreen.gText(15, 70, "to go outside!", blueColour, blackColour, 1, 1);
            delay(TIME_MESSAGE);
          }else{
            myScreen.gText(15, 30, "It's too HOT!", redColour, blackColour, 1, 1);
            myScreen.gText(15, 50, "The pet ", redColour, blackColour, 1, 1);
            myScreen.gText(15, 60, "doesn't want", redColour, blackColour, 1, 1);
            myScreen.gText(15, 70, "to go outside!", redColour, blackColour, 1, 1);
            delay(TIME_MESSAGE);
          }
          return return_menu();  
          break;
          
      case 2: //sleep
          beep(NOTE_B5, 125);
          myScreen.clear(blackColour);
          if(!rested){
            if(choice) drawBitmap(pet1_sleep,64,64);
            else drawBitmap(pet2_sleep,64,64);
            sleep=0;
            myScreen.gText(5, 110, "The pet is asleep!", yellowColour, blackColour, 1, 1);
            while(petSleep());
            if(rested){
              if(choice) drawBitmap(pet1_happy,64,64);
              else drawBitmap(pet2_happy1,64,64);
              myScreen.gText(5, 110, "The pet is rested!", greenColour, blackColour, 1, 1);
            }
            else {
              if(choice) drawBitmap(pet1_sad,64,64);
              else drawBitmap(pet2_sad1,64,64);
              myScreen.gText(5, 110, "The pet is tired! ", redColour, blackColour, 1, 1);
            }
            delay(TIME_MESSAGE);
            if(rested) showMessage(200);
          }else{            
            myScreen.gText(20, 50, "The pet is", yellowColour, blackColour, 1, 1);
            myScreen.gText(20, 60, "already rested", yellowColour, blackColour, 1, 1);
            delay(TIME_MESSAGE);
          }
          return return_menu();  
          break;
          
      case 3: //eat
          beep(NOTE_B5, 125);
          myScreen.clear(blackColour);          
          initFood();
          if(choice) drawBitmap(pet1_food,64,64);
          else drawBitmap(pet2_food,64,64);
          myScreen.gText(5, 20, "The pet is eating!", yellowColour, blackColour, 1, 1);
          while(petEat());
          if(winGame) {
            if(choice) drawBitmap(pet1_happy,64,64);
            else drawBitmap(pet2_happy1,64,64);
            myScreen.gText(15, 110, "The pet is full!", greenColour, blackColour, 1, 1);
          }
          else {
            if(choice) drawBitmap(pet1_sad,64,64);
            else drawBitmap(pet2_sad1,64,64);
            myScreen.gText(5, 110, "The pet is starving!", redColour, blackColour, 1, 1);
          }
          delay(TIME_MESSAGE);          
          digitalWrite(redLED,LOW);
          digitalWrite(greenLED,LOW);
          if(winGame) showMessage(40);
          return return_menu();  
          break;

      case 4: //play
          beep(NOTE_B5, 125);
          myScreen.clear(blackColour);          
          initPlay();
          if(choice) drawBitmap(pet1_play,64,64);
          else drawBitmap(pet2_play,64,64);
          while(petPlay());
          if(winGame){
            if(choice) drawBitmap(pet1_happy,64,64);
            else drawBitmap(pet2_happy1,64,64);
            myScreen.gText(40, 110, "You WON!", greenColour, blackColour, 1, 1);
          }
          else {
            if(choice) drawBitmap(pet1_sad,64,64);
            else drawBitmap(pet2_sad1,64,64);
            myScreen.gText(40, 110, "You LOST!", redColour, blackColour, 1, 1);
          }
          delay(TIME_MESSAGE);
          digitalWrite(redLED,LOW);
          digitalWrite(greenLED,LOW);
          if(winGame) showMessage(100);
          return return_menu(); 
          break;
          
      case 5: //exit
          beep(NOTE_GS3, 125);  
          return return_menu();
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
    //read the interrupt (when the user press the buttonTwo)
    buttonTwoState=digitalRead(buttonTwo);
    // check if the state of the button is LOW(is pressed)
    if(buttonTwoState==LOW){
      //set the semaphore of the menu to true
      busyMenu=true;
      myScreen.clear(blackColour);
      //shows the menu
      while(menu_pet());
    }
  }
}
