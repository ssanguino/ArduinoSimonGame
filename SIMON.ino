/*
*** BUTTONS AND LEDS PIN DEFINITION ********************
*/
const int BUTTONRED = 7;
const int BUTTONBLUE = 6;
const int BUTTONGREEN = 5;
const int LEDRED =  13;
const int LEDBLUE =  12;
const int LEDGREEN = 11;

/*
*** SPEAKER DEFINITION *********************************
*/
const int SPEAKER = 4;

/*
*** NOTES DEFINITION ***********************************
*/
const unsigned int C6 = 1047;
const unsigned int Ab5 = 831;
const unsigned int Bb5 = 932;
const unsigned int G5 = 784;
const unsigned int F5 = 698;
const unsigned int E5 = 659;
const unsigned int Eb5 = 622;
const unsigned int D5 = 587;
const unsigned int Db5 = 554;
const unsigned int C5 = 523;
const unsigned int B4 = 494;
const unsigned int Bb4 = 466;
const unsigned int nA4 = 440;
const unsigned int Ab4 = 415;
const unsigned int G4 = 392;
const unsigned int Gb4 = 370;
const unsigned int F4 = 349;
const unsigned int E4 = 330;
const unsigned int Eb4 = 311;
const unsigned int D4 = 294;
const unsigned int Db4 = 277;
const unsigned int C4 = 262;
const unsigned int B3 = 247;
const unsigned int Bb3 = 233;
const unsigned int nA3 = 220;
const unsigned int G3 = 196;
const unsigned int Gb3 = 185;
const unsigned int F3 = 175;
const unsigned int E3 = 165;

/*
*** VARIABLES *****************************************
*/
boolean displayed = false;
int simonArray[15] = {0};
int answerArray[15] = {0};
int i = 0;
int iterator = 0;
int newColor = 3;
boolean isCorrect = false;
boolean isReady = true;
byte androidInput;
int turnChecker = 0;
int difficultyLevel = 5;
int difficultyVelocity = 0;

void setup() {
  // Initialize the LEDS and SPEAKER as output pins:
  pinMode(LEDRED, OUTPUT); 
  pinMode(LEDBLUE, OUTPUT);      
  pinMode(LEDGREEN, OUTPUT);  
  pinMode(SPEAKER, OUTPUT);
  // Initialize the BUTTONS as input pins:
  pinMode(BUTTONRED, INPUT);     
  pinMode(BUTTONBLUE, INPUT);
  pinMode(BUTTONGREEN, INPUT);
  // Initialize the starting conditions of the game
  startingConditions();
}

void loop(){
  
  if (isReady) {
    displayReady();
  }
  
  turnChecker = checkButtons(); // Wait for a button to be pressed to start the game.
  if (turnChecker == 1) {
    resetGame();  
  } else {
    // Not reset game, a difficulty was chosen or the turn was continued
    if (difficultyVelocity == 0) {
      difficultyLevel = turnChecker;
      adjustDifficulty(difficultyLevel);
    }  
  
    if (!displayed) {
      displayPattern();
    }
    // Main game loop:
    for (i = 0; i < newColor; i++) {
      answerArray[i] = checkButtons();
      if (answerArray[i] == 1) {
        resetGame();
        break;
      }
      isCorrect = compareArrays(i+1);
      if (!isCorrect) {
        displayLose();
        delay(1200);
        break;
      }
    }
    if (isCorrect) {
      delay(400);
      if (newColor == difficultyLevel) {
        VictoryFanfare();
        delay(1200);
        resetGame();
      } else {
        correctAnswer();
        simonArray[newColor] = random (11, 14);
        newColor++;
        displayed = false;
      }
    }
  }
}

void adjustDifficulty(int difLevel) {
  switch (difLevel) {
    case LEDRED:
      difficultyLevel = 5;
      difficultyVelocity = 750;
      break;
    case LEDBLUE:
      difficultyLevel = 10;
      difficultyVelocity = 500;
      break;
    case LEDGREEN:
      difficultyLevel = 15;
      difficultyVelocity = 200;
      break;
    default:
      break;
  }
}

void correctAnswer() {
  for (i = 0; i < 2; i++) {    
    digitalWrite(LEDGREEN, HIGH);
    tone(SPEAKER, E5);
    delay(400);
    noTone(SPEAKER);
    digitalWrite(LEDGREEN, LOW);
    delay (400);
  }
}

void displayReady() {
  digitalWrite(LEDGREEN, HIGH);
  playReadySound();
  digitalWrite(LEDGREEN, LOW);
  isReady = false;
}

void playReadySound() {
  tone(SPEAKER, C5);
  delay(300);
  noTone(SPEAKER);
  delay(50);
  tone(SPEAKER, C4);
  delay(120);
  noTone(SPEAKER);
  delay(25);
  tone(SPEAKER, C4);
  delay(120);
  noTone(SPEAKER);
  delay(50);
  tone(SPEAKER,G5);
  delay(800);
  noTone(SPEAKER);
}

