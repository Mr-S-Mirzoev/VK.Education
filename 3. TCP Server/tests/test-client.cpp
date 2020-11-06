#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "connection.hpp"
#include "exceptions.hpp"
#include <iostream>

//try to connect with server
int SocketConnect(int hSocket, char *ServerAddress, int ServerPort)
{
    int iRetval=-1;
    struct sockaddr_in remote= {0};
    remote.sin_addr.s_addr = inet_addr(ServerAddress); //Local Host
    remote.sin_family = AF_INET;
    remote.sin_port = htons(ServerPort);
    iRetval = connect(hSocket,(struct sockaddr *)&remote,sizeof(struct sockaddr_in));
    return iRetval;
}
// Send the data to the server and set the timeout of 20 seconds
int SocketSend(int hSocket,char* Rqst,short lenRqst)
{
    int shortRetval = -1;
    struct timeval tv;
    tv.tv_sec = 20;  /* 20 Secs Timeout */
    tv.tv_usec = 0;
    if(setsockopt(hSocket,SOL_SOCKET,SO_SNDTIMEO,(char *)&tv,sizeof(tv)) < 0)
    {
        printf("Time Out\n");
        return -1;
    }
    shortRetval = send(hSocket, Rqst, lenRqst, 0);
    return shortRetval;
}
//receive the data from the server
int SocketReceive(int hSocket,char* Rsp,short RvcSize)
{
    int shortRetval = -1;
    struct timeval tv;
    tv.tv_sec = 20;  /* 20 Secs Timeout */
    tv.tv_usec = 0;
    if(setsockopt(hSocket, SOL_SOCKET, SO_RCVTIMEO,(char *)&tv,sizeof(tv)) < 0)
    {
        printf("Time Out\n");
        return -1;
    }
    shortRetval = recv(hSocket, Rsp, RvcSize, 0);
    printf("Response %s\n", Rsp);
    return shortRetval;
}
//main driver program
int main(int argc, char *argv[])
{
    int hSocket, read_size;
    struct sockaddr_in server;
    char SendToServer[100] = {0};
    char server_reply[200] = {0};

    //Create socket
    tcp::Address server_address {"127.0.0.1", DEFAULT_PORT};
    std::cout << "Address created." << std::endl;
    tcp::Descriptor socket = tcp::create_inet4_socket();
    std::cout << "Descriptor created." << std::endl;
    tcp::Connection conn(server_address, std::move(socket));
    std::cout << "Connection established." << std::endl;
    conn.connect(server_address);
    printf("Sucessfully conected with server\n");
    printf("Enter the Message: ");
    fgets(SendToServer, 100, stdin);
    conn.writeExact(SendToServer, strlen(SendToServer));
    //Received the data from the server
    read_size = conn.read(server_reply, 200);
    std::cout << "Got a server reply. Finishing." << std::endl;
    std::cout << server_reply << std::endl;
    return 0;
}