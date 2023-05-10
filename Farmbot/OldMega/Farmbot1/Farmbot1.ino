
#include <EEPROM.h>
#include "RTClib.h"
#include <SimpleTimer.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);

Servo Servo1;
Servo Servo2;
RTC_DS3231 rtc;
SimpleTimer timer;

#define SwitchZ A1
#define SwitchX A2
#define SwitchY A3
#define SwitchL A4

#define SensorFlowA  3
#define button 47
#define Rotary_CHA 19
#define Rotary_CHB 18

/* Relay */
#define PumpWater 32
#define PumpFert 34
#define power 36

/* Stepper */
#define PulseY 12
#define DirY 11
#define PulseZ 10
#define DirZ 9
#define PulseX 8
#define DirX 7
#define PulseL 31
#define DirL 33


struct Tanaman {
  int Usia, JenisTanaman, Tanggal, Bulan, Tahun, Panen;
} Tanaman1, Tanaman2, Tanaman3, Tanaman4, Tanaman5, Tanaman6, Tanaman7, Tanaman8,
Tanaman9, Tanaman10, Tanaman11, Tanaman12, Tanaman13, Tanaman14, Tanaman15, Tanaman16,
Tanaman17, Tanaman18, Tanaman19, Tanaman20;

const char* nTanaman[] = {
  "Kangkung", "Selada", "Pak Coy", "Bayam", "Sawi Pagoda", "kailan", "Sawi", "Daun Bawang", "Daun Mint", "Seledri"
};
const char* nHari[] = {
  "Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jum'at", "Sabtu"
};
const char* nBulan[] = {
  "Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"
};

bool Update = false;

long delay_Micros = 1800; // Set value
long currentMicros = 0; long previousMicros = 0;
String dataTerima;
String dataSave;
String dataTrial;
int limit;
int Count = 0;
long nMM = 150;
int speedDelay = 200;

/** RTC **/
int tNow = 0; // Tanggal
int bNow = 0; // Bulan
int yNow = 0; // Tahun

int hNow = 0; // Jam
int mNow = 0; // Menit

struct SensorFlow {
  int Count;
} FlowA, FlowB;


bool Siram = false;
bool AirBaku = false;
bool AirNutrisi = false;
int Pump = 0;

/* Control Loop */
bool siramState = false;
bool tanamState = false;

const int ON = LOW;
const int OFF = HIGH;

int  CursorPos = 0;
bool Plantstate = false;
bool Flushstate = false;
bool ButtonState = false;

struct ENC
{
  volatile long int pulseCnt;
  long int lastpulse;
} Rotary;

long lastime;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial3.begin(9600);
  rtc.begin();
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  INISIALISASI();

  configTSL();
  pinMode(PumpWater, OUTPUT);
  pinMode(PumpFert, OUTPUT);
  pinMode(power, OUTPUT);
  pinMode(SensorFlowA, INPUT);
  pinMode(SwitchZ, INPUT_PULLUP);
  pinMode(SwitchX, INPUT_PULLUP);
  pinMode(SwitchY, INPUT_PULLUP);
  pinMode(SwitchL, INPUT_PULLUP);
  pinMode(button, INPUT_PULLUP);

  pinMode(PulseX, OUTPUT);
  pinMode(DirX, OUTPUT);
  pinMode(PulseY, OUTPUT);
  pinMode(DirY, OUTPUT);
  pinMode(PulseZ, OUTPUT);
  pinMode(DirZ, OUTPUT);
  pinMode(PulseL, OUTPUT);
  pinMode(DirL, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(SensorFlowA), pulseCounterA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(Rotary_CHA), Rotary_INTT_A, CHANGE);
  attachInterrupt(digitalPinToInterrupt(Rotary_CHB), Rotary_INTT_B, CHANGE);
  digitalWrite(DirX, LOW);
  digitalWrite(DirY, LOW);
  digitalWrite(DirZ, LOW);
  digitalWrite(DirL, LOW);
  digitalWrite(PumpWater, OFF);
  digitalWrite(PumpFert, OFF);

  Servo1.attach(A8);
  Servo2.attach(A9);
  servotutup();

  //  digitalWrite(power, ON);
  //  homie();
  //  digitalWrite(power, OFF);
  //  delay(2000);

  /* SET RTC */
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {
  ReceiveData();
  updateSensor();
  Running();
  navigation();
}

void navigation() {
  menuCheck();
  staticMenu();
}


void Running() {
  if (CheckJam()) {
    siramState = true;
  }

  while (siramState) {
    Serial.println("SIRAM");
    digitalWrite(power, ON);
    SiramTanaman();
  }

  while (tanamState) {
    Serial.println("TANAM");
    digitalWrite(power, ON);
    Tanam();
    tanamState = false;
  }
}


void pulseCounterA() {
  FlowA.Count++;
}
