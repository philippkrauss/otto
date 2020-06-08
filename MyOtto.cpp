#include "MyOtto.h"

#include "Arduino.h"
#include "Otto_mouths.h"

unsigned long* getNumberMouths();
int getNextNumber(int current, int max);

void MyOtto::attach() {
    servo[0].attach(PIN_RR);
    servo[1].attach(PIN_RL);
    servo[2].attach(PIN_YR);
    servo[3].attach(PIN_YL);

    us.init(9, 8);
}

void MyOtto::resetServos() {
    for(int i=0;i<4;i++) servo[i].SetPosition(90);
}

void MyOtto::resetAll() {
    resetServos();
    resetLedMatrix();
}

void MyOtto::resetLedMatrix() {
    ledMatrix.clearMatrix();
}

void MyOtto::showMouth(unsigned long mouth) {
    ledMatrix.writeFull(mouth);
}

float MyOtto::readDistance() {
    return us.read();
}

#define MAX_MODES 10
#define MODE_CYCLE_TIME 1000
#define BLINK_TIME 500
#define NUMBER_OF_BLINKS 3
int MyOtto::selectMode() {
    int selectedMode = 0;
    unsigned long* numbers = getNumberMouths();
    showMouth(numbers[0]);

    float distance = 100;
    unsigned long time = 0;
    int time_difference = 100;
    while(distance > 20)
    {
        distance = readDistance();
        time += time_difference;
        delay(time_difference);
        if (time > MODE_CYCLE_TIME) {
            time = 0;
            selectedMode = getNextNumber(selectedMode, MAX_MODES);
            showMouth(numbers[selectedMode]);
        }
    }
    for (int i = 0; i < NUMBER_OF_BLINKS; i++) {
        resetLedMatrix();
        delay(BLINK_TIME);
        showMouth(numbers[selectedMode]);
        delay(BLINK_TIME);
    }
    resetLedMatrix();
    return selectedMode;
}

unsigned long* getNumberMouths() {
    static unsigned long numbers[10];
    numbers[0] = zero_code;
    numbers[1] = one_code;
    numbers[2] = two_code;
    numbers[3] = three_code;
    numbers[4] = four_code;
    numbers[5] = five_code;
    numbers[6] = six_code;
    numbers[7] = seven_code;
    numbers[8] = eight_code;
    numbers[9] = nine_code;
    return numbers;
}
int getNextNumber(int current, int max) {
    return ++current % max;
}