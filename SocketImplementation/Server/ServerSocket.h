#ifndef SERVERSOCKET
#define SERVERSOCKET

#include <winsock2.h>
#include <iostream>

class ServerSocket {
public:
    ServerSocket(int);
    ~ServerSocket();

    bool Init();
    bool Bind();
    bool Listen(int);
    bool Accept();
    int Receive(char*, int);
    bool Send(const char*, int);
    void Close();

private:
    int port;
    SOCKET server_socket;
    struct sockaddr_in server_address;
    SOCKET client_socket;
 
};

#endif