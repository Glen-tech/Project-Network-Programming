#include <ESP8266WiFi.h>

char ssid[]    = "telenet-apn-a26e6";
char password[] = "2yao18psxaqd";
IPAddress host(193,190,154,184); 
String Data = "Testing message to BenEthernet from ESP32";
DHT dht(DHTPIN, DHTTYPE);

void setup() {
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
  Serial.println(WiFi.localIP()); // locale IP van de ESP32
}

void loop() 
{
    WiFiClient client;
  
    if (!client.connect( host , 24041))
    {      
        Serial.println("Connection to host failed");
        delay(1000);
        return;                        
    }
         else
         {
            Serial.println("Temperatuur is ");
            Serial.print(t);
            Serial.println("connecting...");
            client.write((uint8_t)1);
            client.write((uint8_t)0);
            client.write((uint8_t)(Data.length() + 1));
            client.write((uint8_t)0);
        
            // here's the actual content of the PUT request:
            client.print(Data);
            client.flush();
            client.stop();
            delay(1000);          
         }
  delay(500);
  }
