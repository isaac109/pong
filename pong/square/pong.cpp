// square.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GUI.h"
#include <stdio.h>
#include <iostream>
#include "Socket.h"
#include <string>
using namespace std;

int choice;
char recMessage[STRLEN];
char sendMessage[STRLEN];
ClientSocket sockClient;
ServerSocket sockServer;
bool done = false;
char message[4] = "www"; // w's are used as empty messages


void sendKey(char key[])
{
	if(choice == 1)
	{
		sockServer.GetAndSendMessage(key);
	}
	else if(choice == 2)
	{
		sockClient.GetAndSendMessage(key);
	}
}


//a response is taken in depending on server or client. 
void listenForResponse()
{
	if(choice == 1)
	{
            cout<<"\t--WAIT--"<<endl;
            sockServer.RecvData( recMessage, STRLEN );
            cout<<"Recv > "<<recMessage<<endl;
			GUI::special2(recMessage[0]);
            if ( strcmp( recMessage, "end" ) == 0 ||
                    strcmp( sendMessage, "end" ) == 0 )
            {
                done = true;
            }
	}
	else if(choice == 2)
	{    
            cout<<"\t--WAIT--"<<endl;
            sockClient.RecvData( recMessage, STRLEN );
            cout<<"Recv > "<<recMessage<<endl;
			GUI::special2(recMessage[0]);
            if ( strcmp( recMessage, "end" ) == 0 ||
                        strcmp( sendMessage, "end" ) == 0 )
            {
                done = true;
            }        
	}
}

void checkIfEnd()
{
	if(done)
	{
		sockClient.CloseConnection();
	}
}

void getMessage()
{
	for(int i = 0; i < 3; i++)
	{
		message[i] = GUI::GetData().message[i];
	}
}

int _tmain(int argc, char* argv[])
{
	
    int port = 25565;
    string ipAddress;
    cout<<"1) Host server"<<endl;
    cout<<"2) Join server"<<endl;
    cout<<"3) Quit"<<endl;
    cin>>choice;
	if ( choice == 3 )
        exit(0);
    else if ( choice == 2 )
    {
        //Client
        cout<<"Enter an IP address, 127.0.0.1 is the loopback address"<<endl;
        cin >> ipAddress;        
        cout<<"ATTEMPTING TO CONNECT..."<<endl;
        sockClient.ConnectToServer( ipAddress.c_str(), port );
        //Connected
        
    }
    else if ( choice == 1 )
    {
        //SERVER       
        cout<<"HOSTING..."<<endl;
        sockServer.StartHosting( port );
        //Connected
    }

	GUI::initialize(argc, argv, choice == 1); 
	GUI::MutableData().clearMessage();

	//loop of all logic
	while (!done)
	{
		GUI::update();
		getMessage();
		sendKey(message);
		GUI::MutableData().clearMessage();
		checkIfEnd();
		listenForResponse();
	}
	return 0;
}

