#include <ESP8266WiFi.h>
#include <Wire.h>

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
  
}

void loop() 
{
  WiFiClient client;  
  Serial.print("Temp: ");
  float c = 15;
  Serial.print(c);

  Serial.print(" C\t"); 
  Serial.println(Data);
   if (!client.connect( host , 24041))
    {      
        Serial.println("Connection to host failed");
        delay(1000);
        return;                        
    }


  Data = "Temperatuur>Living>"+String(c);
  Serial.println(Data);
  Serial.println("Temperatuur is");
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
  
