// Himbochi - An virtual 'pet' game where you take care of a cute little himbo.
// Is it weird to call a himbo a pet? Maybe. Is it unethical to turn men into pets? Probably.
// 
// Author: Madison (mayflymadz)
#include <stdint.h>


class Himbo {
    // Visible stats
    private:
        uint8_t gains;
        uint8_t hunger;
        uint8_t happiness;
        const unsigned char* idleBitmap;
        const unsigned char* eatBitmap;
        const unsigned char* trainBitmap;
        const unsigned char* chillBitmap;

    // Methods
    public:
        // Constructor
        Himbo();

        // Actions
        uint8_t eat();
        uint8_t train();
        uint8_t chill();

        // Passive stat decay, called based on decay rate
        uint8_t decay();

        const unsigned char* getIdleBitmap() {
            return idleBitmap;
        }
        const unsigned char* getEatBitmap() {
            return eatBitmap;
        }
        const unsigned char* getTrainBitmap() {
            return trainBitmap;
        }
        const unsigned char* getChillBitmap() {
            return chillBitmap;
        }
};
