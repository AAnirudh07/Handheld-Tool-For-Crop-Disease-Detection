#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);

// Data wire is plugged into digital pin 2 on the Arduino
#define ONE_WIRE_BUS 3

// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

#define DHTTYPE DHT11
#define DHTPIN 2
DHT myDht(DHTPIN, DHTTYPE);

int sensorPin = A0; 

void setup()
{
  Serial.begin(9600);
  mySerial.begin(115200);
  myDht.begin();
  sensors.begin();
}
void loop()
{

  float humidity = myDht.readHumidity();
  float temperature = myDht.readTemperature();
  float soilTemp = sensors.getTempCByIndex(0);
  int sensorValue = analogRead(sensorPin); 
  float moistureP = map(sensorValue,1024,300,0,100);
  
  Serial.println();
  Serial.print("Atmos. Humidity: ");
  Serial.println(humidity, 0);
  Serial.print("Atmos. Temperature: ");
  Serial.println(temperature, 0);
  Serial.print("Soil Temperature: ");
  Serial.println(soilTemp,0);
  Serial.print("Soil Moisture : ");
  Serial.println(moistureP,0);
  
  //------Sending Data to ESP8266--------//
  mySerial.print('*'); // Starting char
  mySerial.print(humidity, 0);
  mySerial.print(temperature, 0);
  mySerial.print(soilTemp, 0);
  mySerial.print(moistureP, 0);
  mySerial.println('#'); // Ending char
  //------------------------------------//
  delay(2000);
}
