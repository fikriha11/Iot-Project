#include <WiFi.h>
#include <NTPClient.h>
#include <HTTPClient.h>

//const char* ssid = "Workshop TRM";
//const char* password = "1sampai8";

const char* ssid = "Haikal";
const char* password = "jember2022";

const long utcOffsetInSeconds = 25200;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "asia.pool.ntp.org", utcOffsetInSeconds);

const char* serverName = "http://192.168.1.106:5001/sensor";


const int pin_interrupt = 14;
long int jumlah_tip = 0;
long int temp_jumlah_tip = 0;
float curah_hujan = 0.00;
float milimeter_per_tip = 0.30;
volatile boolean flag = false;

int detik;
String timeFormat;
String cuaca;


int suhu = 26;
int kelembapan = 74;

long ltime = millis();

float temp_curah_hujan_per_menit = 0.00;
float curah_hujan_per_menit = 0.00;
bool debug = false;

void ICACHE_RAM_ATTR hitung_curah_hujan()
{
  flag = true;
}


void setup() {
  Serial.begin(9600);
  delay(1000);

  pinMode(pin_interrupt, INPUT);
  attachInterrupt(digitalPinToInterrupt(pin_interrupt), hitung_curah_hujan, FALLING);

  WiFi.begin(ssid, password);
  Serial.println("\nConnecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }

  timeClient.begin();

  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());
}


void loop()
{
  updatePerMinute();
}

void readSensor() {
  if (flag == true)
  {
    curah_hujan += milimeter_per_tip;
    jumlah_tip++;
    delay(500);
    flag = false;
  }
  curah_hujan = jumlah_tip * milimeter_per_tip;
  if ((jumlah_tip != temp_jumlah_tip))
  {
    if (debug) {
      printSerial();
    }
  }
  temp_jumlah_tip = jumlah_tip;

}

void printSerial()
{
  Serial.print("Jumlah tip=");
  Serial.print(jumlah_tip);
  Serial.println(" kali ");
  Serial.print("Curah hujan=");
  Serial.print(curah_hujan, 1);
  Serial.print(" mm");
  Serial.println();
}


void updateTime() {
  timeClient.update();
  detik = timeClient.getSeconds();
  timeFormat = timeClient.getFormattedDate();
  timeFormat = timeFormat.substring(0, 10) + " " + timeFormat.substring(11, 19);
  delay(500);
}

void updatePerMinute() {
  updateTime();
  readSensor();
  if (millis() - ltime >= 1000) {
    temp_curah_hujan_per_menit = curah_hujan;
    if (detik == 0) {
      curah_hujan_per_menit = temp_curah_hujan_per_menit;

      // Reset
      temp_curah_hujan_per_menit = 0.00;
      curah_hujan = 0.00;
      jumlah_tip = 0; 
      
      checkCuaca(curah_hujan_per_menit);
      postdata(curah_hujan_per_menit, cuaca, timeFormat);
    }
    ltime = millis();
  }
}


void postdata(int curah_hujan, String cuaca, String datetime) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    // String arduinoDataString = "{\"curah_hujan\": " + String(curah_hujan) + ", \"cuaca\": \"" + cuaca + "\", \"createdAt\": \"" + datetime + "\"}";
    String arduinoDataString = "{\"curah_hujan\": " + String(curah_hujan) + ", \"cuaca\": \"" + cuaca + "\", \"suhu\": " + String(suhu) + ", \"kelembapan\": " + String(kelembapan) + ", \"createdAt\": \"" + datetime + "\"}";
    http.begin(client, serverName);
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST(arduinoDataString);

    if (httpResponseCode > 0) {
      Serial.print("HTTP response code: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Error sending POST request: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
}


void checkCuaca(int curah_hujan_hari_ini) {
  //Probabilistik Curah Hujan https://www.bmkg.go.id/cuaca/probabilistik-curah-hujan.bmkg
  if (curah_hujan_hari_ini <= 0.00 && curah_hujan_hari_ini <= 0.50)
  {
    cuaca = "Berawan";
  }
  if (curah_hujan_hari_ini > 0.50 && curah_hujan_hari_ini <= 20.00)
  {
    cuaca = "Hujan Ringan";
  }
  if (curah_hujan_hari_ini > 20.00 && curah_hujan_hari_ini <= 50.00)
  {
    cuaca = "Hujan Sedang";
  }
  if (curah_hujan_hari_ini > 50.00 && curah_hujan_hari_ini <= 100.00)
  {
    cuaca = "Hujan Lebat";
  }
  if (curah_hujan_hari_ini > 100.00 && curah_hujan_hari_ini <= 150.00)
  {
    cuaca = "Hujan Sgt Lebat";
  }
  if (curah_hujan_hari_ini > 150.00)
  {
    cuaca = "Hujan ekstrem";
  }
}
