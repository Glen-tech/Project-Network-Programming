#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Wire.h>
#include "Adafruit_MCP9808.h"

//Ingave netwerk

unsigned long time_1 = 0;
unsigned long time_2 = 0;
char ssid[]    = "TP-Link_26EA";
char password[] = "29304479";

IPAddress local_IP(192, 168, 0, 54);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255 ,0);

//Ingave website voor ingave 

// API code , moet ook in de php code zitten. 
//object temperatuursensor
//Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();

WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  
  WiFi.begin(ssid, password);
  Serial.println("Verbinding aan het maken");
  
  while(WiFi.status() != WL_CONNECTED)
  { 
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  
  if (!WiFi.config(local_IP, gateway, subnet)) 
  {
    Serial.println("STA Failed to configure");
  }
  
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() 
{
    WiFiClient client = server.available();
    
    if (client)
    {                                
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) // loop while the client's connected
    {            
      if (client.available()) 
      {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);  
      }
    }
  delay(500);
}
}
