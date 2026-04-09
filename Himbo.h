// Himbochi - A virtual 'pet' game where you take care of a cute little himbo.
// Is it weird to call a himbo a pet? Maybe. Is it unethical to turn men into pets? Probably.
// 
// Author: Madison (mayflymadz)
#include <stdint.h>
#include <avr/pgmspace.h>

// A mood chart for the himbo, which will affect his dialogue
enum Mood {
    HAPPY,
    CONTENT,
    SAD
};

enum Action {
    EAT,
    TRAIN,
    CHILL
};

// This is for himbochi.ino to use, just wasn't sure where to put tit
enum State {
    IDLE,
    CHILLING,
    EATING,
    TRAINING,
    SPLASH
};

class Himbo {
    // Visible stats
    private:
        uint8_t gains;
        uint8_t hunger;
        uint8_t happiness;
        const uint8_t statMax = 12;
        const unsigned char* idleBitmap;
        const unsigned char* eatBitmap;
        const unsigned char* trainBitmap;
        const unsigned char* chillBitmap;
        Mood mood;

    // Methods
    public:
        // Constructor
        Himbo();

        // Actions
        uint8_t eat();
        uint8_t train();
        uint8_t chill();
        uint8_t doActivity(Action actionType);
        const char* getDialogue();

        // Passive stat decay, called based on decay rate
        void decay();

        // Retrieve data
        uint8_t getGains() { return gains; };
        uint8_t getHunger() { return hunger; };
        uint8_t getHappiness() { return happiness; };
        Mood getMood() { return mood; };

        const unsigned char* getIdleBitmap() { return idleBitmap; }
        const unsigned char* getEatBitmap() { return eatBitmap; }
        const unsigned char* getTrainBitmap() { return trainBitmap; }
        const unsigned char* getChillBitmap() { return chillBitmap; }

        const uint8_t Himbo::getStatMax() { return statMax; }
};



