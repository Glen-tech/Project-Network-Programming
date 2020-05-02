#include <ESP8266WiFi.h>
#include <Wire.h>
#include "Adafruit_MCP9808.h"
 
// Create the MCP9808 temperature sensor object
Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();

char ssid[]    = "TP-Link_26EA";
char password[] = "29304479";

long duration;
int distance;
int ventilator = 4;


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

   if (!client.connect( host , 24041))
    {      
        Serial.println("Connection to host failed");
        delay(1000);
        return;                        
    }

   if(c > 22)
   {
   Data = "Lage temperatuur , rond de 20 graden";  
   }
       
   if(c > 24)
   {
   Data = "Hoge temperatuur , rond de 22 graden";  
   }
          
   if(c > 26)
   {
   Data = "Ventilator staat aan , boven 26 graden";                           
   }

  Serial.println("Temperatuur is ");
  Serial.print(c);
  client.write((uint8_t)1);
  client.write((uint8_t)0);
  client.write((uint8_t)(Data.length() + 1));
  client.write((uint8_t)0);
  client.print(Data);
  client.flush();
  client.stop();
  delay(1000);      
  delay(500);
  }
  
