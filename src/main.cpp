#include <Arduino.h>
#include <DHT.h>
#include <SoftwareSerial.h>
#define DHTPING 2
#define DHTPINA 3
#define DHTPINP 4

 
// Uncomment whatever type you're using!
#define DHTTYPE DHT11 // DHT 11
//#define DHTTYPE DHT22 // DHT 22 (AM2302), AM2321
//#define DHTTYPE DHT21 // DHT 21 (AM2301)
#define RX 5
#define TX 6

SoftwareSerial espSerial(RX, TX);
DHT dhtGreenhouse(DHTPING, DHTTYPE);
DHT dhtAtmospheric(DHTPINA, DHTTYPE);
DHT dhtPile(DHTPINP, DHTTYPE);

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
  
  float tG = dhtGreenhouse.readTemperature();
  if (isnan(tG)) {
      return;
  }
  else 
  {
    str = String("G|T|°C|" + String(tG));
    allData = allData + str + ';';
  }

  float tA = dhtAtmospheric.readTemperature();
  if (isnan(tA)) {
      return;
  }
  else 
  {
    str = String("A|T|°C|" + String(tA));
    allData = allData + str + ';';
  }

  float tP = dhtPile.readTemperature();
  if (isnan(tP)) {
      return;
  }
  else 
  {
    str = String("P|T|°C|" + String(tP));
    allData = allData + str + ';';
  }

  float hG = dhtGreenhouse.readHumidity();
  if (isnan(hG)) {
      return;
  }
  else 
  {
    str =String("G|H|%|" + String(hG));
    allData = allData + str + ';';
  }
  
  float hA = dhtAtmospheric.readHumidity();
  if (isnan(hA)) {
      return;
  }
  else 
  {
    str =String("A|H|%|" + String(hA));
    allData = allData + str + ';';
  }
  
  float hP = dhtPile.readHumidity();
  if (isnan(hP)) {
      return;
  }
  else 
  {
    str =String("P|H|%|" + String(hP));
    allData = allData + str;
  }
  
  Serial.println(allData);
  espSerial.println(allData);

  delay(1000);
}