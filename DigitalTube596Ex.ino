#include <DigitalTube595.h>

int lastTime = 0;

DigitalTube595 disp(7, 6, 5, 4);
void setup(){
 Serial.begin(9600);
 disp.show("1.2.3.4.");
}

void loop(){
  if ((millis() - lastTime) > 1000) {    
    String s = String(millis());
    lastTime = millis();
    disp.show(s);
  }
  disp.update();
}
