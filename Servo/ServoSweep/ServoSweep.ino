/*
Servo Sweep
*/
#include <Servo.h>

Servo myServo;
int posicion=0;

void setup() {
  myServo.attach(9);
}

void loop() {
  for(posicion=0;posicion<=180;posicion+=1) {
    myServo.write(posicion);
    delay(15);
  }
  for(posicion=180;posicion>=0;posicion-=1) {
    myServo.write(posicion);
    delay(15);
  }
    
}
