#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);
#define SwitchBtn 17
#define Rotary_CHA 18
#define Rotary_CHB 19

struct ENC
{
  volatile long int pulseCnt;
  long int lastpulse;
} EncDepan, EncBelakang, EncKanan, EncKiri, EncX, Rotary;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  pinMode(INPUT_PULLUP, SwitchBtn);

  attachInterrupt(digitalPinToInterrupt(Rotary_CHA), Rotary_INTT_A, CHANGE);
  attachInterrupt(digitalPinToInterrupt(Rotary_CHB), Rotary_INTT_B, CHANGE);
}

void loop() {
  menuCheck();
}


void trialRotary() {
  Serial.print(LimitRotary());
  Serial.print("\t");
  Serial.println(switchRotary());
}
