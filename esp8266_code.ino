#include "ThingSpeak.h"
#include <ESP8266WiFi.h>

//------- WI-FI details ----------//
char ssid[] = "OPPO A5s"; //SSID
char pass[] = "sandhya123"; // Passowrd
//--------------------------------//

//----------- Channel details ----------------//
unsigned long Channel_ID = 1637487; // Your Channel ID
const char * myWriteAPIKey = "BD1UNT635OV8GVH4"; //Your write API key
//-------------------------------------------//

const int Field_Number_1 = 1;
const int Field_Number_2 = 2;
const int Field_Number_3 = 3;
const int Field_Number_4 = 4;
String value = "";
int value_1 = 0, value_2 = 0, value_3 = 0, value_4 = 0;
int x, y;
WiFiClient  client;

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
  internet();
}

void loop()
{
  internet();
  if (Serial.available() > 0)
  {
    delay(100);
    while (Serial.available() > 0)
    {
      value = Serial.readString();
      if (value[0] == '*')
      {
        if (value[9] == '#')
        {
          value_1 = ((value[1] - 0x30) * 10 + (value[2] - 0x30));
          value_2 = ((value[3] - 0x30) * 10 + (value[4] - 0x30));
          value_3 = ((value[5] - 0x30) * 10 + (value[6] - 0x30));
          value_4 = ((value[7] - 0x30) * 10 + (value[8] - 0x30));
        }
      }
    }
  }
  upload();
}

void internet()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);
      delay(5000);
    }
  }
}

void upload()
{
  ThingSpeak.writeField(Channel_ID, Field_Number_1, value_1, myWriteAPIKey);
  delay(2000);
  ThingSpeak.writeField(Channel_ID, Field_Number_2, value_2, myWriteAPIKey);
  delay(2000);
  ThingSpeak.writeField(Channel_ID, Field_Number_3, value_3, myWriteAPIKey);
  delay(2000);
  ThingSpeak.writeField(Channel_ID, Field_Number_4, value_4, myWriteAPIKey);
  delay(2000);
  value = "";
}
