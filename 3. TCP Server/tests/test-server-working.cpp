#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

#include "socket.hpp"
#include "exceptions.hpp"

int BindCreatedSocket(int hSocket)
{
    int iRetval=-1;
    int ClientPort = 60606;
    struct sockaddr_in  remote= {0};
    /* Internet address family */
    remote.sin_family = AF_INET;
    /* Any incoming interface */
    remote.sin_addr.s_addr = htonl(INADDR_ANY);
    remote.sin_port = htons(ClientPort); /* Local port */
    iRetval = bind(hSocket,(struct sockaddr *)&remote,sizeof(remote));
    return iRetval;
}

int main(int argc, char *argv[])
{
    int socket_desc, sock, clientLen, read_size;
    struct sockaddr_in server, client;
    char client_message[200]= {0};
    char message[100] = {0};
    const char *pMessage = "Hello, Server";
    //Create socket
    tcp::Socket socket;
    std::cout << "Socket object initialised" << std::endl;
    try {
        socket_desc = socket.get_fd();
    } catch (tcp::BadDescriptorUsed &bdu) {
        std::cerr << "Could not create socket" << std::endl;
        std::cerr << bdu.what() << std::endl;
        return 1;
    }
    std::cout << "Socket created" << std::endl;
    //Bind
    if( BindCreatedSocket(socket_desc) < 0)
    {
        //print the error message
        std::cerr << "bind failed." << std::endl;
        return 1;
    }
    std::cout << "bind done" << std::endl;
    //Listen
    listen(socket_desc, 3);
    //Accept and incoming connection
    while(1)
    {
        std::cout << "Waiting for incoming connections..." << std::endl;
        clientLen = sizeof(struct sockaddr_in);
        //accept connection from an incoming client
        sock = accept(socket_desc,(struct sockaddr *)&client,(socklen_t*)&clientLen);
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
    return 0;
}