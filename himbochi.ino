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
const uint8_t DIALOGUE_X = 0;
const uint8_t DIALOGUE_Y = 16;

// Variables we can use while we are in an action to track how much time has passed
unsigned long actionStartTime = 0;
const unsigned long ACTION_DURATION = 2000; // Duration of the action animations in milliseconds
bool actionStarted = false;

// Variables to show dialogue
const unsigned long DIALOGUE_DURATION = 4000; // Dialogue on screen for 4 seconds
bool isSpeaking = false;
const char* currentLine;

// Button values
const int buttonPin1 = 10;
const int buttonPin2 = 4;
const int buttonPin3 = 6;
const int buzzerPin = 2;

int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;

// Buzzer values
unsigned long toneStartTime = 0;
const unsigned long TONE_DURATION = 100; // short click sound
bool isPlayingTone = false;

Adafruit_SSD1306 display(128, 64, &Wire);
Himbo himbo = Himbo();

// TODO: change these to an enum so we can't hit weird states where we are idle and chilling or something (except speaking, that's a special condtion on top of idle)
State state = IDLE;

// Most important value: the timer
unsigned long lastDecayTime = 0;
unsigned long lastDialogueTime = 0;
const unsigned long decayRate = 60000; // Decay every 60 seconds (1 minute), we can adjust this throughout development as needed.
const unsigned long dialogueRate = 1000; // Dialogue every 10 seconds, also subject to change.
const unsigned long dialogueTime = 3000; // Dialogue lasts for 3 seconds

// Display stat bar function
// Draws a stat bar of 20x10, filled area scaled off of amount, statmax, and 20
void displayStatBar(uint8_t x, uint8_t y, uint8_t amount) {
    display.drawRect(x, y, 20, 10, SSD1306_WHITE);
    display.fillRect(x + 1, y + 1, ((amount * 20) / himbo.getStatMax()), 8, SSD1306_WHITE);
}

// Make a little tone on the buzzer
void playTone(uint16_t frequency) {
  tone(buzzerPin, frequency);
  toneStartTime = millis();
  isPlayingTone = true;
}

// This function will be continually called to check for the tone
void updateTone() {
  if (isPlayingTone && (millis() - toneStartTime >= TONE_DURATION)) {
    noTone(buzzerPin);
    isPlayingTone = false;
  }
}

void idle() {
    // This is the 'homescreen' of the himbo. It shows his current stats and lets you choose an action.
    display.clearDisplay();

    // play tone if we get prompted to
    updateTone();

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
      isPlayingTone = true;
      playTone(300);
      state = TRAINING;
    }

      // Button 2
    display.setCursor(BUTTON_2_X, BUTTON_2_Y);
    display.println(">Eat");
    buttonState2 = digitalRead(buttonPin2);
    if (buttonState2 == HIGH) {
      isPlayingTone = true;
      playTone(300);
      state = EATING;
    }
    // Button 3
    display.setCursor(BUTTON_3_X, BUTTON_3_Y);
    display.println(">Chill");
    buttonState3 = digitalRead(buttonPin3);
    if (buttonState3 == HIGH) {
      isPlayingTone = true;
      playTone(300); 
      state = CHILLING;
    }
}

void actionAnimation(Action actionType, char* message) {
  // This will play the animation for the action and update stats, we don't need eat, train and chill to be seperate methods

  // Since we leave idle immediately and enter this function, we need to update the tone now as well so it turns off when we want it to
  updateTone();

  if (!actionStarted) {
    actionStartTime = millis();
    actionStarted = true;
    himbo.doActivity(actionType);
  }

  display.clearDisplay();
  display.setCursor(ANIMATION_TITLE_X, ANIMATION_TITLE_Y);
  display.println(message);
  display.display();

  if (millis() - actionStartTime > ACTION_DURATION) {
    switch (actionType)
    {
    case CHILL:
      state = CHILLING;
      break;
    case TRAIN:
      state = TRAINING;
      break;
    case EAT:
      state = EATING;
      break;    
    default:
      break;
    }
    state = IDLE;
    actionStarted = false; // reset this flag so the other actions can use it!
  }
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

  // Check the current time for stat decay and dialogue

  // Stat decay
  unsigned long currentTime = millis();
  if (currentTime - lastDecayTime >= decayRate) {
    himbo.decay();
    lastDecayTime = currentTime;
  }

  // Dialogue
  if (currentTime - lastDialogueTime >= dialogueRate) {
    isSpeaking = true;
    lastDialogueTime = currentTime;
    currentLine = himbo.getDialogue();
  }
  if (currentTime - lastDialogueTime >= DIALOGUE_DURATION){
    isSpeaking = false;
  }
  if (isSpeaking) {
    display.setCursor(DIALOGUE_X, DIALOGUE_Y);
    display.println(currentLine);
  }

  // Check what state the screen should be in 
  if (state == IDLE) {
    idle();
  } else if (state == TRAINING) {
    actionAnimation(Action::TRAIN, "Lifting Weights!");
  } else if (state == EATING) {
    actionAnimation(Action::EAT, "Getting some protein!");
  } else if (state == CHILLING) {
    actionAnimation(Action::CHILL, "Chillin!");
  }

  display.display();

}