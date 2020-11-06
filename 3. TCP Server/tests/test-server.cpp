#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <string_view>

#include "server.hpp"
#include "exceptions.hpp"

#define DEFAULT_PORT 60606

int main(int argc, char *argv[])
{
    int socket_desc, sock, clientLen, read_size;
    std::string client_message(200, 0);
    std::string message(200, 0);
    const std::string pMessage = "Hello, Server";

    //Create server
    try {
        tcp::Server server(DEFAULT_PORT, 3);
        std::cout << "Server object initialised, listening..." << std::endl;
        //Accept all incoming connection
        while(1)
        {
            std::cout << "Waiting for incoming connections..." << std::endl;

            //accept connection from an incoming client
            try {
                tcp::Connection conn = server.accept();
                std::cout << "Connection accepted" << std::endl;
                size_t read_bytes;

                try {
                    read_bytes = conn.read(client_message.data(), 200);
                } catch (std::runtime_error &read_err) {
                    std::cerr << "Read failed due to: " << read_err.what() << std::endl;
                }

                std::cout << "Client reply : " << client_message << std::endl;
                if (pMessage == client_message)
                    message = "Hi, there!";
                else
                    message = "Invalid Message. You can greet server with \"Hello, Server\"!";

                try {
                    conn.write(message.data(), message.size());
                } catch (std::runtime_error &write_err) {
                    std::cerr << "Write failed due to: " << write_err.what() << std::endl;
                }
            } catch (tcp::ServerAcceptError &acp) {
                std::cout << "Failed to accpet client: " << acp.what() << std::endl;
            } catch (std::exception &excp) {
                std::cout << "Communication with client failed: " << excp.what() << std::endl;
            }

            ::sleep(1);
        }
    } catch (tcp::BadDescriptorUsed &bdu) {
        std::cerr << "Could not create socket" << std::endl;
        std::cerr << bdu.what() << std::endl;
        return 1;
    } catch (tcp::ServerBindError &bnd) {
        std::cerr << "Could not bind socket to designated port" << std::endl;
        std::cerr << bnd.what() << std::endl;
    } catch (tcp::ServerListenError &lst) {
        std::cerr << "Could not listen through the created socket" << std::endl;
        std::cerr << lst.what() << std::endl;
    }
    return 0;
}