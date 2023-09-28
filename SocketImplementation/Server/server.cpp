#include <iostream>
#include "ServerSocket.h"

int main() {
    const int port = 8080;
    ServerSocket server(port);

    if (!server.Init() || !server.Bind() || !server.Listen(3)) {
        std::cerr << "Init() failed" << std::endl;
        return -1;
    }
 
    std::cout << "Listening to port" << std::endl;
    if (server.Accept()) {
        char buffer[50] = {0};
        int val_read = server.Receive(buffer, sizeof(buffer));

        if (val_read != -1) {
            std::cout << "Received info :: " << buffer << std::endl; 
            const char* hello = "Hello from server";
            if (server.Send(hello, strlen(hello))) {
                std::cout << "Hello is sent" << std::endl;
            }
        }
    }
    
    return 0;
}