#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "bitmaps.h"
#include "himbo.h"


const uint8_t CHARACTER_ANCHOR_X = 48;
const uint8_t CHARACTER_ANCHOR_Y = 16;
const uint8_t BUTTON_1_X = 0;
const uint8_t BUTTON_1_Y = 52;
const uint8_t BUTTON_2_X = 50;
const uint8_t BUTTON_2_Y = 52;
const uint8_t BUTTON_3_X = 90;
const uint8_t BUTTON_3_Y = 52;
const uint8_t ANIMATION_TITLE_X = 0;
const uint8_t ANIMATION_TITLE_Y = 52;

// Button values
const int buttonPin1 = 2;
const int buttonPin2 = 4;
const int buttonPin3 = 6;

int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;

Adafruit_SSD1306 display(128, 64, &Wire);
Himbo himbo = Himbo();
bool isIdle = true;
bool isTraining = false;
bool isEating = false;
bool isChilling = false;

void idle() {
    display.clearDisplay();
    display.drawBitmap(CHARACTER_ANCHOR_X, CHARACTER_ANCHOR_Y, himbo.getIdleBitmap(), HIMBO_IDLE_FRAME_WIDTH, HIMBO_IDLE_FRAME_HEIGHT, SSD1306_WHITE);

    // Button 1
    display.setCursor(BUTTON_1_X, BUTTON_1_Y);
    display.println(">Train");
    pinMode(buttonPin1, INPUT);
    buttonState1 = digitalRead(buttonPin1);
    if (buttonState1 == HIGH) {
      isIdle = false;
      isTraining = true;
    }

      // Button 2
    display.setCursor(BUTTON_2_X, BUTTON_2_Y);
    display.println(">Eat");
    pinMode(buttonPin2, INPUT);
    buttonState2 = digitalRead(buttonPin2);
    if (buttonState2 == HIGH) {
      isIdle = false;
      isEating = true;
    }
    // Button 3
    display.setCursor(BUTTON_3_X, BUTTON_3_Y);
    display.println(">Chill");
    pinMode(buttonPin3, INPUT);
    buttonState3 = digitalRead(buttonPin3);
    if (buttonState3 == HIGH) {
      isIdle = false;
      isChilling = true;
    }
}

void train() {
  display.clearDisplay();
  display.setCursor(ANIMATION_TITLE_X, ANIMATION_TITLE_Y);
  display.println("Lifting Weights...");
  //himbo.train();
  delay(2000);
  isTraining = false;
  isIdle = true;
}

void eat() {
  display.clearDisplay();
  display.setCursor(ANIMATION_TITLE_X, ANIMATION_TITLE_Y);
  display.println("Getting some protein...");
  //himbo.feed();
  delay(2000);
  isEating = false;
  isIdle = true;
}

void chill() {
  display.clearDisplay();
  display.setCursor(ANIMATION_TITLE_X, ANIMATION_TITLE_Y);
  display.println("Chilling...");
  //himbo.chill();
  delay(2000);
  isChilling = false;
  isIdle = true;
}

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // This orientation is important for how my breadboard is set up. Subject to change depending on how you set up your board. 
  display.setRotation(2);
  display.clearDisplay();

}

void loop() {
  
  display.setTextSize(.5);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  while (isIdle) {
    idle();
  }
  while (isTraining) {
    train();
  }
  while (isEating) {
    eat();
  }
  while (isChilling) {
    chill();
  }


  display.display();

}