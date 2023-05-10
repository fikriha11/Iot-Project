void SiramTanaman() {
  switch (Count) {
    case 0:
      homie();
      delay(500);
      siram(0);
      break;
    case 1 :
      Serial.println("Tanaman1");
      gotoY(120);
      delay(500);
      gotoZ(200);
      delay(500);
      gotoX(70);
      delay(500);
      Running(EEPROM.read(Tanaman1.JenisTanaman), EEPROM.read(Tanaman1.Usia), EEPROM.read(Tanaman1.Panen));
      break;
    case 2 :
      Serial.println("Tanaman2");
      gotoX(78);
      delay(500);
      Running(EEPROM.read(Tanaman2.JenisTanaman), EEPROM.read(Tanaman2.Usia), EEPROM.read(Tanaman2.Panen));
      break;
    case 3 :
      Serial.println("Tanaman3");
      gotoX(83);
      delay(500);
      Running(EEPROM.read(Tanaman3.JenisTanaman), EEPROM.read(Tanaman3.Usia), EEPROM.read(Tanaman3.Panen));
      break;
    case 4 :
      Serial.println("Tanaman4");
      gotoX(83);
      delay(500);
      Running(EEPROM.read(Tanaman4.JenisTanaman), EEPROM.read(Tanaman4.Usia), EEPROM.read(Tanaman4.Panen));
      break;

    case 5 :
      gotoY(90);
      delay(500);
      Running(EEPROM.read(Tanaman5.JenisTanaman), EEPROM.read(Tanaman5.Usia), EEPROM.read(Tanaman5.Panen));
      break;
    case 6 :
      gotoX(-78);
      delay(500);
      Running(EEPROM.read(Tanaman6.JenisTanaman), EEPROM.read(Tanaman6.Usia), EEPROM.read(Tanaman6.Panen));
      break;
    case 7 :
      gotoX(-78);
      delay(500);
      Running(EEPROM.read(Tanaman7.JenisTanaman), EEPROM.read(Tanaman7.Usia), EEPROM.read(Tanaman7.Panen));
      break;
    case 8 :
      gotoX(-83);
      delay(500);
      Running(EEPROM.read(Tanaman8.JenisTanaman), EEPROM.read(Tanaman8.Usia), EEPROM.read(Tanaman8.Panen));
      break;


    case 9 :
      gotoY(80);
      delay(500);
      Running(EEPROM.read(Tanaman9.JenisTanaman), EEPROM.read(Tanaman9.Usia), EEPROM.read(Tanaman9.Panen));
      break;
    case 10 :
      gotoX(88);
      delay(500);
      Running(EEPROM.read(Tanaman10.JenisTanaman), EEPROM.read(Tanaman10.Usia), EEPROM.read(Tanaman10.Panen));
      break;
    case 11 :
      gotoX(78);
      delay(500);
      Running(EEPROM.read(Tanaman11.JenisTanaman), EEPROM.read(Tanaman11.Usia), EEPROM.read(Tanaman11.Panen));
      break;
    case 12 :
      gotoX(78);
      delay(500);
      Running(EEPROM.read(Tanaman12.JenisTanaman), EEPROM.read(Tanaman12.Usia), EEPROM.read(Tanaman12.Panen));
      break;

    case 13 :
      gotoY(90);
      delay(500);
      Running(EEPROM.read(Tanaman13.JenisTanaman), EEPROM.read(Tanaman13.Usia), EEPROM.read(Tanaman13.Panen));
      break;
    case 14 :
      gotoX(-78);
      delay(500);
      Running(EEPROM.read(Tanaman14.JenisTanaman), EEPROM.read(Tanaman14.Usia), EEPROM.read(Tanaman14.Panen));
      break;
    case 15 :
      gotoX(-78);
      delay(500);
      Running(EEPROM.read(Tanaman15.JenisTanaman), EEPROM.read(Tanaman15.Usia), EEPROM.read(Tanaman15.Panen));
      break;
    case 16 :
      gotoX(-82);
      delay(500);
      Running(EEPROM.read(Tanaman16.JenisTanaman), EEPROM.read(Tanaman16.Usia), EEPROM.read(Tanaman16.Panen));
      break;

    case 17 :
      gotoY(90);
      delay(500);
      Running(EEPROM.read(Tanaman17.JenisTanaman), EEPROM.read(Tanaman17.Usia), EEPROM.read(Tanaman17.Panen));
      break;
    case 18 :
      gotoX(78);
      delay(500);
      Running(EEPROM.read(Tanaman18.JenisTanaman), EEPROM.read(Tanaman18.Usia), EEPROM.read(Tanaman18.Panen));
      break;
    case 19 :
      gotoX(78);
      delay(500);
      Running(EEPROM.read(Tanaman19.JenisTanaman), EEPROM.read(Tanaman19.Usia), EEPROM.read(Tanaman19.Panen));
      break;
    case 20 :
      gotoX(85);
      delay(500);
      Running(EEPROM.read(Tanaman20.JenisTanaman), EEPROM.read(Tanaman20.Usia), EEPROM.read(Tanaman20.Panen));
      break;

    case 21:
      homie();
      Count = 0;
      digitalWrite  (power, OFF);
      siramState = false;
      break;
  }
}

void siram(int value) {
  FlowA.Count = 0;
  while (true) {
    Serial2.println(FlowA.Count);
    digitalWrite(power, OFF);
    if (FlowA.Count <= value and value != 0 ) {
      digitalWrite(Pump, ON);
    } else {
      delay(500);
      digitalWrite(Pump, OFF);
      break;
    }
  }
  digitalWrite(power, ON);
  Count++;  // Pindah Step
}

bool CheckTanaman(int JenisTanaman) {
  if (JenisTanaman != 0) {
    Siram = true;
  } else {
    Siram = false;
  }
  return Siram;
}

int Takaran(int JenisTanaman, int Umur) {
  int Takar = 0;
  if (JenisTanaman >= 1 && JenisTanaman < 9 ) {
    if (Umur <= 7) {
      Takar = 1000; // 75 ml
    } else if (Umur > 7 && Umur <= 35) {
      Takar = 1300; // 100 ml
    } else {
      Takar = 1800; // 150 ml
    }
  }
  else {
    if (Umur <= 7) {
      Takar = 1000;  // 75 ml
    } else {
      Takar = 1300; // 100 ml
    }
  }
  return Takar;
}

void Running(int JenisTanaman, int UmurTanaman, int UmurPanen) {
  if (CheckTanaman(JenisTanaman)) {
    if (UmurTanaman < UmurPanen) {
      int ml = Takaran(JenisTanaman, UmurTanaman);
      siram(ml);
    } else {
      siram(1800);
    }
  } else {
    Count++; // Pindah Step
  }
}

bool CheckJam() {
  DateTime now = rtc.now();
  hNow = now.hour(), DEC;
  mNow = now.minute(), DEC;

  if (hNow == 7 and mNow == 0 ) {
    Pump = PumpFert;
    return true;
  } else if (hNow == 16 and mNow == 00) {
    Pump = PumpFert;
    return true;
  }
  return false;
}
