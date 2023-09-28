#ifndef CLIENTSOCKET
#define CLIENTSOCKET

#include <winsock2.h>
#include <iostream>

class ClientSocket {
public:
    ClientSocket(std::string server_ip, int server_port);
    ~ClientSocket();

    bool Init();
    bool Connect();
    int Send(const char*, int);
    int Receive(char*, int);
    void Close();

private:
    std::string server_ip;
    int  server_port;
    SOCKET client_socket;
};

#endif