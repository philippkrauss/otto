#ifndef MyOtto_h
#define MyOtto_h

#include <Oscillator.h>

#define PIN_YL 2
#define PIN_YR 3
#define PIN_RL 4
#define PIN_RR 5
#define PIN_Buzzer  13

//-- Constants
#define FORWARD     1
#define BACKWARD    -1
#define LEFT        1
#define RIGHT       -1
#define SMALL       5
#define MEDIUM      15
#define BIG         30

class MyOtto
{
    public:
        void init(int YL = 2, int YR = 3, int RL = 4, int RR = 5, int Buzzer = PIN_Buzzer);
        void home();
        void walk(float steps=4, int T=1000, int dir = FORWARD);
        void sing(int songName);

    private:
        Oscillator servo[4];
        int servo_pins[4];
        int servo_trim[4];
        int servo_position[4];

        int pinBuzzer;
        
        unsigned long final_time;
        unsigned long partial_time;
        float increment[4];

        bool isOttoResting;

        //-- Servo related methods
        void attachServos();
        void detachServos();
        void _moveServos(int time, int  servo_target[]);
        void oscillateServos(int A[4], int O[4], int T, double phase_diff[4], float cycle = 1);
        void _execute(int A[4], int O[4], int T, double phase_diff[4], float steps);

        //-- Sounds
        void _tone (float noteFrequency, long noteDuration, int silentDuration);
        void bendTones (float initFrequency, float finalFrequency, float prop, long noteDuration, int silentDuration);
};

#endif