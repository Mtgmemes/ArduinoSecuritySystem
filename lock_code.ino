#include <LiquidCrystal.h>
#include <Keypad.h>

const byte ROWS = 4;  //four rows
const byte COLS = 4;  //four columns

const String password = "1234B"; //correct password
String current = "";             //entered password
bool isCorrect = false;          //determines whether or not the password is correct

int ledPin = 13;      // choose the pin for the LED
int inputPin = 8;     // choose the input pin (for PIR sensor)
int pirState = LOW;   // determining if there is motion or not. Starting assuming no motion
int val = 0;          // variable for reading the pin status
int stage = 0;        // the state of the fsm

char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

byte rowPins[ROWS] = { 39, 41, 43, 45 };  //connect to the row pinouts of the keypad
byte colPins[COLS] = { 47, 49, 51, 53 };  //connect to the column pinouts of the keypad

//Create an object of keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

unsigned long timer; //current time
unsigned long recordedTime; //when the countdown starts

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(inputPin, INPUT);

  Serial.begin(9600);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  lcd.clear();  // Clears the LCD screen
  lcd.setCursor(4,0); //Centers the LCD
  lcd.print("Stage 0");
  digitalWrite(ledPin, LOW);
}

void loop() {
  // // put your main code here, to run repeatedly:
  char key = keypad.getKey();

  //this loop deals with the key input

  if(key){ // if a key was inputted
    if(key == '*'){ // * is the key that checks the current password
      if(current.equals(password)){
        isCorrect = true;
      }
      current = ""; //reseting the password after each attempt
    }
    else{
      current = current + key; //adding key to the end of the current password attempt
      Serial.println(current);
    }
  }

  pirState = digitalRead(inputPin);
  //for seeing if there is motion

  if(stage == 0){
    if(isCorrect){ //if the password is entered, then the alarm arms
      stage = 1;
      isCorrect = false;
      lcd.clear();
      lcd.setCursor(4,0);
      lcd.print("Stage 1");
    }
  }
  else if(stage == 1){
    if(isCorrect){ //if correct password, return to stage 0
      stage = 0;
      isCorrect = false;
      lcd.clear();
      lcd.setCursor(4,0);
      lcd.print("Stage 0");
    }
    else if(pirState == HIGH){ //if motion is detected, go to stage 2
      stage = 2;
      isCorrect = false;
      lcd.clear();
      lcd.setCursor(4,0);
      lcd.print("Stage 2");
      recordedTime = millis(); //recording when the alarm tripped
    }
  }
  else if(stage == 2){
    timer = millis();
    if(isCorrect){ //if correct password, return to stage 0
      stage = 0;
      isCorrect = false;
      lcd.clear();
      lcd.setCursor(4,0);
      lcd.print("Stage 0");
    }
    else if(timer - recordedTime > 30000){ //goes to stage 3 after 30 seconds
      stage = 3;
      isCorrect = false;
      lcd.clear();
      lcd.setCursor(4,0);
      lcd.print("Stage 3");
      digitalWrite(ledPin, HIGH); //representing when the alarm fully triggers
    }
  }
  else if(stage == 3){
    if(isCorrect){ //if correct password, return to stage 0
      stage = 0;
      isCorrect = false;
      lcd.clear();
      lcd.setCursor(4,0);
      lcd.print("Stage 0");
      digitalWrite(ledPin, LOW); //reseting the alarm to off
    }
  }

}
