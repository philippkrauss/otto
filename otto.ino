#include "MyOtto.h"
#include "Otto_sounds.h"

MyOtto otto;


void setup() {
    otto.init();
    otto.sing(S_connection); //Otto wake up!
    otto.home();
}

void loop() {
    otto.walk(2,1000,FORWARD); //2 steps FORWARD
    otto.sing(S_OhOoh);
    otto.walk(2,1000,BACKWARD); //2 steps BACKSWARD
    otto.sing(S_OhOoh2);
    otto.home();
    delay(5000);
}