boolean compareArrays(int numberToCompare) {
  for (iterator = 0; iterator < numberToCompare; iterator++){
    if (answerArray[iterator] != simonArray[iterator]){
      return false; 
    }
  }
  return true;
}

void displayPattern(){
  for (i = 0; i < newColor; i++){
    digitalWrite(simonArray[i], HIGH);
    playColorSound(simonArray[i], difficultyVelocity);
    noTone(SPEAKER);
    digitalWrite(simonArray[i], LOW);
    delay(350 - difficultyLevel*15);
  }
  displayed = true;
}

void playColorSound(int LED, int nDelay) {
  if (LED == LEDRED) {
    tone(SPEAKER, C5);
  } 
  else if (LED == LEDBLUE) {
    tone(SPEAKER, Db5);
  } 
  else if (LED == LEDGREEN) {
    tone(SPEAKER, F4);
  }
  delay(nDelay);
}

void displayLose(){
  resetGame();
  for (i = 0; i < 4; i++) {    
    digitalWrite(LEDRED, HIGH);
    tone(SPEAKER, G3);
    delay(400);
    noTone(SPEAKER);
    digitalWrite(LEDRED, LOW);
    delay (400);
  }
}

void resetGame() {
  displayed = false;
  newColor = 3;
  difficultyVelocity = 0;
  startingConditions();
  isReady = true;
  isCorrect = false;
}

void startingConditions() {
  for (i = 0; i < newColor; i++) {
    simonArray[i] = random (11, 14);
  }
}

void VictoryFanfare()          
{
  digitalWrite(LEDGREEN, HIGH);
  tone(SPEAKER,C5);
  delay(166);
  digitalWrite(LEDGREEN, LOW);
  noTone(SPEAKER);
  delay(50);
  digitalWrite(LEDGREEN, HIGH);
  tone(SPEAKER,C5);
  delay(166);
  digitalWrite(LEDGREEN, LOW);
  noTone(SPEAKER);
  delay(50);
  digitalWrite(LEDGREEN, HIGH);
  tone(SPEAKER,C5);
  delay(166);
  digitalWrite(LEDGREEN, LOW);
  noTone(SPEAKER);
  delay(50);
  digitalWrite(LEDGREEN, HIGH);
  tone(SPEAKER,C5);
  delay(500);
  digitalWrite(LEDGREEN, LOW);
  digitalWrite(LEDBLUE, HIGH);
  tone(SPEAKER,Ab4);
  delay(500);
  digitalWrite(LEDBLUE, LOW);
  digitalWrite(LEDRED, HIGH);
  tone(SPEAKER,Bb4);
  delay(500);
  digitalWrite(LEDRED, LOW);
  digitalWrite(LEDGREEN, HIGH);
  tone(SPEAKER,C5);
  delay(166);
  digitalWrite(LEDGREEN, LOW);
  noTone(SPEAKER);
  delay(166);
  digitalWrite(LEDBLUE, HIGH);
  tone(SPEAKER,Bb4);
  delay(166);
  digitalWrite(LEDBLUE, LOW);
  digitalWrite(LEDGREEN, HIGH);
  tone(SPEAKER,C5);
  delay(1200);
  digitalWrite(LEDGREEN, LOW);
  noTone(SPEAKER);
}

int checkButtons(){
  Serial.begin(9200);
  while (true) {
    if (digitalRead(BUTTONRED) == HIGH) {
      return delayButtonPressed(BUTTONRED, LEDRED);
    } 
    else if (digitalRead(BUTTONBLUE) == HIGH) {
      return delayButtonPressed(BUTTONBLUE, LEDBLUE);
    }
    else if (digitalRead(BUTTONGREEN) == HIGH) {
      return delayButtonPressed(BUTTONGREEN, LEDGREEN);
    } else if (Serial.available() > 0) {
      androidInput = Serial.read();
      Serial.println(androidInput);
      Serial.end();
    }
    switch (androidInput) {
      case 7:
        androidInput = 0;
        return delayAndroidPressed(LEDRED);
      case 6:
        androidInput = 0;
        return delayAndroidPressed(LEDBLUE);
      case 5:
        androidInput = 0;
        return delayAndroidPressed(LEDGREEN);
      case 1:
        androidInput = 0;
        return 1;
      case 2:
        androidInput = 0;
        VictoryFanfare();
        return checkButtons();
      default:
        break;
    }
  }
}

int delayButtonPressed (int button, int led) {
  while (digitalRead(button) == HIGH) {
    if (displayed) {
      playColorSound(led, 0);
      digitalWrite(led, HIGH);
    }
    delay(1);
  }
  digitalWrite(led, LOW);
  noTone(SPEAKER);
  return led;
}

int delayAndroidPressed (int led) {
  if (displayed) {
    digitalWrite(led, HIGH);
    playColorSound(led, 600);
    digitalWrite(led, LOW);
    noTone(SPEAKER);
  }
  return led;
}

