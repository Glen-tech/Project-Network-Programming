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
	
	const char *command1 = "1";
	const char *command2 = "2";
	const char *command3 = "3";
	
	const char *filter  = "Temperatuur>Bureau";
	const char *filter2 = "Licht>Bureau";
	const char *filter3 = "Temperatuur>Living";
	
	string findTemp;
	string findLight;

    sub.setsockopt(ZMQ_SUBSCRIBE, command1, strlen(command1));
	sub.setsockopt(ZMQ_SUBSCRIBE, command2, strlen(command2));
	sub.setsockopt(ZMQ_SUBSCRIBE, command3, strlen(command3));
	
	sub.setsockopt(ZMQ_SUBSCRIBE, filter,  strlen(filter));
	sub.setsockopt(ZMQ_SUBSCRIBE, filter2, strlen(filter2));
	sub.setsockopt(ZMQ_SUBSCRIBE, filter3, strlen(filter3));
	
     while (true) 
	 {
          zmq::message_t reply;
          sub.recv(&reply);
	      string rp = std::string(static_cast<char*>(reply.data()), reply.size());
		  
		  vector<string> result; 
		  char Store[50];
		
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
		  
		  if(rp == "1")
		  {
			  command = 1;
		  }
				  else if(rp == "2")
				  {
					  command = 2;
				  }
				  
				  else if(rp == "3")
				  {
					  command = 3;
				  }
				  
				  
		  switch(command)
		  {
			  case 1:  if(rp == "1"){cout <<"Commando>1>Commando temperatuur bureau ontvangen>" << endl;}
			           else{
						   if(command == 1 && findTemp != " " ){cout << findTemp << ">" << endl;}	
						   }
					   break;
			  case 2:  if(rp == "2"){cout <<"Commando>2>Commando licht bureau ontvangen>"<< endl;}
			           else{
							if(command == 2 && findLight != " " ){cout << findLight << ">" << endl;}	
						   }
					   break;
					   
		      case 3:  if(rp == "3"){cout <<"Commando>3>Commando temperatuur living ontvangen>"<< endl;
									 cout << "Temperatuur>Living>In Productie>" << ">" << endl;	}
			           else{
						if(command == 3){cout << "Temperatuur>Living>In Productie>" << ">" << endl;}	
						 }
					   break;
		      default:	cout << "Fail>Geef een commando in>"<< endl;break;		  
		  }
		  
		  sleep(1);
    }
    return 0;
}
