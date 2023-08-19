#include <Arduino.h>
#include <DHT.h>
#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>


#define DHTPIN1 2
#define DHTPIN2 3

#define SOIL_MOISTURE_PIN1 A0
#define SOIL_MOISTURE_PIN2 A1

#define ONE_WIRE_BUS 4
#define DHTTYPE DHT22 

#define RX 5
#define TX 6
#define SENSOR_COUNT 8 
#define SENSOR_WAIT_TIME 900000 / SENSOR_COUNT

/*SoftwareSerial espSerial(RX, TX);*/
OneWire oneWire(ONE_WIRE_BUS);


DHT dhtPlant1(DHTPIN1, DHTTYPE);
DHT dhtPlant2(DHTPIN2, DHTTYPE);

String str;
String sensorData[SENSOR_COUNT];
DallasTemperature soilTempSensors(&oneWire);

int numberOfSoilMoistureSensors;
DeviceAddress tempSMSAddress;

const int drySoilMoisture = 595; // value for dry sensor
const int wetSoilMoisture = 239; // value for wet sensor


void setup(){
pinMode(RX, INPUT);
pinMode(TX, OUTPUT);

Serial.begin(115200);
/*espSerial.begin(9600);*/
dhtPlant1.begin();
dhtPlant2.begin();
soilTempSensors.begin();


numberOfSoilMoistureSensors = soilTempSensors.getDeviceCount();
Serial.println(numberOfSoilMoistureSensors, DEC);


delay(2000);
}
 
 
void loop()
{
  
  float hP1 = dhtPlant1.readHumidity();
  
  if (isnan(hP1)) {
     return;
  }
  else 
  {
    str =String("hP1|" + String(hP1));
    sensorData[0] = str;
  }
  
  float tP1 = dhtPlant1.readTemperature();
  if (isnan(tP1)) {
      return;
  }
  else 
  {
    str = String("tP1|" + String(tP1));
    sensorData[1] = str;
  }

  float hP2 = dhtPlant2.readHumidity();
  if (isnan(hP2)) {
      return;
  }
  else 
  {
    str =String("hP2|" + String(hP2));
    sensorData[2] = str;
  }
  
  float tP2 = dhtPlant2.readTemperature();

  if (isnan(tP2)) {
      return;
  }
  else 
  {
    str = String("tP2|" + String(tP2));
    sensorData[3] = str;
  }

  int smP1 = analogRead(SOIL_MOISTURE_PIN1);

  if (isnan(smP1)) {
      return;
  }
  else 
  {
    int soilMoistureP1 = map(smP1, wetSoilMoisture, drySoilMoisture, 100, 0); 
    str = String("smP1|" + String(soilMoistureP1));
    sensorData[4] = str;
  }

  int smP2 = analogRead(SOIL_MOISTURE_PIN2);

  if (isnan(smP2)) {
      return;
  }
  else 
  {
    int soilMoistureP2 = map(smP2, wetSoilMoisture, drySoilMoisture, 100, 0); 
    str = String("smP2|" + String(soilMoistureP2));
    sensorData[5] = str;
  }

  soilTempSensors.requestTemperatures();

  int stP1 = soilTempSensors.getTempCByIndex(0);
  if (isnan(stP1)) {
    return;
  }
  else
  {
    str =String("stP1|" + String(stP1));
    sensorData[6] = str;
  }
  
  int stP2 = soilTempSensors.getTempCByIndex(1);
  if (isnan(stP2)) {
    return;
  }
  else
  {
    str =String("stP2|" + String(stP2));
    sensorData[7] = str;
  }
    

  Serial.println("Acquired all sensor data ---> ");
  
  delay(1000);

  for(int i = 0; i < SENSOR_COUNT; i++) 
  {
    /*espSerial.println(sensorData[i]);*/
    Serial.println("Sensor:" + sensorData[i]);
    delay(3000);
  }
  
  Serial.println("Done sending sensor data");
  delay(1000);
  
}