#include <Servo.h>
Servo Servo1;
Servo Servo2;

String Data;

void setup() {
  Servo1.attach(A8);
  Servo2.attach(A9);
  // servobukatitik();
  // servobuka();
    servotutup();
}

void loop() {

  if (Serial.available()) {
    Data = Serial.readStringUntil('\n');
  }

  if (Data == "a") {
    servotutup();
  } else if (Data == "b") {
    servobuka();
  } else if (Data == "c") {
    servobukatitik();
  }
}
void servobuka() {
  Servo1.write(45);
  Servo2.write(40);
}
void servotutup() {
  Servo1.write(94);
  Servo2.write(0);
}
void servobukatitik() {
  Servo1.write(70);
  Servo2.write(30);
}
