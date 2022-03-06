#include <arduino-timer.h>
#include <LiquidCrystal.h>

#define lightIntensityPin A0

#define redBtnPin 4
#define greenBtnPin 7
#define blueBtnPin 2

//#define colorResetBtnPin 1

#define redLightPin 9
#define greenLightPin 10
#define blueLightPin 11

#define rs 13
#define en 6
#define d4 5
#define d5 8
#define d6 3
#define d7 12

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

auto timer = timer_create_default();

int lightIntensityValue = 0;

int redBtnValue = 0;
int greenBtnValue = 0;
int blueBtnValue = 0;

int redLightValue = 85;
int greenLightValue = 0;
int blueLightValue = 0;

void setup() {
  Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.print("Hello world!");
  
  pinMode(lightIntensityPin, INPUT);
  
  pinMode(redBtnPin, INPUT);
  pinMode(greenBtnPin, INPUT);
  pinMode(blueBtnPin, INPUT);
  
  pinMode(redLightPin, OUTPUT);
  pinMode(greenLightPin, OUTPUT);
  pinMode(blueLightPin, OUTPUT);
}

void loop() {
  timer.tick();
  
  lightIntensityValue = map(analogRead(lightIntensityPin), 0, 1000, 0, 3);

  if (lightIntensityValue > 0) {
    rgbButtons();
  }

  analogWrite(redLightPin, redLightValue * lightIntensityValue);
  analogWrite(greenLightPin, greenLightValue * lightIntensityValue);
  analogWrite(blueLightPin, blueLightValue * lightIntensityValue);

  timer.every(10, resetSecondLineLcd);
}

void rgbButtons() {
//  int tp = digitalRead(colorResetBtnPin);
//  Serial.println(tp);
//  
//  if (tp == 1) {
//    redLightValue = 85;
//    greenLightValue = 0;
//    blueLightValue = 0;
//
//    firstLineLcdPrint("Reset done!");
//
//    return;
//  }
  
  redBtnValue = digitalRead(redBtnPin);
  greenBtnValue = digitalRead(greenBtnPin);
  blueBtnValue = digitalRead(blueBtnPin);
  
  if (redBtnValue == 1 && redLightValue < 255) {
    redLightValue++;
    secondLineLcdPrint("Red: " + redLightValue);
  }

  if (greenBtnValue == 1 && greenLightValue < 255) {
    greenLightValue++;
    secondLineLcdPrint("Green: " + greenLightValue);
  }

  if (blueBtnValue == 1 && blueLightValue < 255) {
    blueLightValue++;
    secondLineLcdPrint("Blue: " + blueLightValue);
  }
}

void firstLineLcdPrint(String msg) {
  lcd.setCursor(16,2);
  
  lcd.print(msg);
}

void secondLineLcdPrint(String msg) {
  lcd.setCursor(0,1);
  
  lcd.print(msg);

  timer.in(1000, resetSecondLineLcd);
}

bool resetSecondLineLcd(void *argument) {
  lcd.setCursor(0,1);
  
  lcd.print("I: ");
  lcd.print(lightIntensityValue);

  lcd.print(" | R: ");
  lcd.print(redLightValue);

  lcd.print(" | G: ");
  lcd.print(greenLightValue);

  lcd.print(" | B: ");
  lcd.println(blueLightValue);

  return false;
}