#include <zmq.hpp>
#include <string>
#include <iostream>

using namespace std;

int main ()
{
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REQ);
	
	string geefin ;
	const void * a = nullptr;

    cout << "Welkom bij project netwerken" <<endl;
    socket.connect ("tcp://localhost:5555");
	//socket.connect ("tcp://192.168.0.54:80");
	
	cout << "Geef aan in voor werkende ventilator" << endl;
	cout << "Geef uit in voor de ventilator stil te zetten" << endl;
	
    //  Do 10 requests, waiting each time for a response
     while (true) {
		 
		cin >> geefin;
		a = geefin.c_str();
        zmq::message_t request (3);
        memcpy (request.data (), a , 3);
		
		
		string rp1 = std::string(static_cast<char*>(request.data()), request.size());
		cout << "Sending "<< rp1 <<endl;
        socket.send (request);

        //  Get the reply.
        zmq::message_t reply;
        socket.recv (&reply);
		
	    string rp2 = std::string(static_cast<char*>(reply.data()), reply.size());
		cout << "Recieved "<< rp2 << endl;
        
    }
    return 0;
}