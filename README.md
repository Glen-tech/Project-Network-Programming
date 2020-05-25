**Hardware control and measurement over the internet.**

The sockets of all the codes uses the TCP protocol , the cpp files uses the zeromq library.

client.cpp : Here the user can give commando's for filtering the data of the ESP32. This data comes from 2 sensors.

reciever.cpp : The parshed message is here disected and vieuwed , this is independent of witch commado is used.

NetworkProgramming.ino : Here in this file is the code of the ESP32. The message is send thanks to the TCP protocol.

