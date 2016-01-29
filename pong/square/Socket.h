#pragma once
#include <iostream>

#include <WinSock2.h>

using namespace std;

//length of communication
const int STRLEN = 4;

//communication logic
class Socket
{
    protected:
        WSADATA wsaData;
        SOCKET mySocket;
        SOCKET myBackup;
        SOCKET acceptSocket;
        sockaddr_in myAddress;
    public:
        Socket();
        ~Socket();
        bool SendData( char* );
        bool RecvData( char*, int );
        void CloseConnection();
        void GetAndSendMessage(char* movement);
};

//establishing a server
class ServerSocket : public Socket
{
    public:
        void Listen();
        void Bind( int port );
        void StartHosting( int port );
};


//establishing a client connection
class ClientSocket : public Socket
{
    public:
        void ConnectToServer( const char *ipAddress, int port );
};