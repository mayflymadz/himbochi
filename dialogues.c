//Dialogues for the himbo to say periodically based on his mood.

#include <stdint.h>
#include <avr/pgmspace.h>

struct DialogueSet {
    const char* const* lines;
    uint8_t lineCount;
};