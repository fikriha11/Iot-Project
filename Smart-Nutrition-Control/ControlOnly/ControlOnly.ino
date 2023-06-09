#include <Wire.h>
#include <EEPROM.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);

#define encoder0PinA  19
#define encoder0PinB  18
#define SwitchBtn 17

/* Switch Sensor */
#define sw_airbaku  A1
#define sw_mixLow  A2
#define sw_mixHigh  A3
#define sw_A  A4
#define sw_B  A5

#define Pump 8
#define MotorMixA 11
#define MotorMixB 10
#define MotorMixCampuran 7
#define PumpMixA 9
#define PumpMixB 12
#define PumpOut 6
#define SensorFlowA  2
#define SensorFlowB  3


#define ON  1
#define OFF 2

int flowMixA = 0;
int flowMixB = 0;

bool State = true;
bool ProsesMixing = false;
bool IsiTandonCampuran = false;
bool PenambahanABmix = false;
bool Distribusi = false;
bool Mixing = false;
bool BacaSensor = true;

bool PupukA = false;
bool PupukB = false;

int CursorPos = 0;
bool state = false;
bool Button = false;


byte menuCount = 0;
byte ppmCount = 0;
byte pulse = 0;

/* trial */
String SerialData;
String Data[10];
String SplitData;
int StringData;

/** SAVE EEPROM **/
bool Start = true;
bool Setting = false;

/* Address */
int addrPPM = 0;


struct SensorFlow {
  int Count;
} FlowA, FlowB;




void BacaSensorTandonUtama() {
  if (digitalRead(sw_airbaku) == HIGH) {
    ProsesMixing = true;
    IsiTandonCampuran = true;
    BacaSensor = false;
  }
}


void Pompa(int Status) {
  if (Status == ON) {
    digitalWrite(Pump, LOW);
  } else {
    digitalWrite(Pump, HIGH);
  }
}

void MotorMix(int Type, int Status) {
  if (Status == ON) {
    digitalWrite(Type, LOW);
  } else {
    digitalWrite(Type, HIGH);
  }
}


void setup() {
  Wire.begin();
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  ppmCount = EEPROM.read(addrPPM);

  /* Switch */
  pinMode(sw_airbaku, INPUT);
  pinMode(sw_mixLow, INPUT);
  pinMode(sw_mixHigh, INPUT);
  pinMode(sw_A, INPUT);
  pinMode(sw_B, INPUT);
  pinMode(SwitchBtn, INPUT_PULLUP);

  /* Motor and Valve */
  pinMode(Pump, OUTPUT);
  pinMode(MotorMixCampuran, OUTPUT);
  pinMode(MotorMixA, OUTPUT);
  pinMode(MotorMixB, OUTPUT);
  pinMode(PumpMixA, OUTPUT);
  pinMode(PumpMixB, OUTPUT);
  pinMode(PumpOut, OUTPUT);

  digitalWrite(Pump, HIGH);
  digitalWrite(MotorMixA, HIGH);
  digitalWrite(MotorMixB, HIGH);
  digitalWrite(PumpMixA, HIGH);
  digitalWrite(PumpMixB, HIGH);
  digitalWrite(PumpOut, HIGH);
  digitalWrite(MotorMixCampuran, HIGH);

  pinMode(SensorFlowA, INPUT);
  pinMode(SensorFlowB, INPUT);

  attachInterrupt(digitalPinToInterrupt(encoder0PinA), doEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(SensorFlowA), pulseCounterA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(SensorFlowB), pulseCounterB, CHANGE);

  display.clearDisplay();
  display.setTextSize(1.7);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("AN-MIX");
  display.print("Menyiapkan...");
  display.display();
  delay(5000);
}


void loop() {
  setting();
  MainLoop();

}

void setting() {
  if (digitalRead(SwitchBtn) == LOW) {
    Button = true;
  } if (digitalRead(SwitchBtn) == HIGH && Button) {
    menuCount = 0;
    Start = false;
    Setting = true;
    Button = false;
  }
  while (Setting) {
    staticMenu();
    menuCheck();
  }
}


