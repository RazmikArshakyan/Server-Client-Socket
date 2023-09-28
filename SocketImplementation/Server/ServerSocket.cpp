#include "ServerSocket.h"

ServerSocket::ServerSocket(int port)
    : port{port}
    , server_socket{INVALID_SOCKET}
    , client_socket{INVALID_SOCKET}
{
    WSADATA wd;
    if (WSAStartup(MAKEWORD(2, 2), &wd) != 0) {
        std::cerr << "WSAStartup() failed" << std::endl;
    }
}

ServerSocket::~ServerSocket()
{
    WSACleanup();
}

bool ServerSocket::Init()
{
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        std::cerr << "socket() failed" << std::endl;
        return false;
    }

    int option{1};
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&option, sizeof(option)) == SOCKET_ERROR) {
        std::cerr << "setsockopt() failed" << std::endl;
        closesocket(server_socket);
        return false;
    }

    return true;
}

bool ServerSocket::Bind()
{
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == SOCKET_ERROR) {
        std::cerr << "bind() failed" << std::endl;
        closesocket(server_socket);
        return false;
    }

    return true;
}

bool ServerSocket::Listen(int backlog)
{
    if (listen(server_socket, backlog) == SOCKET_ERROR) {
        std::cerr << "listen() failed" << std::endl;
        closesocket(server_socket);
        return false;
    }

    return true;
}

bool ServerSocket::Accept()
{
    sockaddr_in new_address;
    int addr_len = sizeof(new_address); 
    client_socket = accept(server_socket, (struct sockaddr*)&new_address, &addr_len);
    if (client_socket == INVALID_SOCKET) {
        std::cerr << "accept() failed" << std::endl;
        closesocket(server_socket);
        return false;
    }

    return true;
}

int ServerSocket::Receive(char* buffer, int buffer_size)
{
    int val_read = recv(client_socket, buffer, buffer_size, 0);
    if (val_read == SOCKET_ERROR) {
        std::cerr << "Receive failed" << std::endl;
        closesocket(client_socket);
        return -1;
    }

    return val_read;
}

bool ServerSocket::Send(const char* data, int length)
{
    int bytes_sent = send(client_socket, data, length, 0);
    if (bytes_sent == SOCKET_ERROR) {
        std::cerr << "send() failed" << std::endl;
        closesocket(client_socket);
        return false;
    }

    return true;
}

void ServerSocket::Close()
{
    closesocket(client_socket);
    closesocket(server_socket);
}
