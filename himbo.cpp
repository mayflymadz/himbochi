// Himbochi - An virtual 'pet' game where you take care of a cute little himbo.
// Author: Madison (mayflymadz)
#include <stdio.h>
#include <stdlib.h>


#include "himbo.h"
#include "bitmaps.h"


Himbo::Himbo() {
    gains = 10;
    hunger = 10;
    happiness = 10;

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