//#include <ESP8266WiFi.h>
#include "WiFi.h"
#include <Wire.h>
#include "Adafruit_MCP9808.h"
#define LICHT A0//Grove - Light Sensor is connected to A0 of Arduino

// Create the MCP9808 temperature sensor object
Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();

//char ssid[]    = "TP-Link_26EA";
//char password[] = "29304479";
char ssid[] = "telenet-apn-a26e6";
char password[] = "2yao18psxaqd";   

long duration;
int distance;
int ventilator = 4;

IPAddress host(193,190,154,184); 

String Data;
String DataLight;
String completeData;


void setup() {

  pinMode(ventilator, OUTPUT);    
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Verbinding aan het maken");
  
  while(WiFi.status() != WL_CONNECTED)
  { 
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP()); // locale IP van de ESP32*/

  if (!tempsensor.begin())
  {
    Serial.println("Couldn't find MCP9808!");
    while (1);
  }

}

void loop() 
{
  WiFiClient client;  
  float c = tempsensor.readTempC();
  int l = analogRead(LICHT);
  Serial.print("Temp: ");
  Serial.print(c);

  Serial.print(" C\t"); 
  Serial.println(DataLight);
   if (!client.connect( host , 24041))
    {      
        Serial.println("Connection to host failed");
        delay(1000);
        return;                        
    }

   if(c > 0 && l > 0)
   {
   Data = "Temperatuur>Bureau>"+String(c);  
   DataLight = "Licht>Bureau>"+String(l);
   }
          
   if(c > 26)
   {
   Data = "Temperatuur>Bureau>Ventilator_staat_aan>"+String(c);                          
   }

  completeData = Data +" "+DataLight;
  Serial.println(completeData);
  Serial.println("Temperatuur is");
  Serial.print(c);
  client.write((uint8_t)1);
  client.write((uint8_t)0);
  client.write((uint8_t)(completeData.length() + 1));
  client.write((uint8_t)0);
  client.print(completeData);
  client.flush();
  client.stop();
  delay(1000);      
  delay(500);
  }
  
