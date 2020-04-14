#include <zmq.hpp>
#include <string>
#include <iostream>

using namespace std;

int main ()
{
    //  Prepare our context and socket
    zmq::context_t context(1);
    zmq::socket_t push (context,ZMQ_PUSH);
	push.connect("tcp://benternet.pxl-ea-ict.be:24041");
	//push.connect ("tcp://localhost:5555");
	
    zmq::socket_t pull (context, ZMQ_PULL);
	pull.connect ("tcp://benternet.pxl-ea-ict.be:24042");
	//pull.connect ("tcp://localhost:5556");
	
	string geefin ;
	const void * a = nullptr;

    cout << "Welkom bij project netwerken" <<endl;
	socket.connect ("tcp://benternet.pxl-ea-ict.be:24041");
    //socket.connect ("tcp://localhost:5555");
	//socket.connect ("tcp://192.168.0.54:80");
	
	cout << "Geef aan in voor werkende ventilator" << endl;
	cout << "Geef uit in voor de ventilator stil te zetten" << endl;
	
    //  Do 10 requests, waiting each time for a response
     while (true) {
		 
		 
		cin >> geefin;
		a = geefin.c_str();
        zmq::message_t request (3);
        memcpy (request.data (), a, 3);
		
		
		string rp1 = std::string(static_cast<char*>(request.data()), request.size());
		cout << "Sending "<< rp1 <<endl;
        push.send(request);

         // Get the reply.
          zmq::message_t reply;
          pull.recv(&reply);
		
	      string rp2 = std::string(static_cast<char*>(reply.data()), reply.size());
		  cout << "Recieved "<< rp2 << endl;
        
    }
    return 0;
}