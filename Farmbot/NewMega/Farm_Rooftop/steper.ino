
void homie() {
  //  digitalWrite(DirL, LOW);
  //  digitalRead(SwitchL);
  //  do {
  //    digitalWrite(PulseL, HIGH);
  //    delayMicroseconds(2000); //Set Value
  //    digitalWrite(PulseL, LOW);
  //    delayMicroseconds(2000); //Set Value
  //  } while (digitalRead(SwitchL) == HIGH);
  digitalWrite(DirZ, HIGH);
  digitalRead(SwitchZ);
  do {
    digitalWrite(PulseZ, HIGH);
    delayMicroseconds(speedDelay); //Set Value
    digitalWrite(PulseZ, LOW);
    delayMicroseconds(speedDelay); //Set Value
  } while (digitalRead(SwitchZ) == HIGH);
  digitalWrite(DirX, HIGH);
  digitalRead(SwitchX);
  do {
    digitalWrite(PulseX, HIGH);
    delayMicroseconds(speedDelay); //Set Value
    digitalWrite(PulseX, LOW);
    delayMicroseconds(speedDelay); //Set Value
  } while (digitalRead(SwitchX) == HIGH);
  digitalWrite(DirY, HIGH);
  digitalRead(SwitchY);
  do {
    digitalWrite(PulseY, HIGH);
    delayMicroseconds(speedDelay); //Set Value
    digitalWrite(PulseY, LOW);
    delayMicroseconds(speedDelay); //Set Value
  } while (digitalRead(SwitchY) == HIGH);
}


void gotoX(long eX) {
  //  Serial.print("Xe--> "); Serial.println(eX);
  eX *= nMM;

  if (eX < 0) {
    digitalWrite(DirX, HIGH);
    eX *= -1;
  } else
  {
    digitalWrite(DirX, LOW);
  }
  for (long i = 0; i <= eX; i++) {
    digitalWrite(PulseX, HIGH);
    delayMicroseconds(speedDelay); //Set Value
    digitalWrite(PulseX, LOW);
    delayMicroseconds(speedDelay); //Set Value
  }
}

void gotoY(long Ye) {
  // Serial.print("Y --> "); Serial.println(Ye);
  Ye *= nMM;

  if (Ye < 0) {
    digitalWrite(DirY, HIGH);
    Ye *= -1;
  } else
  {
    digitalWrite(DirY, LOW);
  }
  for (long i = 0; i <= Ye; i++) {
    digitalWrite(PulseY, HIGH);
    delayMicroseconds(speedDelay); //Set Value
    digitalWrite(PulseY, LOW);
    delayMicroseconds(speedDelay); //Set Value
  }
}

void gotoZ(long Ze) {
  // Serial.print("Z --> "); Serial.println(Ze);
  Ze *= nMM;

  if (Ze < 0) {
    digitalWrite(DirZ, HIGH);
    Ze *= -1;
  } else
  {
    digitalWrite(DirZ, LOW);
  }
  for (long i = 0; i <= Ze; i++) {
    digitalWrite(PulseZ, HIGH);
    delayMicroseconds(speedDelay); //Set Value
    digitalWrite(PulseZ, LOW);
    delayMicroseconds(speedDelay); //Set Value
  }
}

void gotoL(long Le) {
  // Serial.print("Z --> "); Serial.println(Ze);
  Le *= nMM;

  if (Le < 0) {
    digitalWrite(DirL, LOW);
    Le *= -1;
  } else
  {
    digitalWrite(DirL, HIGH);
  }
  for (long i = 0; i <= Le; i++) {
    //previousMicros = currentMicros;
    digitalWrite(PulseL, HIGH);
    delayMicroseconds(2000); //Set Value
    digitalWrite(PulseL, LOW);
    delayMicroseconds(2000); //Set Value
  }
}


void homeL() {
  digitalWrite(DirL, LOW);
  digitalRead(SwitchL);
  do {
    digitalWrite(PulseL, HIGH);
    delayMicroseconds(2000);
    digitalWrite(PulseL, LOW);
    delayMicroseconds(2000);
  } while (digitalRead(SwitchL) == HIGH);
}

void homeY() {
  digitalWrite(DirY, HIGH);
  digitalRead(SwitchY);
  do {
    digitalWrite(PulseY, HIGH);
    delayMicroseconds(speedDelay); //Set Value
    digitalWrite(PulseY, LOW);
    delayMicroseconds(speedDelay); //Set Value
  } while (digitalRead(SwitchY) == HIGH);

}

void homeZ() {
  digitalWrite(DirZ, HIGH);
  digitalRead(SwitchZ);
  do {
    digitalWrite(PulseZ, HIGH);
    delayMicroseconds(speedDelay); //Set Value
    digitalWrite(PulseZ, LOW);
    delayMicroseconds(speedDelay); //Set Value
  } while (digitalRead(SwitchZ) == HIGH);
}

void servobuka() {
  Servo1.write(45);
  Servo2.write(40);
  delay(1000);
}
void servotutup() {
  Servo1.write(94);
  Servo2.write(10);
  delay(1000);
}
void servobukatitik() {
  Servo1.write(70);
  Servo2.write(30);
  delay(1000);
}
