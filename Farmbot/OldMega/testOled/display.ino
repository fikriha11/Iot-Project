void menuCheck() {
  CursorPos = map(Rotary.pulseCnt, 0, 255, 0, 10);
  if (Rotary.pulseCnt < 55) {

    if (Serial.available()) {
      String Data = Serial.readStringUntil('\n');
      if (Data == "a") {
        Button = true;
      }
    }

    if (Button && digitalRead(SwitchBtn) == HIGH ) {
      Button = false;
      state = true;
    }
    CursorPos = 0;
  } else {
    CursorPos = 10;
  }
  while (state) {
    displayTanaman();
    if (Serial.available()) {
      String Data = Serial.readStringUntil('\n');
      if (Data == "a") {
        state = false;
      }
    }
  }
}

void displayTanaman() {
  display.setTextColor(WHITE);
  display.setTextSize(1.7);
  display.setCursor(25, 0);
  display.println("PILIH TANAMAN");

  display.setTextSize(2);
  display.setCursor(50, 13);
  display.println(map(Rotary.pulseCnt, 0, 255, 0, 20));

  display.display();
  display.clearDisplay();
  delay(50);
}
