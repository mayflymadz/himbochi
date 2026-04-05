// Himbochi - A Tamagotchi-inspired virtual pet for people who want to take care of a cute little himbo.
// Author: Madison (mayflymadz)
// April 2026

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "bitmaps.c"
#include "Himbo.h"

// These will point where the buttons, character, and bars go. The character is in the middle of the scree, the buttons are on the bootom, and the bars are at the top
// I will probably simplify this later, but this is helping me visualize where everything is going for now.
// TODO: Calculate locations based on screen size and character size instead of hardcoding them. This will make it easier to change the screen size later if I want to.
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
const uint8_t GAINS_BAR_X = 0;
const uint8_t GAINS_BAR_Y = 0;
const uint8_t HUNGER_BAR_X = 50;
const uint8_t HUNGER_BAR_Y = 0;
const uint8_t HAPPINESS_BAR_X = 100;
const uint8_t HAPPINESS_BAR_Y = 0;

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

// Display stat bar function
void displayStatBar(uint8_t x, uint8_t y, uint8_t amount) {
    display.drawRect(x, y, 20, 10, SSD1306_WHITE);
    display.fillRect(x + 1, y + 1, amount, 8, SSD1306_WHITE);
}

void idle() {
    // This is the 'homescreen' of the himbo. It shows his current stats and lets you choose an action.
    display.clearDisplay();

    // Stat bars
    displayStatBar(GAINS_BAR_X, GAINS_BAR_Y, himbo.getGains());
    displayStatBar(HUNGER_BAR_X, HUNGER_BAR_Y, himbo.getHunger());
    displayStatBar(HAPPINESS_BAR_X, HAPPINESS_BAR_Y, himbo.getHappiness());

    // Character art/sprite
    display.drawBitmap(CHARACTER_ANCHOR_X, CHARACTER_ANCHOR_Y, himbo.getIdleBitmap(), HIMBO_IDLE_FRAME_WIDTH, HIMBO_IDLE_FRAME_HEIGHT, SSD1306_WHITE);

    // Button 1
    display.setCursor(BUTTON_1_X, BUTTON_1_Y);
    display.println(">Train");
    buttonState1 = digitalRead(buttonPin1);
    if (buttonState1 == HIGH) {
      isIdle = false;
      isTraining = true;
    }

      // Button 2
    display.setCursor(BUTTON_2_X, BUTTON_2_Y);
    display.println(">Eat");
    buttonState2 = digitalRead(buttonPin2);
    if (buttonState2 == HIGH) {
      isIdle = false;
      isEating = true;
    }
    // Button 3
    display.setCursor(BUTTON_3_X, BUTTON_3_Y);
    display.println(">Chill");
    buttonState3 = digitalRead(buttonPin3);
    if (buttonState3 == HIGH) {
      isIdle = false;
      isChilling = true;
    }
}

void train() {
  // This will play the training animation and update the himbo's stats accordingly. It will then return to the idle screen.
  // TODO: Make sprite for training animation
  display.clearDisplay();
  display.setCursor(ANIMATION_TITLE_X, ANIMATION_TITLE_Y);
  display.println("Lifting Weights...");
  display.display();

  himbo.train();
  delay(2000);
  isTraining = false;
  isIdle = true;
}

void eat() {
  // This will play the eating animation and update the himbo's stats accordingly. It will then return to the idle screen.
  // TODO: Make sprite for eating animation
  display.clearDisplay();
  display.setCursor(ANIMATION_TITLE_X, ANIMATION_TITLE_Y);
  display.println("Getting some protein...");
  display.display();

  himbo.eat();
  delay(2000);
  isEating = false;
  isIdle = true;
}

void chill() {
  // This will play the chilling animation and update the himbo's stats accordingly. It will then return to the idle screen.
  // TODO: Make sprite for chilling animation
  display.clearDisplay();
  display.setCursor(ANIMATION_TITLE_X, ANIMATION_TITLE_Y);
  display.println("Chilling...");
  display.display();

  himbo.chill();
  delay(2000);
  isChilling = false;
  isIdle = true;
}

void setup() {
  // Set up display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // setup buttons
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);

  // This orientation is important for how my breadboard is set up. Subject to change depending on how you set up your board. 
  display.setRotation(2);
  display.clearDisplay();

}

void loop() {
  
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  // Check what state the screen should be in 
  if (isIdle) {
    idle();
  } else if (isTraining) {
    train();
  } else if (isEating) {
    eat();
  } else if (isChilling) {
    chill();
  }

  display.display();

}