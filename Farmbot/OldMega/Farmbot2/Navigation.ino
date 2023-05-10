void menuCheck() {
  CursorPos = map(Rotary.pulseCnt, 0, 255, 0, 10);
  if (Rotary.pulseCnt > 55) {
    if (Button()) {
      ButtonState = true;
    }
    if (ButtonState && !Button()) {
      Rotary.pulseCnt = 0;
      ButtonState = false;
      Plantstate = true;
    }
    CursorPos = 10;
  }
  else {
    if (Button()) {
      ButtonState = true;
    }
    if (ButtonState && !Button()) {
      ButtonState = false;
      Flushstate = true;
    }
    CursorPos = 0;
  }

  while (Plantstate) { // Tanam
    Count = map(Rotary.pulseCnt, 0, 255, 1, 20);
    displayTanam();
    if (Button()) {
      ButtonState = true;
    }
    if (ButtonState && !Button()) {
      tanamState = true;
      ButtonState = false;
      Plantstate = false;
    }
  }

  while (Flushstate) { // Siram
    displaySiram();
    if (Rotary.pulseCnt > 55) {
      CursorPos = 10;
      if (Button()) {
        ButtonState = true;
      }
      if (ButtonState && !Button()) {
        siramState = true;
        Pump = PumpWater;
        ButtonState = false;
        Flushstate = false;
      }
    }
    else {
      if (Button()) {
        ButtonState = true;
      }
      if (ButtonState && !Button()) {
        siramState = true;
        Pump = PumpFert;
        ButtonState = false;
        Flushstate = false;
      }
      CursorPos = 0;
    }
  }
}

void staticMenu() {
  display.setTextColor(WHITE);
  display.setTextSize(1.7);
  display.setCursor(10, 0);
  display.println("SIRAM");
  display.setCursor(10, 10);
  display.println("TANAM ");
  display.setCursor(2, CursorPos);
  display.println(">");
  display.display();
  display.clearDisplay();
  delay(50);
}

void displayTanam() {
  display.setTextColor(WHITE);
  display.setTextSize(1.7);
  display.setCursor(25, 0);
  display.println("PILIH TANAMAN");

  display.setTextSize(2);
  display.setCursor(50, 13);
  display.println(Count);

  display.display();
  display.clearDisplay();
  delay(50);
}

void displaySiram() {
  display.setTextColor(WHITE);
  display.setTextSize(1.7);
  display.setCursor(10, 0);
  display.println("FERT");
  display.setCursor(10, 10);
  display.println("WATER");
  display.setCursor(2, CursorPos);
  display.println(">");
  display.display();
  display.clearDisplay();
  delay(50);
}
