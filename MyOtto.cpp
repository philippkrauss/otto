#include "Arduino.h"
#include "MyOtto.h"
#include "Otto_sounds.h"

#include "Oscillator.h"

//High level interface methods

void MyOtto::init(int YL, int YR, int RL, int RR, int Buzzer) {
    servo_pins[0] = YL;
    servo_pins[1] = YR;
    servo_pins[2] = RL;
    servo_pins[3] = RR;

    attachServos();
    isOttoResting = false;
  
    for (int i = 0; i < 4; i++) servo_position[i] = 90;

    pinBuzzer = Buzzer;
    pinMode(Buzzer,OUTPUT);
}

void MyOtto::home(){
    if (isOttoResting == false) {
        int homes[4]={90, 90, 90, 90}; //All the servos at rest position
        _moveServos(500,homes);   //Move the servos in half a second
        detachServos();
        isOttoResting = true;
    }
}

void MyOtto::walk(float steps, int T, int dir){

  //-- Oscillator parameters for walking
  //-- Hip sevos are in phase
  //-- Feet servos are in phase
  //-- Hip and feet are 90 degrees out of phase
  //--      -90 : Walk forward
  //--       90 : Walk backward
  //-- Feet servos also have the same offset (for tiptoe a little bit)
  int A[4]= {30, 30, 20, 20};
  int O[4] = {0, 0, 4, -4};
  double phase_diff[4] = {0, 0, DEG2RAD(dir * -90), DEG2RAD(dir * -90)};

  //-- Let's oscillate the servos!
  _execute(A, O, T, phase_diff, steps);  
}

void MyOtto::sing(int songName){
  switch(songName){

    case S_connection:
      _tone(note_E5,50,30);
      _tone(note_E6,55,25);
      _tone(note_A6,60,10);
    break;

    case S_disconnection:
      _tone(note_E5,50,30);
      _tone(note_A6,55,25);
      _tone(note_E6,50,10);
    break;

    case S_buttonPushed:
      bendTones (note_E6, note_G6, 1.03, 20, 2);
      delay(30);
      bendTones (note_E6, note_D7, 1.04, 10, 2);
    break;

    case S_mode1:
      bendTones (note_E6, note_A6, 1.02, 30, 10);  //1318.51 to 1760
    break;

    case S_mode2:
      bendTones (note_G6, note_D7, 1.03, 30, 10);  //1567.98 to 2349.32
    break;

    case S_mode3:
      _tone(note_E6,50,100); //D6
      _tone(note_G6,50,80);  //E6
      _tone(note_D7,300,0);  //G6
    break;

    case S_surprise:
      bendTones(800, 2150, 1.02, 10, 1);
      bendTones(2149, 800, 1.03, 7, 1);
    break;

    case S_OhOoh:
      bendTones(880, 2000, 1.04, 8, 3); //A5 = 880
      delay(200);

      for (int i=880; i<2000; i=i*1.04) {
           _tone(note_B5,5,10);
      }
    break;

    case S_OhOoh2:
      bendTones(1880, 3000, 1.03, 8, 3);
      delay(200);

      for (int i=1880; i<3000; i=i*1.03) {
          _tone(note_C6,10,10);
      }
    break;

    case S_cuddly:
      bendTones(700, 900, 1.03, 16, 4);
      bendTones(899, 650, 1.01, 18, 7);
    break;

    case S_sleeping:
      bendTones(100, 500, 1.04, 10, 10);
      delay(500);
      bendTones(400, 100, 1.04, 10, 1);
    break;

    case S_happy:
      bendTones(1500, 2500, 1.05, 20, 8);
      bendTones(2499, 1500, 1.05, 25, 8);
    break;

    case S_superHappy:
      bendTones(2000, 6000, 1.05, 8, 3);
      delay(50);
      bendTones(5999, 2000, 1.05, 13, 2);
    break;

    case S_happy_short:
      bendTones(1500, 2000, 1.05, 15, 8);
      delay(100);
      bendTones(1900, 2500, 1.05, 10, 8);
    break;

    case S_sad:
      bendTones(880, 669, 1.02, 20, 200);
    break;

    case S_confused:
      bendTones(1000, 1700, 1.03, 8, 2); 
      bendTones(1699, 500, 1.04, 8, 3);
      bendTones(1000, 1700, 1.05, 9, 10);
    break;

    case S_fart1:
      bendTones(1600, 3000, 1.02, 2, 15);
    break;

    case S_fart2:
      bendTones(2000, 6000, 1.02, 2, 20);
    break;

    case S_fart3:
      bendTones(1600, 4000, 1.02, 2, 20);
      bendTones(4000, 3000, 1.02, 2, 20);
    break;

  }
}

