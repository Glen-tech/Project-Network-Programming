client.cpp : Via hier kan de gebruiker commando's geven voor de data te filteren van 3 verschillende sensoren

reciever.cpp : De samengestelde bericht van de ESP32 wordt hier ontleed en gefilterd aan de hand van de commando wat het binnenkrijgt

NetworkProgramming.ino : Hier zit de code in van de ESP32 voor 2 sensoren aan te sturen. 1 bericht wordt om de seconden verzonden met 
de data van beide sensoren. Voor 3de sensor gebeurt via andere esp32

