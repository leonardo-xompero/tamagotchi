//function for return the previous menu
bool return_menu(){
  if(blackLight==1)myScreen.clear(blackColour);
  else myScreen.clear(whiteColour);
  drawBitmap(bmp);
  choiceX=0;
  busyMenu=false;
  return false;
}

void initPlay(){
  //drawBitmap(bmp);
  //myScreen.gText(5, 20, "Play with your pet!", blueColour, blackColour, 1, 1);
  i=0;
  j=BAR_LIMIT;
  //initialize the bar
  for(int x=0;x<j;x++) bar[x]='_';
  bar[0]='|';
  //set a random orienation for the game
  randOrientation= rand() % 4;
  //TODO : MESSAGE OF HOW TO PLAY AND INDICATION OF THE ORIENTATION
}

//show the message after the action, the points may vary from the action performed
void showMessage(int points){  
    char sPoints[10];
    sprintf(sPoints, "by %d", points); 
    myScreen.clear(blackColour);
    myScreen.gText(30, 50, "The pet life", blueColour, blackColour, 1, 1);
    myScreen.gText(30, 60, "is increased", blueColour, blackColour, 1, 1);
    myScreen.gText(30, 70, sPoints, blueColour, blackColour, 1, 1);
    delay(TIME_MESSAGE);
    //check the limit
    if( life_pet+points<999)
      life_pet+=points;
}

//the random variables decides the axys of the screen
bool play(){
    myScreen.setOrientation(randOrientation);
    myScreen.gText(30,50,"0",greenColour,blackColour,1,1);
    myScreen.gText(85,50,"10",greenColour,blackColour,1,1);
    myScreen.gText(30,60,bar,greenColour,blackColour,1,1);
    analogReadResolution(12);
    //foor the accelerometer, we need 12 bit, so we set it 
    int analogValue;
    if(randOrientation == 0 || randOrientation == 2){
      // CHECK X AXIS (red) 
      analogValue = analogRead(xpin); // read Y axis 
      if(analogValue >2048){ // check if tilting on x axis in positive direction
         if(i<j){
            bar[i]='|';
            i+=STEP;
         }
      } 
      else if(analogValue<2048){ // check if tilting on x axis in negative direction 
          if(i>0){
            bar[i]='_';
            i-=STEP;
          }
      } 
    }else{
      // CHECK Y AXIS (green) 
      analogValue = analogRead(ypin); // read Y axis 
      if(analogValue >2048){ // check if tilting on Y axis in positive direction 
          if(i<j){
            bar[i]='|';
            i+=STEP;
         }
      } 
      else if(analogValue<2048){ // check if tilting on Y axis in negative direction 
        if(i>0){
            bar[i]='_';
            i-=STEP;
          }
      } 
    }
    delay(10);
  //now we need to set the default value for msp432
  analogReadResolution(10);
  buttonTwoState=digitalRead(buttonTwo);
  if(buttonTwoState==LOW) {
    myScreen.setOrientation(0);
    return false;
  }
  else return true;
}

//function for the event "dance"
bool dance(){  
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

    // Wait for the specief duration before playing the next note.
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
        myScreen.gText(30, 10, "dance", greenColour, orangeColour, 1, 1);
        myScreen.gText(30, 30, "walk", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 50, "sleep", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 70, "eat", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 90, "play", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 110, "exit", greenColour, blackColour, 1, 1);
        break;
        
    case 1:
        myScreen.gText(30, 10, "dance", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 30, "walk", greenColour, orangeColour, 1, 1);
        myScreen.gText(30, 50, "sleep", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 70, "eat", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 90, "play", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 110, "exit", greenColour, blackColour, 1, 1);
        break;
        
    case 2:
        myScreen.gText(30, 10, "dance", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 30, "walk", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 50, "sleep", greenColour, orangeColour, 1, 1);
        myScreen.gText(30, 70, "eat", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 90, "play", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 110, "exit", greenColour, blackColour, 1, 1);
        break;
        
    case 3:
        myScreen.gText(30, 10, "dance", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 30, "walk", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 50, "sleep", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 70, "eat", greenColour, orangeColour, 1, 1);
        myScreen.gText(30, 90, "play", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 110, "exit", greenColour, blackColour, 1, 1);
        break;      

    case 4:
        myScreen.gText(30, 10, "dance", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 30, "walk", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 50, "sleep", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 70, "eat", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 90, "play", greenColour, orangeColour, 1, 1);
        myScreen.gText(30, 110, "exit", greenColour, blackColour, 1, 1);
        break; 

    case 5:
        myScreen.gText(30, 10, "dance", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 30, "walk", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 50, "sleep", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 70, "eat", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 90, "play", greenColour, blackColour, 1, 1);
        myScreen.gText(30, 110, "exit", greenColour, orangeColour, 1, 1);
        break; 
  }
  
  buttonOneState = digitalRead(buttonOne);
    
  if(buttonOneState==LOW){
    switch (choiceX)
    {
      case 0:
          myScreen.clear(blackColour);
          drawBitmap(bmp);
          myScreen.gText(5, 20, "The pet is dancing!", blueColour, blackColour, 1, 1);
          while(dance());
          myScreen.gText(15, 110, "The pet had fun!", blueColour, blackColour, 1, 1);
          delay(TIME_MESSAGE);
          showMessage(50);
          return return_menu();         
          break;
      case 1:
          return return_menu();  
          break;

      case 4:
          myScreen.clear(blackColour);          
          initPlay();
          while(play());
          myScreen.gText(15, 110, "The pet had fun!", blueColour, blackColour, 1, 1);
          delay(TIME_MESSAGE);
          showMessage(50);
          return return_menu(); 
          break;
          
      case 5:
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
