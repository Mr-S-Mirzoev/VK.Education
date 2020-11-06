#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

#include "server.hpp"
#include "exceptions.hpp"

int BindCreatedSocket(int hSocket)
{ 
/*
    int iRetval=-1;
    int ClientPort = 60606;
    ::sockaddr_in  remote = {0};
    // Internet address family 
    remote.sin_family = AF_INET;
    // Any incoming interface 
    remote.sin_addr.s_addr = htonl(INADDR_ANY);
    remote.sin_port = htons(ClientPort); // Local port 
    iRetval = bind(hSocket,(struct sockaddr *)&remote,sizeof(remote));
 
    return iRetval;
*/

    uint16_t _port = 60606;
    ::sockaddr_in remote = tcp::any_address(_port).get_struct();
    int ret = ::bind(hSocket, 
                reinterpret_cast<sockaddr*> (&remote), 
                sizeof(remote));
    if (ret < 0)
        throw tcp::ServerBindError(_port);

    return ret;

}

int main(int argc, char *argv[])
{
    int socket_desc, sock, clientLen, read_size;
    struct sockaddr_in server, client;
    char client_message[200]= {0};
    char message[100] = {0};
    const char *pMessage = "Hello, Server";
    //Create socket
    tcp::Descriptor socket = tcp::create_inet4_socket();
    std::cout << "Socket object initialised" << std::endl;
    try {
        socket_desc = socket.get_fd();
        std::cout << "Socket created" << std::endl;
        //Bind
        if( BindCreatedSocket(socket.get_fd()) < 0)
        {
            //print the error message
            std::cerr << "bind failed." << std::endl;
            return 1;
        }
        std::cout << "bind done" << std::endl;
        //Listen
        listen(socket.get_fd(), 3);
        //Accept and incoming connection
        while(1)
        {
            std::cout << "Waiting for incoming connections..." << std::endl;
            clientLen = sizeof(struct sockaddr_in);
            //accept connection from an incoming client
            sock = accept(socket.get_fd(),(struct sockaddr *)&client,(socklen_t*)&clientLen);
            if (sock < 0)
            {
                std::cerr << "accept failed" << std::endl;
                return 1;
            }
            std::cout << "Connection accepted" << std::endl;
            memset(client_message, '\0', sizeof client_message);
            memset(message, '\0', sizeof message);
            //Receive a reply from the client
            if( recv(sock, client_message, 200, 0) < 0)
            {
                std::cerr << "recv failed" << std::endl;
                break;
            }
            std::cout << "Client reply : " << client_message << std::endl;
            if(strcmp(pMessage,client_message)==0)
            {
                strcpy(message,"Hi there !");
            }
            else
            {
                strcpy(message,"Invalid Message !");
            }
            // Send some data
            if( send(sock, message, strlen(message), 0) < 0)
            {
                std::cerr << "Send failed" << std::endl;
                return 1;
            }
            close(sock);
            sleep(1);
        }
    } catch (tcp::BadDescriptorUsed &bdu) {
        std::cerr << "Could not create socket" << std::endl;
        std::cerr << bdu.what() << std::endl;
        return 1;
    }
    return 0;
}