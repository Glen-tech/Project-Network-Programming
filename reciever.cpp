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
    zmq::context_t context(1);
    zmq::socket_t sub (context, ZMQ_SUB);
	
	int command = 0;
	
	sub.connect("tcp://benternet.pxl-ea-ict.be:24042");
	
	const char *command1 = "1";
	const char *command2 = "2";
	
	const char *filter  =  "Lage temperatuur , rond de 20 graden";
	const char *filter2 =  "Hoge temperatuur , rond de 22 graden";
	const char *filter3 =  "Ventilator staat uit";
	const char *filter4 =  "Ventilator staat aan , boven 26 graden";
	const char *test =  "test";

    sub.setsockopt(ZMQ_SUBSCRIBE, command1, strlen(command1));
	sub.setsockopt(ZMQ_SUBSCRIBE, command2, strlen(command2));
	
	sub.setsockopt(ZMQ_SUBSCRIBE, filter,  strlen(filter));
	sub.setsockopt(ZMQ_SUBSCRIBE, filter2, strlen(filter2));
	sub.setsockopt(ZMQ_SUBSCRIBE, filter3, strlen(filter3));
	sub.setsockopt(ZMQ_SUBSCRIBE, filter4, strlen(filter4));
	sub.setsockopt(ZMQ_SUBSCRIBE, test, strlen(test));


     while (true) 
	 {
          zmq::message_t reply;
          sub.recv(&reply);
	      string rp = std::string(static_cast<char*>(reply.data()), reply.size());
		  
		  if(rp == "1")
		  {
			  command = 1;
		  }
				  else if(rp == "2")
				  {
					  command = 2;
				  }
		  switch(command)
		  {
			  case 1:  if(rp == "1"){cout <<"Commando Temperatuur ontvangen" << endl;}
			           else{cout << "Temperatuur>" << rp << ">" << endl; }
					   break;
			  case 2:  if(rp == "2"){cout <<"Commando Licht ontvangen"<< endl;}
			           else{
							if(command == 2 && rp == test){cout << "Licht>" << rp << ">" << endl;}	
						   }
					   break;
		      default:	cout << "Fail>Probeer opnieuw>"<< endl; break;		  
		  }
		  
		  sleep(1);
    }
    return 0;
}
