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
#include <thread>

using namespace std;

zmq::context_t context(1);
zmq::socket_t push (context, ZMQ_PUSH);
zmq::socket_t sub (context, ZMQ_SUB);	
zmq::socket_t sub2 (context, ZMQ_SUB);	

string sTemp;
string findTemp;
string findLight;
string rp;
string allData;
string Data;
static int command = 0;	
static int iTemp = 0;

vector<string> result; 
char Store[70];


string FindingTemp(string HotOrNot) // vind de temperatuur waarde uit de string 
{
	size_t posTemp = HotOrNot.find("Ventilator_staat_aan");  
	
		if(posTemp == string::npos)
		{
		   posTemp = HotOrNot.find("Bureau");  
		}
	
	string token = HotOrNot.substr(posTemp); 
	size_t symbol =  token.find(">"); 
	string Temp = token.substr(symbol+1);
	return Temp;
}


void toSend(int temp) // zend de infowaarde door via het benethernet
{
	push.connect("tcp://benternet.pxl-ea-ict.be:24041");
	
	const char *koud =  "Temperatuur>Info>Bureau>koud";
	const char *goed =  "Temperatuur>Info>Bureau>goed";
	const char *warm =  "Temperatuur>Info>Bureau>warm";
	const char *heet =  "Temperatuur>Info>Bureau>heet";
	
	if (temp <= 15)
	{	
		zmq::message_t cold (strlen(koud));
		memcpy (cold.data(),koud,strlen(koud));		
		push.send(cold);		
	}
		else if ( (temp >= 15) &&  (temp <= 25) )
		{
			zmq::message_t good  (strlen(goed));
			memcpy (good.data(), goed,strlen(goed));		
			push.send(good);				
		}
		
		else if ( (temp >= 25) &&  (temp <= 30) )
		{
			zmq::message_t VeryGood (strlen(warm));
			memcpy (VeryGood.data(), warm,strlen(warm));		
			push.send(VeryGood);				
		}
		
		else if ( (temp >= 30) &&  (temp <= 40) )
		{
			zmq::message_t hot (strlen(heet));
			memcpy (hot.data(),heet,strlen(heet));		
			push.send(hot);					
		}
		
			else
			{
				cout << "Welcome to Africa" << endl; 
			}
		
}


void thread_data() // Deze thread ontvangt de waarde van de ESP32
{
	sub.connect("tcp://benternet.pxl-ea-ict.be:24042");
	
	const char *filter  = "Temperatuur>Bureau";
	const char *filter2 = "Licht>Bureau";	
	
	zmq::message_t reply;
	
	sub.setsockopt(ZMQ_SUBSCRIBE, filter,  strlen(filter));
	sub.setsockopt(ZMQ_SUBSCRIBE, filter2, strlen(filter2));
	
	while (true) 
    {	
    sub.recv(&reply);
	rp = std::string(static_cast<char*>(reply.data()), reply.size());
	allData = rp;	
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
	}
	
}

void thread_subsribe() // Deze thread ontvangt de filter van de client.cpp
{
    zmq::message_t recieved;	  		
			
	sub2.connect("tcp://benternet.pxl-ea-ict.be:24042");
	
	const char *filter3 = "Data>ESPbureau>temp>";
	const char *filter4 = "Data>ESPbureau>licht>";
	const char *filter5 = "Data>AllData>ESP>";
	
	sub2.setsockopt(ZMQ_SUBSCRIBE, filter3, strlen(filter3));
	sub2.setsockopt(ZMQ_SUBSCRIBE, filter4, strlen(filter4));
	sub2.setsockopt(ZMQ_SUBSCRIBE, filter5, strlen(filter5));
	
	while(true)
	{		
		zmq::message_t recieved;
		sub2.recv(&recieved);
		Data = std::string(static_cast<char*>(recieved.data()), recieved.size());
		cout << Data << endl;
	}
	
}

void thread_dataHandeling() // Deze thread verwerkt de data van de thread_subsribe()
{	
	while (true) 
	{
		  if(Data == "Data>ESPbureau>temp>")
		  {
			  command = 1;
		  }
		  
		  if(Data == "Data>ESPbureau>licht>")
		  {
			command = 2;
		  }
				  
		  if(Data == "Data>AllData>ESP>")
		  {
			command = 3;
		  }
				  
				  
		  switch(command)
		  {
			  case 1:  if(Data == "Data>ESPbureau>temp>"){cout <<"Commando>1>Commando temperatuur bureau ontvangen>" << endl;}
			             else{
						   if(command == 1 && findTemp != " " )							   
							{
								cout << findTemp << ">" << endl;	
								sTemp = FindingTemp(findTemp);
								iTemp = stoi(sTemp); // omzetten string naar integer
								toSend(iTemp);
							}
						  }				
						  
					   break;
			  case 2:  if(Data == "Data>ESPbureau>licht>"){cout <<"Commando>2>Commando licht bureau ontvangen>"<< endl;}
			           else{
					   if(command == 2 && findLight != " " ){cout << findLight << ">" << endl;}	
					   } 
					   break;
					   
		      case 3:  if(Data == "Data>AllData>ESP>"){cout <<"Commando>3>Commando Alle data ontvangen>"<< endl;}
			           else{
					   if(command == 3 && allData != " " ){cout << allData << ">" << endl;}	
					   }
					   break;
		      default:	cout << "Fail>Geef een commando in>"<< endl;break;		  
		  }
		  
		  Data = ""; // zodat de else in de switch actief wordt
		  sleep(1); 
	 }
}

int main ()
 {
 	thread t1(thread_data);
	thread t2(thread_subsribe);
	thread t3(thread_dataHandeling);
			
	t1.join();
	t2.join();
	t3.join();
	
    return 0;
}