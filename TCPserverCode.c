#include <winsock2.h>
#include <unistd.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//ADD to pro
//LIBS += -lws2_32


int main()
{
    WSADATA wsaData;   // if this doesn't work
    SOCKET s ;
    socklen_t addr_size;

    int new_fd;
    int nbuf = 0;
    int nbuf2 = 0;

    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed.\n");
        exit(1);
    }
    printf("Initialsatie compleet server.\n");


        if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
        {
            printf("Foutmelding , socket werd niet gecreeërd: %d" , WSAGetLastError());
        }

        printf("Socket created.\n");


        struct addrinfo hints, *res;
        struct sockaddr_storage their_addr;
        int sockfd;

        // first, load up address structs with getaddrinfo():

        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_UNSPEC;  // use IPv4 or IPv6, whichever
        hints.ai_socktype = SOCK_STREAM; // TCP
        hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

        printf("Waiting for visitor.\n");
        getaddrinfo(NULL, "24012", &hints, &res);


        sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);


        bind(sockfd, res->ai_addr, res->ai_addrlen);
        listen(sockfd,20);


        addr_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
        printf("Accepting visitor.\n");
        char buffer[256];
        char buffer2[256];
        while(1)
        {
            fgets(buffer,256,stdin);
            nbuf = send( new_fd, buffer , 256 , 0);

            if(nbuf > 0)
            {
              buffer[nbuf] = '/0';
              printf("message : %s \n",buffer);
            }
            memset(buffer , 0 , sizeof buffer);

            nbuf2 = recv( new_fd , buffer2, 256, 0);

             if(nbuf2 > 0)
              {
               buffer[nbuf2] = '/0';
               printf("message : %s \n",buffer2);
               }
               memset(buffer2 , 0 , sizeof buffer2);

        }

        printf("Finished.\n");

        close(sockfd); // kill visitor
        WSACleanup(); // kill client
        return 0;

}
