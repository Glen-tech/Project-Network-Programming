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

    cout << "Welkom bij project netwerken" <<endl;
	char geefin[50];
	cout << "Druk 1 voor temperatuur , 2 voor licht"<<endl;
     while (true) 
	 {
	    cin.getline(geefin,sizeof(geefin));
        zmq::message_t request (strlen(geefin));
        memcpy (request.data(), &geefin,strlen(geefin));

        push.send(request);
		string rp2 = std::string(static_cast<char*>(request.data()), request.size());
        sleep(1);
		
		memcpy (geefin,"",50); 
        
     }
    return 0;
}