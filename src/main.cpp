#include <Arduino.h>
#include <DHT.h>
#include <SoftwareSerial.h>
#define DHTPIN 0
#define DHTPIN 1
#define DHTPIN 2

 
// Uncomment whatever type you're using!
#define DHTTYPE DHT11 // DHT 11
//#define DHTTYPE DHT22 // DHT 22 (AM2302), AM2321
//#define DHTTYPE DHT21 // DHT 21 (AM2301)
#define RX 5
#define TX 6

SoftwareSerial espSerial(RX, TX);
DHT dhtGreenhouse(DHTPIN, DHTTYPE);
DHT dhtAtmospheric(DHTPIN, DHTTYPE);
DHT dhtPile(DHTPIN, DHTTYPE);

String str;
 
void setup(){
pinMode(RX, INPUT);
pinMode(TX, OUTPUT);

Serial.begin(115200);
espSerial.begin(9600);
dhtGreenhouse.begin();
dhtAtmospheric.begin();
dhtPile.begin();
delay(2000);
}
 
 
void loop()
{
  String allData = "";
  
  float hG = dhtGreenhouse.readHumidity();
  if (isnan(hG)) {
      return;
  }
  else 
  {
    str =String("GH|" + String(hG));
    allData = allData + str;
  }
  
  float tG = dhtGreenhouse.readTemperature();
  if (isnan(tG)) {
      return;
  }
  else 
  {
    str = String("GT|" + String(tG));
    allData = allData + '$' + str;
  }

  float hA = dhtAtmospheric.readHumidity();
  if (isnan(hA)) {
      return;
  }
  else 
  {
    str =String("AH|" + String(hA));
    allData = allData + str;
  }
  
  float tA = dhtAtmospheric.readTemperature();

  if (isnan(tA)) {
      return;
  }
  else 
  {
    str = String("AT|" + String(tA));
    allData = allData + '$' + str;
  }

  Serial.println(allData);
  espSerial.println(allData);

  delay(1000);
}