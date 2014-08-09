// Button Groups
int btnMatrix[4][2] = {
  {2, 3},
  {4, 5},
  {6, 7},
  {8, 9}
};

// Float switch that stops the pump when upper tank is filled
int floatSwitch = {10};

// Water pump to fill upper tank on reset
int pump = {11};

// Start button to activate valve
int startBtn = {11};
int startLed = {1};

// Valve
int valve = {12};

// Reset button for filling upper tank and reseting defaults
int resetBtn = {13};

//Counter for number of buttons written to high
int aBtnCounter = 0;
int bBtnCounter = 0;

//Saves the user button selections
int btnState[8];

int drainTime = 0; // set drain time to how long it takes to drain to zero
int fillTime = 0; // set fill time to how logn it take to fill upper tank


void setup(){
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 2; j++){
      pinMode(btnMatrix[i][j], INPUT);
      digitalWrite(btnMatrix[i][j], HIGH); //enable internal pullup; mat switches start in HIGH position; logic reversed
    }
  }
  pinMode(floatSwitch, INPUT);
  digitalWrite(floatSwitch, HIGH);  
  pinMode(startBtn, INPUT);
  digitalWrite(startBtn, HIGH);
  pinMode(startLed, OUTPUT);
  pinMode(resetBtn, INPUT);
  digitalWrite(resetBtn, HIGH);
  pinMode(pump, OUTPUT);
  pinMode(valve, OUTPUT);
}

void loop(){
  
  //Iterate over Button Groups and store the buttonstate
  for(int n = 0; n < 8; n++){
    for(int i = 0; i < 4; i++){
      for(int j = 0; j < 2; j++){
         btnState[n] = digitalRead(btnMatrix[i][j]);
      }
    }
      //digitalWrite button to LOW based on state of the button in the same row of the 
      //btnMatrix (ie btnState[0] = btnMatrix[0][0], btnState[1] = btnMatrix[0][1] etc).
      //increment aBtnCounter for every button written to LOW in the first column and increment bBtnCounter for every button
      //written to LOW for every button in second column.
    if(btnState[n] % 2 == 0 && btnState [n] == HIGH && btnState[n+1] == HIGH){
       btnState[n] = LOW;
       aBtnCounter = aBtnCounter++;
    }
    else
    if(btnState[n] % 2 != 0 && btnState[n] == HIGH  && btnState[n-1] == HIGH){
      btnState[n] = LOW;
      bBtnCounter = bBtnCounter++;
    }
  }

  //Start light is on when the aBtnCounter and bBtnCounter = 4. Meaning all choices were made and user can see
  //the results of their choices by pushing startBtn.
  //When startBtn is pushed upper tank will drain according to selections made by the user
  int count = aBtnCounter + bBtnCounter;
  if(count = 4){
    digitalWrite(startLed, HIGH);
    startBtn = digitalRead(startBtn);
    if(startBtn == LOW){
      digitalWrite(valve, HIGH);
      if(bBtnCounter == 4){
      delay(drainTime);
      }
      else if(bBtnCounter == 3){
      delay(drainTime * .87);
      }
      else if(bBtnCounter == 2){
      delay(drainTime * .74);
      }
      else if(bBtnCounter == 1){
      delay(drainTime * .61);
      }
      else if(bBtnCounter == 0){
      delay(drainTime * .50);
      }
      digitalWrite(valve, LOW);
      digitalWrite(startLed, HIGH);
    }
    
  }
  
  //After results displayed use the resetBtn to refill the tank and set everything back to default
   resetBtn = digitalRead(resetBtn);
   if(resetBtn == LOW){
     for( int n = 0; n < 8; n++){
       btnState[n] = HIGH;
       aBtnCounter = 0;
       bBtnCounter = 0;
     }
     for(int i = 0; i < 4; i++){
      for(int j = 0; j < 2; j++){
         digitalWrite(btnMatrix[i][j], HIGH);
      }
    }
    digitalWrite(pump, HIGH);
    delay(fillTime);
    digitalWrite(pump, LOW);
    floatSwitch = digitalRead(floatSwitch);
    if(floatSwitch == LOW){
      digitalWrite(pump, LOW);
    }
     
   }
   delay(250);
   resetBtn = HIGH;
  
  
}
