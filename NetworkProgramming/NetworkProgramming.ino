#include <ESP8266WiFi.h>
#include <Wire.h>
#include "Adafruit_MCP9808.h"
 
// Create the MCP9808 temperature sensor object
Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();

long duration;
int distance;
int ventilator = 4;

char ssid[]    = "telenet-apn-a26e6";
char password[] = "2yao18psxaqd";
IPAddress host(193,190,154,184); 
String Data;
void temperatuur();

void setup() {

  pinMode(ventilator, OUTPUT);    
  Serial.begin(9600);

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
  Serial.print("Temp: ");
  Serial.print(c);
  Serial.print(" C\t"); 

    if(c > 28.00)
    {
      digitalWrite(ventilator,HIGH);
      Serial.print("Ventilator staat aan");
    }

    else 
    {
      digitalWrite(ventilator,LOW);
      Serial.print("Ventilator staat uit");
    }
   if (!client.connect( host , 24041))
    {      
        Serial.println("Connection to host failed");
        delay(1000);
        return;                        
    }
         else
         {
                    
                  Data = String(c);
                  Serial.println("Temperatuur is ");
                  Serial.print(c);
                  Serial.println("connecting...");
                  client.write((uint8_t)1);
                  client.write((uint8_t)0);
                  client.write((uint8_t)(Data.length() + 1));
                  client.write((uint8_t)0);
                  // here's the actual content of the PUT request:
                  client.print(Data);
                  client.flush();
                  client.stop();
                  delay(3000);       
         }
  delay(500);
  }
  
