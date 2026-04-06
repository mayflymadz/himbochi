// Himbochi - An virtual 'pet' game where you take care of a cute little himbo.
// Author: Madison (mayflymadz)
#include <stdio.h>
#include <stdlib.h>


#include "Himbo.h"
#include "bitmaps.c"
#include "dialogues.c"

Himbo::Himbo() {
    gains = 1;
    hunger = 1;
    happiness = 1;
    mood = CONTENT;

    idleBitmap = epd_bitmap_himbo_idle;
}

uint8_t Himbo::eat() {
    hunger += 2;
    happiness += 1;
    return hunger;
}

uint8_t Himbo::train() {
    gains += 2;
    hunger -= 1;
    happiness -= 1;
    return gains;
}

uint8_t Himbo::chill() {
    happiness += 2;
    hunger -= 1;
    return happiness;
}

uint8_t Himbo::doActivity(Action actionType) {
    if (actionType == Action::TRAIN) { train(); }
    else if (actionType == Action::EAT) { eat(); }
    else if (actionType == Action::CHILL) { chill(); }
}

void Himbo::decay() {
    // This will be called periodically to decay the himbo's stats. It will also update his mood based on his stats.
    gains -= 1;
    hunger -= 1;
    happiness -= 1;

    if (happiness >= 5) {
        mood = HAPPY;
    } else if (happiness >= 2) {
        mood = CONTENT;
    } else {
        mood = SAD;
    }
}

const char* Himbo::getDialogue() {
    // This will return a dialogue based on the himbo's mood.
    // TODO: pull dialoge from program memory, have multiple dialogue options for each mood
    if (mood == HAPPY) {
        return "Poggers!";
    } else if (mood == CONTENT) {
        return "Do you think doors are sad when they can't open?";
    } else {
        return "I'm not feeling so good...";
    }
}