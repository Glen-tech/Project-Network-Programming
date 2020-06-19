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

#include <algorithm>
#include <iterator>
#include <vector>


using namespace std;

int main () {
  //  Prepare our context and socket
    
	zmq::context_t context(1);
	zmq::context_t context2(1);
	
	zmq::socket_t push (context2,ZMQ_PUSH);
    zmq::socket_t sub (context, ZMQ_SUB);
	
	push.connect("tcp://benternet.pxl-ea-ict.be:24041");
    sub.connect("tcp://benternet.pxl-ea-ict.be:24042");
	
	int command = 0;
	char *arrayHoudtBij[6];
	int arrayTemp1 = 0;
	int arrayTemp2 = 0;
	
	char *temp ;
	int verschil = 0;
	int caseBepaal = 0;
	int testemp = 0;
	const char* tosend = 0;
	
	const char *filter  = "Temperatuur>Bureau";
	const char *filter2 = "Licht>Bureau";
	
	const char *filter3 = "Data>ESPbureau>temp>";
	const char *filter4 = "Data>ESPbureau>licht>";
	const char *filter5 = "Data>AllData>ESP>";
	
	string findTemp;
	string findLight;	
	string token;
	
	string uitkomst;	
	string delta = "Temperatuur>Delta>Bureau>";	
	string sending;
	
	
	sub.setsockopt(ZMQ_SUBSCRIBE, filter,  strlen(filter));
	sub.setsockopt(ZMQ_SUBSCRIBE, filter2, strlen(filter2));
	sub.setsockopt(ZMQ_SUBSCRIBE, filter3, strlen(filter3));	
	sub.setsockopt(ZMQ_SUBSCRIBE, filter4, strlen(filter4));
	sub.setsockopt(ZMQ_SUBSCRIBE, filter5, strlen(filter5));
	
	
     while (true) 
	 {
          zmq::message_t reply;
          sub.recv(&reply);
	      string rp = std::string(static_cast<char*>(reply.data()), reply.size());
		  string allData = rp;
		  
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
			

          if(rp == "Data>AllData>ESP>")
		  {
			command = 3;
		  }			
		  
				  
		  switch(command)
		  {
			  case 1:  if(rp == "Data>ESPbureau>temp>"){cout <<"Commando>1>Commando temperatuur bureau ontvangen>" << endl;}
			           else{
							   if(command == 1 && findTemp != " " )
							   {
								   cout << findTemp << ">" << endl;
								   int len = findTemp.find(">");
								   string first = findTemp.substr(0, len);	
								   int lengt = sizeof(first);
								   string succes = findTemp.substr(lengt-1, len);
								   cout << succes << endl;
								   cout << testemp << endl;								   								  
								   testemp = stoi(succes);
								   
								   if (testemp != 0)
								   {
								   
									   switch(caseBepaal)
									   {
										   case 0: arrayTemp1 = testemp; 
												   cout << "arrayTemp 1 " << arrayTemp1 ;
												   caseBepaal++;	
										   case 1: arrayTemp2 = testemp; 
												   cout << "arrayTemp 2 " << arrayTemp2 ;
												   caseBepaal++;
										   case 3:
													if(arrayTemp2 > arrayTemp1)
													{
														verschil = arrayTemp2 - arrayTemp1;
														caseBepaal++;
													}
													
													else if(arrayTemp2 < arrayTemp1)
												    {											        
														verschil = arrayTemp1 - arrayTemp2;	
														caseBepaal++;														
													}
													else if(arrayTemp2 == arrayTemp1)
													{
														verschil = 0;
														caseBepaal++;
													}
											case 4:
											cout << "verschil " << verschil << endl;
											uitkomst = to_string(verschil);
											sending = delta+uitkomst;
											tosend = sending.c_str();
											cout<<sending<<endl;											
											
											zmq::message_t request (strlen(tosend));
											memcpy (request.data(), &tosend,strlen(tosend));
											push.send(request);
											
											caseBepaal = 0;	     											
																					 
									   }
								   
								   }
		   
							   }	
						   }
					   break;
			  case 2:  if(rp == "Data>ESPbureau>licht>"){cout <<"Commando>2>Commando licht bureau ontvangen>"<< endl;}
			           else{
							if(command == 2 && findLight != " " ){cout << findLight << ">" << endl;}	
						   }
					   break;
					   
		      case 3:  if(rp == "Data>AllData>ESP>"){cout <<"Commando>3>Commando Alle data ontvangen>"<< endl;}
			           else{
							if(command == 3 && allData != " " ){cout << allData << ">" << endl;}	
						   }
					   break;
					   
		      default:	cout << "Fail>Geef een commando in>"<< endl;break;		  
		  }
		  
		  sleep(1);
    }
    return 0;
}
