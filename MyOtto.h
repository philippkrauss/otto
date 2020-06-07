#ifndef __MY_OTTO_H
#define __MY_OTTO_H

#include <Oscillator.h>
#include "US.h"
#include "LedMatrix.h"

#define EEPROM_TRIM false 
// Activate to take callibration data from internal memory
#define TRIM_RR 7
#define TRIM_RL 4
#define TRIM_YR  4
#define TRIM_YL -7

#define N_SERVOS 4

#define PIN_RR 5
#define PIN_RL 4
#define PIN_YR 3
#define PIN_YL 2

#define INTERVALTIME 10.0 

//-- First step: Configure the pins where the servos are attached
/*
         --------------- 
        |     O   O     |
        |---------------|
YR 3==> |               | <== YL 2
         --------------- 
            ||     ||
            ||     ||
RR 5==>   -----   ------  <== RL 4
         |-----   ------|
*/
class MyOtto {
    public:
    Oscillator servo[N_SERVOS];
    LedMatrix ledMatrix;
    US us;

    void attach();
    void resetAll();
    void resetServos();
    void resetLedMatrix();

    void showMouth(unsigned long mouth);

    float readDistance();
};

#endif // __MY_OTTO_H
