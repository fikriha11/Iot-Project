#include <Wire.h>
#include "TSL2561.h"

//#include <BH1750.h>

//#BH1750 lightMeter;

#define AddrTSL 0x39
#define AddrSHT 0x44
#define soilMoisture A10

#include "Adafruit_SHT31.h"
bool enableHeater = false;
uint8_t loopCnt = 0;
Adafruit_SHT31 sht31 = Adafruit_SHT31();

const int AirValue = 620;
const int WaterValue = 310;

int soilMoistureValue =  0;
int soilmoisturepercent = 0;


int Moisture() {
  soilMoistureValue = analogRead(soilMoisture);
  soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 100, 0);
  if (soilmoisturepercent > 100) {
    soilmoisturepercent = 100; //return 100;
  }
  else if (soilmoisturepercent < 0) {
    soilmoisturepercent = 0; //return 0;
  }
  else {
    soilmoisturepercent;
  }
  int indexSoil = map(soilmoisturepercent, 0, 100, 1, 5);
  return indexSoil;
}


void configTSL() {
  Wire.beginTransmission(AddrTSL);
  Wire.write(0x00 | 0x80);
  Wire.write(0x03);
  Wire.endTransmission();

  Wire.beginTransmission(AddrTSL);
  Wire.write(0x01 | 0x80);
  Wire.write(0x02);
  Wire.endTransmission();
  delay(300);
  sht31.begin(0x44);
}

int Lumen() {
  unsigned int data[4];
  for (int i = 0; i < 4; i++)
  {
    Wire.beginTransmission(AddrTSL);
    Wire.write((140 + i));
    Wire.endTransmission();
    Wire.requestFrom(AddrTSL, 1);

    if (Wire.available() == 1)
    {
      data[i] = Wire.read();
    }
    delay(200);
  }

  // Convert the data
  double ch0 = ((data[1] & 0xFF) * 256) + (data[0] & 0xFF);
  double ch1 = ((data[3] & 0xFF) * 256) + (data[2] & 0xFF);
  if (ch1 > 8000.0 || ch1 < 0.0) {
    ch1 = 8000.0;
  }
  int indexLux = map(ch1, 0.0, 8000.0, 1, 4);
  return indexLux;
}

/*int Lumen2(){
  Wire.begin();
  lightMeter.begin();
  lightMeter.setMTreg(32);
  float lux = lightMeter.readLightLevel();
  return lux;
  }
*/

int SHT(String param) {

  float cTemp = sht31.readTemperature();
  float humidity = sht31.readHumidity();

  if (cTemp < 0.0) {
    cTemp = 55.0;
  }
  if (param == "Temp") {
    return cTemp;
  } else {
    return humidity;
  }

}


/*int SHT(String param) {
  unsigned int data[6];

  Wire.beginTransmission(AddrSHT);
  Wire.write(0x2C);
  Wire.write(0x06);
  Wire.endTransmission();
  delay(300);
  Wire.beginTransmission(AddrSHT);
  Wire.endTransmission();
  Wire.requestFrom(AddrSHT, 6);

  if (Wire.available() == 6)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
    data[3] = Wire.read();
    data[4] = Wire.read();
    data[5] = Wire.read();
  }

  // Convert the data
  int temp = (data[0] * 256) + data[1];
  float cTemp = -45.0 + (175.0 * temp / 65535.0);
  float fTemp = (cTemp * 1.8) + 32.0;
  float humidity = (100.0 * ((data[3] * 256.0) + data[4])) / 65535.0;

  if (param == "Temp") {
    return cTemp;
  } else {
    return humidity;
  }
  }
*/

void updateSensor() {
  if (Update) {
    if (millis() - lastime > 3000) {
      if (!siramState and !tanamState) {
        String temp = String(SHT("Temp"));
        String humid = String(SHT("Hum"));
        String lumen = String(Lumen());
        String moisture = String(Moisture());
        Serial.println("A" + String(1) + "B" + temp + "C" + humid + "D" + lumen + "E" + moisture + "F");
      }
      lastime = millis();
    }
  } else {
    lastime = millis();
  }
}
