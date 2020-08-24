#include <zmq.hpp>
#include <string>
#include <iostream>
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>

#define sleep(n)    Sleep(n)
#endif
#include<sstream>
using namespace std;

int main () {
  //  Prepare our context and socket
    zmq::context_t context(1);
    zmq::socket_t sub (context, ZMQ_SUB);

	int command = 0;
	
	sub.connect("tcp://benternet.pxl-ea-ict.be:24042");
	
	const char *filter  = "Temperatuur>Bureau";
	const char *filter2 = "Licht>Bureau";
	const char *filter3 = "Temperatuur>Living";
	
	const char *filter4 = "Data>ESPbureau>temp>";
	const char *filter5 = "Data>ESPbureau>licht>";
	const char *filter6 = "Data>ESPliving>temp>";
	
	
	string findTemp;
	string findLight;
	
	sub.setsockopt(ZMQ_SUBSCRIBE, filter,  strlen(filter));
	sub.setsockopt(ZMQ_SUBSCRIBE, filter2, strlen(filter2));
	sub.setsockopt(ZMQ_SUBSCRIBE, filter3, strlen(filter3));
	
	sub.setsockopt(ZMQ_SUBSCRIBE, filter4, strlen(filter4));
	sub.setsockopt(ZMQ_SUBSCRIBE, filter5, strlen(filter5));
	sub.setsockopt(ZMQ_SUBSCRIBE, filter6, strlen(filter6));
	
     while (true) 
	 {
          zmq::message_t reply;
          sub.recv(&reply);
	      string rp = std::string(static_cast<char*>(reply.data()), reply.size());
		  
		  vector<string> result; 
		  char Store[70];
		
		   istringstream iss(rp);     //object 'iss' created
		   for(int i = 0 ; i < 2 ; i++)
		   {
			   iss >> Store;  
			   if(i == 0)
			   {
				  findTemp = Store; 
			   }
			   else if(i == 1)
			   {
				   findLight= Store;
			   }
		   }
		  
		  if(rp == "Data>ESPbureau>temp>")
		  {
			  command = 1;
		  }
		  
		  if(rp == "Data>ESPbureau>licht>")
		  {
			command = 2;
		  }
				  
		  if(rp == "Data>ESPliving>temp>")
		  {
			command = 3;
		  }
				  
				  
		  switch(command)
		  {
			  case 1:  if(rp == "Data>ESPbureau>temp>"){cout <<"Commando>1>Commando temperatuur bureau ontvangen>" << endl;}
			           else{
						   if(command == 1 && findTemp != " " ){cout << findTemp << ">" << endl;}	
						   }
					   break;
			  case 2:  if(rp == "Data>ESPbureau>licht>"){cout <<"Commando>2>Commando licht bureau ontvangen>"<< endl;}
			           else{
							if(command == 2 && findLight != " " ){cout << findLight << ">" << endl;}	
						   }
					   break;
					   
		      case 3:  if(rp == "Data>ESPliving>temp>"){cout <<"Commando>3>Commando temperatuur living ontvangen>"<< endl;
									 cout << "Temperatuur>Living>In Productie>" << endl;	}
			           //else{
						//if(command == 3){cout << "Temperatuur>Living>In Productie>" << endl;}	
						// }
					   break;
		      default:	cout << "Fail>Geef een commando in>"<< endl;break;		  
		  }
		  
		  sleep(1);
    }
    return 0;
}
