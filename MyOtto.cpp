#include "MyOtto.h"

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