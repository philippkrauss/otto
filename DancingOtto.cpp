#include "DancingOtto.h"
#include <Arduino.h>

//---------------------------------------------------------
//-- First step: Make sure the pins for servos are in the right position
/*
         --------------- 
        |     O   O     |
        |---------------|
YR 3==> |               | <== YL 2
         --------------- 
            ||     ||
RR 5==>   -----   ------  <== RL 4
         |-----   ------|
         
*/
#define PIN_YL 2 //servo[2]
#define PIN_YR 3 //servo[3]
#define PIN_RL 4 //servo[4]
#define PIN_RR 5 //servo[5]

void DancingOtto::setup()
{
    //Set the servo pins
    Otto.init(PIN_YL, PIN_YR, PIN_RL, PIN_RR, false);
    Otto.sing(S_connection); //Otto wake up!
    Otto.home();
    delay(50);
}

void DancingOtto::dance()
{
    //OBSTACLE MODE ON!!!!
    obstacleMode();
    Otto.sing(S_surprise);
    Otto.walk(2, 1000, 1); //2 steps FORWARD
    Otto.sing(S_OhOoh);
    Otto.walk(2, 1000, -1); //2 steps BACKSWARD
    Otto.sing(S_OhOoh2);
    Otto.playGesture(OttoFretful);
    Otto.sing(S_cuddly);
    Otto.home();
    Otto.playGesture(OttoSleeping);
    Otto.sing(S_sleeping);
    delay(1000);
    Otto.sing(S_happy);
    Otto.playGesture(OttoHappy);
    Otto.turn(2, 1000, 1); //2 steps turning RIGHT
    Otto.sing(S_happy_short);
    delay(50);
    Otto.playGesture(OttoSuperHappy);
    Otto.sing(S_superHappy);
    Otto.turn(2, 1000, -1); //2 steps turning RIGHT
    Otto.playGesture(OttoSad);
    Otto.sing(S_sad);
    delay(50);
    Otto.moonwalker(3, 1000, 25, 1);
    Otto.playGesture(OttoConfused);
    Otto.sing(S_confused);
    Otto.home();
    Otto.bend(1, 2000, 1);
    Otto.playGesture(OttoFart);
    Otto.sing(S_fart1);
    Otto.sing(S_fart2);
    Otto.sing(S_fart3);
    Otto.home();
    Otto.ascendingTurn(1, 2000, 22);
    Otto.playGesture(OttoVictory);
    Otto.home();
    Otto.updown(1, 2000, 22);
    Otto.playGesture(OttoMagic);
    Otto.home();
    Otto.playGesture(OttoFail);
    Otto.sing(S_disconnection);
}

void DancingOtto::obstacleMode()
{
    distance = Otto.getDistance();
    if (distance < 15)
    {
        Otto.sing(S_surprise);
        Otto.walk(2, 1300, -1);
        Otto.turn(3, 1000, -1);
        delay(50);
    }
    else
    {
        Otto.walk(2, 1000, 1);
    }
}