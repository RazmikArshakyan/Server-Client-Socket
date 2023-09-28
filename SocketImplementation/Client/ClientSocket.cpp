#include "ClientSocket.h"

ClientSocket::ClientSocket(std::string server_ip, int server_port)
    : server_ip{server_ip}
    , server_port{server_port}
    , client_socket{INVALID_SOCKET}
{
}

ClientSocket::~ClientSocket()
{
    Close();
}

bool ClientSocket::Init()
{
    WSADATA wd;
    if (WSAStartup(MAKEWORD(2, 2), &wd) != 0) {
        return false;
    }

    return true;
}

bool ClientSocket::Connect()
{
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == INVALID_SOCKET) {
        return false;
    }

    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(server_port);
    server_address.sin_addr.s_addr = inet_addr(server_ip.c_str());

    if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == SOCKET_ERROR) {
        return false;
    }

    return true;
}

int ClientSocket::Send(const char* data, int length)
{
    return send(client_socket, data, length, 0);
}

int ClientSocket::Receive(char* buffer, int buffer_size)
{
    return recv(client_socket, buffer, buffer_size, 0);
}

void ClientSocket::Close()
{
    if (client_socket != INVALID_SOCKET) {
        closesocket(client_socket);
    }
    WSACleanup();
}
