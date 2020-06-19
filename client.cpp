#include <zmq.hpp>
#include <string>
#include <iostream>

#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>

#define sleep(n)    Sleep(n)
#endif
using namespace std;

int main ()
{
    //  Prepare our context and socket
    zmq::context_t context(1);
    zmq::socket_t push (context,ZMQ_PUSH);
	push.connect("tcp://benternet.pxl-ea-ict.be:24041");
	
	zmq::socket_t sub (context, ZMQ_SUB);
	sub.connect("tcp://benternet.pxl-ea-ict.be:24042");

    cout << "Welkom bij project netwerken" <<endl;
	char geefin[50];
	cout << "Geef Data>ESPbureau>temp> voor temperatuur van de bureau " << endl;
	cout << "Geef Data>ESPbureau>licht> in voor het licht in de bureau " <<endl;
	cout << "Geef Data>AllData>ESP> in voor alla data te ontvangen" << endl;
	
	const char *filter  = "Temperatuur>Delta>Bureau";

	sub.setsockopt(ZMQ_SUBSCRIBE, filter,  strlen(filter));
	
     while (true) 
	 {
		cin.getline(geefin,sizeof(geefin));
		zmq::message_t request (strlen(geefin));
		memcpy (request.data(), &geefin,strlen(geefin));
		
        push.send(request);
		string rp2 = std::string(static_cast<char*>(request.data()), request.size());
        sleep(1);
		
		memcpy (geefin,"",50); 
		
				
		zmq::message_t delta;
        sub.recv(&delta);
	    string data  = std::string(static_cast<char*>(delta.data()), delta.size());	
		cout << data << endl;	
		
        
     }
    return 0;
}