void MainLoop() {
  if (BacaSensor  && Start) {
    ppmSetting();
    // Serial.println("STAND BY");
    BacaSensorTandonUtama();
  }
  while (ProsesMixing) {
    /******* Isi Air Tandon Campuran ******/
    showPhrase("ISI AIR BAKU", 25, 10);
    // Serial.println("ISI AIR BAKU");
    if (IsiTandonCampuran) {
      if (digitalRead(sw_mixHigh) == HIGH) {
        delay(500);
        Pompa(ON);
        MotorMix(MotorMixA, ON);
        MotorMix(MotorMixB, ON);
      }
      else {
        delay(500);
        Pompa(OFF);
        MotorMix(MotorMixA, OFF);
        MotorMix(MotorMixB, OFF);
        delay(2000);
        IsiTandonCampuran = false;
        PenambahanABmix = true;
        PupukA = true;
        ResetFlow();
      }
    }

    /******* Proses Penambahan Pupuk ABmix ******/
    while (PenambahanABmix) {
      readFlow();
      int target = EEPROM.read(addrPPM);
      if (PupukA) {
        showPhrase("TAMBAH NUTRISI A", 19, 10);
        // Serial.println("Nutrisi A");
        digitalWrite(PumpMixA, LOW);
        if (FlowA.Count >= target ) {
          digitalWrite(PumpMixA, HIGH);
          delay(3000);
          PupukA = false;
          PupukB = true;
        }
      }
      if (PupukB) {
        showPhrase("TAMBAH NUTRISI B", 19, 10);
        // Serial.println("Nutrisi A");
        digitalWrite(PumpMixB, LOW);
        if (FlowB.Count >= target) {
          digitalWrite(PumpMixB, HIGH);
          delay(3000);
          State = true;
          PupukA = false;
          PupukB = false;
          Mixing = true;
          PenambahanABmix = false;
        }
      }
    }

    /******* Proses Mixing tandon Campuran ******/
    while (Mixing) {
      showPhrase("PENGADUKAN", 33, 10);
      // Serial.println("MIXING");
      MotorMix(MotorMixCampuran, ON);
      delay(60000);
      MotorMix(MotorMixCampuran, OFF);
      delay(2000);
      State = true;
      Mixing = false;
      Distribusi = true;
    }

    /******* Proses Distribusi Pupuk ******/
    while (Distribusi) {
      showPhrase("PENGELUARAN", 33, 10);
      // ReadSwitch();
      digitalWrite(PumpOut, LOW);
      if (digitalRead(sw_mixLow) == HIGH) {
        delay(48000);
        digitalWrite(PumpOut, HIGH);
        showPhrase("PENGELUARAN", 33, 10);
        Distribusi = false;
        ProsesMixing = false;
        BacaSensor = true;
      }
    }
  }
}

void ResetFlow() {
  FlowA.Count = 0;
  FlowB.Count = 0;
}

void pulseCounterA() {
  FlowA.Count++;
}

void pulseCounterB() {
  FlowB.Count++;
}

void doEncoder() {
  if (digitalRead(encoder0PinA) == HIGH) {
    if (digitalRead(encoder0PinB) == LOW && ppmCount > 0) {
      ppmCount--;
      menuCount--;
      pulse--;
    }
    else {
      ppmCount++;
      menuCount++;
      pulse++;
    }
  }
  else
  {
    if (digitalRead(encoder0PinB) == LOW ) {
      ppmCount++;
      menuCount++;
      pulse++;
    }
    else {
      if (ppmCount > 0) {
        ppmCount--;
        menuCount--;
        pulse--;
      }

    }
  }
}

/** Versi 2 **/
//void doEncoder() {
//  if (digitalRead(encoder0PinA) == digitalRead(encoder0PinB)) {
//    ppmCount++;
//    menuCount++;
//    pulse++;
//  } else {
//    ppmCount--;
//    menuCount--;
//    pulse--;
//  }
//
//  if (ppmCount < 0) {
//    ppmCount = menuCount = pulse = 0;
//  } if (ppmCount > 287) {
//    ppmCount = 287;
//  }
//}
