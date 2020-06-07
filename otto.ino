#include "MyOtto.h"
#include "Otto_mouths.h"

#include "SmoothCriminal.h"


MyOtto otto;

void setup()
{
  Serial.begin(9600);
  Serial.println("go");
  otto.attach();
  otto.resetAll();
}



void loop()
{
  otto.resetServos();
  otto.showMouth(tongueOut_code);
  
  float distance = 100;
  while(distance > 20)
  {
    Serial.println(distance);
    distance = otto.readDistance();
    delay(100);
  }
  
  Serial.println("waiting");
  
  danceSmoothCriminal();
}

