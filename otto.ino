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
  switch(otto.selectMode()) {
    case 0:
    default:
      danceSmoothCriminal();
      break;
  }
}