//Low level leg movement methods

void MyOtto::attachServos(){
    servo[0].attach(servo_pins[0]);
    servo[1].attach(servo_pins[1]);
    servo[2].attach(servo_pins[2]);
    servo[3].attach(servo_pins[3]);
}

void MyOtto::detachServos(){
    servo[0].detach();
    servo[1].detach();
    servo[2].detach();
    servo[3].detach();
}

void MyOtto::_moveServos(int time, int  servo_target[]) {
    attachServos();
    if (isOttoResting == true) {
        isOttoResting = false;
    }

    if (time > 10) {
        for (int i = 0; i < 4; i++) increment[i] = ((servo_target[i]) - servo_position[i]) / (time / 10.0);
        final_time = millis() + time;

        for (int iteration = 1; millis() < final_time; iteration++) {
            partial_time = millis() + 10;
            for (int i = 0; i < 4; i++) servo[i].SetPosition(servo_position[i] + (iteration * increment[i]));
            while (millis() < partial_time); //pause
        }
    } else {
        for (int i = 0; i < 4; i++) servo[i].SetPosition(servo_target[i]);
    }
    for (int i = 0; i < 4; i++) servo_position[i] = servo_target[i];
}

void MyOtto::_execute(int A[4], int O[4], int T, double phase_diff[4], float steps = 1.0){
    attachServos();
    isOttoResting = false;

    int cycles= (int)steps;    

    //-- Execute complete cycles
    if (cycles >= 1) {
        for(int i = 0; i < cycles; i++)  {
            oscillateServos(A, O, T, phase_diff);
        }
    }
    //-- Execute the final not complete cycle    
    oscillateServos(A,O, T, phase_diff,(float)steps-cycles);
}

void MyOtto::oscillateServos(int A[4], int O[4], int T, double phase_diff[4], float cycle) {
    for (int i = 0; i < 4; i++) {
        servo[i].SetO(O[i]);
        servo[i].SetA(A[i]);
        servo[i].SetT(T);
        servo[i].SetPh(phase_diff[i]);
    }
    double ref = millis();
    for (double x = ref; x <= T * cycle + ref; x = millis()) {
        for (int i = 0; i < 4; i++) {
            servo[i].refresh();
        }
    }
}

// Low level sound methods

void MyOtto::_tone (float noteFrequency, long noteDuration, int silentDuration){
    if (silentDuration==0) {
        silentDuration=1;
    }
    tone(pinBuzzer, noteFrequency, noteDuration);
    delay(noteDuration);
    delay(silentDuration);
}

void MyOtto::bendTones (float initFrequency, float finalFrequency, float prop, long noteDuration, int silentDuration) {
    //Examples:
    //  bendTones (880, 2093, 1.02, 18, 1);
    //  bendTones (note_A5, note_C7, 1.02, 18, 0);

    if (silentDuration == 0) {
        silentDuration = 1;
    }

    if (initFrequency < finalFrequency) {
        for (int i = initFrequency; i < finalFrequency; i = i * prop) {
            _tone(i, noteDuration, silentDuration);
        }
    } else {
        for (int i = initFrequency; i > finalFrequency; i = i / prop) {
            _tone(i, noteDuration, silentDuration);
        }
    }
}
