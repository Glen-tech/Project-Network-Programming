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
    zmq::socket_t socket (context, ZMQ_REP);
    socket.bind ("tcp://*:5555");

    while (true) 
	{
        zmq::message_t request;

        //  Wait for next request from client
        socket.recv (&request);
		string rp2 = std::string(static_cast<char*>(request.data()), request.size());
		cout << " Server Recieved "<< rp2 << endl;

        //  Do some 'work'
        sleep(1);

        //  Send reply back to client
		
		
		if (rp2 == "aan")
		{
        zmq::message_t reply (17);
        memcpy (reply.data (), "Ventilator is aan", 17);
        socket.send (reply);
		}
		
			else if (rp2 == "uit")
			{
			zmq::message_t reply (17);
			memcpy (reply.data (), "Ventilator is uit", 17);
			socket.send (reply);
			}
	}
		
    return 0;
}
