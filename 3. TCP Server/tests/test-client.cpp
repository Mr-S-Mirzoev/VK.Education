#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "socket.hpp"
#include "exceptions.hpp"
#include <iostream>

#define DEFAULT_PORT 90190

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
    tcp::Socket socket;
    std::cout << "Socket object initialised" << std::endl;
    try {
        hSocket = socket.get_fd();
    } catch (tcp::BadDescriptorUsed &bdu) {
        std::cerr << "Could not create socket" << std::endl;
        std::cerr << bdu.what() << std::endl;
        return 1;
    }
    std::cout << "Socket created" << std::endl;
    //Connect to remote server
    if (SocketConnect(hSocket, "127.0.0.1", DEFAULT_PORT) < 0)
    {
        perror("connect failed.\n");
        return 1;
    }
    printf("Sucessfully conected with server\n");
    printf("Enter the Message: ");
    fgets(SendToServer, 100, stdin);
    SendToServer[strlen(SendToServer) - 1] = 0;
    //Send data to the server
    SocketSend(hSocket, SendToServer, strlen(SendToServer));
    //Received the data from the server
    read_size = SocketReceive(hSocket, server_reply, 200);
    printf("Got a server reply. Finishing.\n");
    close(hSocket);
    shutdown(hSocket,0);
    shutdown(hSocket,1);
    shutdown(hSocket,2);
    return 0;
}