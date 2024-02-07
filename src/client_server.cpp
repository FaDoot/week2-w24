// TODO: Update your includes as necessary.

#include "client_server.hpp"
#include <iostream> 
#include <string> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

using namespace std;

void sendOnServer() {
    // TODO: Set up the loopback address and a port to bind the server to.
    int sockfd, newsockfd, portno, n;
    portno = 9999;
    char buffer[255];
    //vars used to store stuff about client and server 
    struct sockaddr_in serv_addr, cli_addr; //gives internet addr
    // TODO: Set up a socket.

    //store size for client addr
    socklen_t clilen; //32 bit data type for 

    // TODO: Bind the socket to the address and port.
    //new socked in sockfd: internet, TCP
    sockfd = socket(AF_INET , SOCK_STREAM, 0);

    if(sockfd < 0){
        printf("Error opening the socket");
    }
    //remove zeros in the addr
    bzero((char *) &serv_addr , sizeof(serv_addr) );

    serv_addr.sin_family = AF_INET; //internet addy
    serv_addr.sin_addr.s_addr = INADDR_ANY; //accept from any ip
    serv_addr.sin_port = htons(portno); //converts the integer port number from the host byte order to network byte order


    if(::bind(sockfd, (struct sockaddr* )&  serv_addr , sizeof(serv_addr)) < 0){
        printf("Binding failed");
    }


    // TODO: Listen on the socket.

    //max num clients  is second arg
    listen(sockfd, 2);
    clilen = sizeof(cli_addr);

    // TODO: Accept a client connection.
        newsockfd = accept(sockfd , (struct sockaddr * ) &cli_addr, &clilen);
    if(newsockfd < 0){
        printf("error on accepting connection");
    }
    // TODO: Send the string "Hail to the Victors!" over the socket.
    // while(true){

    //     bzero(buffer , 255);
    //     n = read(newsockfd, buffer, 255);
    //     if(n < 0)
    //     {
    //         printf("error on reading from client");
    //     }
    //     printf("Client: %s\n", buffer);

    //     bzero(buffer, 255);
    //     fgets(buffer, 255, stdin);

    //     n= write(newsockfd, buffer, strlen(buffer));
    //     if(n < 0){
    //         printf("error with writing");
    //     }
    //     int i = strncmp("Bye", buffer, 3);
    //     if(i == 0){
    //         break; 
    //     }
    // }
    strncpy(buffer, "Hail to the Victors!", sizeof(buffer) - 1);

    write(newsockfd, buffer, strlen(buffer));
    // TODO: Close the sockets.
    close(newsockfd);
    close(sockfd);
    
}

string receiveOnClient() {
    int sockfd, newsockfd, portno, n;
    portno = 9999;
    struct hostent *server; 

    char buffer[255];

    socklen_t clilen;
    // TODO: Set up a socket.

    //vars used to store stuff about client and server 
    struct sockaddr_in serv_addr, cli_addr; //gives internet addr
    

    //new socked in sockfd: internet, TCP
    portno = 9999;
    sockfd = socket(AF_INET , SOCK_STREAM, 0);
    if(sockfd < 0){
        printf("Error opening the socket");
    }

    // TODO: Bind the socket to the address and port.
    server = gethostbyname("127.0.0.1"); //right might need to add port somehwere
    if(server == NULL){
        printf("error: no such host here");
    }
    bzero((char * ) & serv_addr , sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char*)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    while(true)
    {
        if(connect(sockfd, (struct sockaddr *) &serv_addr , sizeof(serv_addr))>= 0){
        //printf("connection failed");
        break;
        }
    }
    

    // while(true){
    //     bzero(buffer, 255);
    //     fgets(buffer, 255, stdin);
    //     n = write(sockfd, buffer, strlen(buffer));
    //     if(n < 0){
    //         printf("writting error");
    //     }
    //     bzero(buffer, 255);
    //     n = read(sockfd, buffer, 255);
    //     if(n < 0){
    //         printf("read error");
    //     }
    //     printf("Server: %s\n", buffer);
    //     int i = strncmp("Bye", buffer, 3);
    //     if(i == 0){
    //         break; 
    //     }
        

    // }
    bzero(buffer, 255);
    read(sockfd, buffer, 255);

    close(sockfd);
    
    // TODO: Set up the address and port of the server to be used for connect().

    // TODO: Set up a socket.

    // TODO: Connect the socket to the server in server.cpp. Loop and retry connecting until success.

    // TODO: Allocate a buffer big enough to hold the string. Receive on the socket.
    /* 
     * NOTE: If you make the buffer big enough and you are using the loopback address,
     *       then you will get the whole string on one recv() call. This does not
     *       apply in general. There is no gaurantee on all bytes being sent or received.
     */ 

    // TODO: Close the socket.

    // TODO: Decode the string and return it.
    return std::string(buffer);
}
