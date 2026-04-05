// Himbochi - An virtual 'pet' game where you take care of a cute little himbo.
// Author: Madison (mayflymadz)
#include <stdio.h>
#include <stdlib.h>


#include "himbo.h"
#include "bitmaps.h"

uint8_t showIdle() {
    return 0;
}

uint8_t showFeed() {
    return 0;
}

uint8_t showTrain() {
    return 0;
}

uint8_t showChill() {
    return 0;
}

Himbo::Himbo() {
    gains = 10;
    hunger = 10;
    happiness = 10;

    idleBitmap = epd_bitmap_himbo_idle;
}
