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

int main () {
    //  Prepare our context and socket
    zmq::context_t context (1);
	zmq::socket_t pull (context, ZMQ_PULL);
	zmq::socket_t push (context, ZMQ_PUSH);
	pull.bind("tcp://*:24041");
	push.bind("tcp://*:24042");
	//pull.bind("tcp://*:5555");
	//push.bind("tcp://*:5556");
	
    while (true) 
	{
        zmq::message_t request;
		zmq::message_t reply (17);

        //  Wait for next request from client
        pull.recv(&request);
		string rp2 = std::string(static_cast<char*>(request.data()), request.size());
		cout << " Server Recieved "<< rp2 << endl;
        sleep(1);

		
		if (rp2 == "aan")
		{
        memcpy (reply.data (), "Ventilator is aan", 17);
        push.send(reply);
		}
		
			else if (rp2 == "uit")
			{
			memcpy (reply.data (), "Ventilator is uit", 17);
			push.send (reply);
			}
			
			else if(rp2 == "")
			{
			memcpy (reply.data (), "Leeg bericht \n\r", 17);
			push.send (reply);
			}
			
				else
				{
     			memcpy (reply.data (), "Probeer opnieuw \n\r", 17);
				push.send (reply);
				}
	}
		
    return 0;
}
