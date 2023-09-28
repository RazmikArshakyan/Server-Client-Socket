#include <iostream>
#include "ClientSocket.h"

int main() {
    const int port = 8080;
    ClientSocket client("127.0.0.1", port);

    if (client.Init() && client.Connect()) {
        const char* client_message = "Hello from client";
        if (client.Send(client_message, strlen(client_message)) != SOCKET_ERROR) {
            char client_buffer[50] = {0};
            int client_val_read = client.Receive(client_buffer, sizeof(client_buffer));
            if (client_val_read != -1) {
                std::cout << "Client received :: " << client_buffer << std::endl;
            }
        }
    }

    client.Close();

    return 0;
}