H:regional_indicator_a: :regional_indicator_r: :regional_indicator_d: :regional_indicator_w: :regional_indicator_a: :regional_indicator_r: :regional_indicator_e:   :regional_indicator_o: :regional_indicator_v: :regional_indicator_e: :regional_indicator_r:   :regional_indicator_t: :regional_indicator_h: :regional_indicator_e:   :regional_indicator_i: :regional_indicator_n: :regional_indicator_t: :regional_indicator_e: :regional_indicator_r: :regional_indicator_n: :regional_indicator_e: :regional_indicator_t: 


In this project , the data of the sensors is read by a esp32. This is send with the TCP protocol to a broker. The laptop as client can give commando's to filter the data that comes over the internet. This with the zeromq library.

client.cpp : Here the user can give commando's for filtering of sensor data of 2 diffrent sensors.

reciever.cpp : The parsed message will be disected and filters , this depends on with commando it recieves

NetworkProgramming.ino : Here is the code of the ESP32 for reading the data sensors + communication to the broker. 
