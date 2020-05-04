#include <winsock2.h>
#include <unistd.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>


void *recieving(void *value)
{
    int nbuf = 0;
    char buffer[256];

    int *socking = (int *) value;

    nbuf = recv(*socking, buffer, 256, 0);

    while(1)
    {
         if(nbuf > 0)
          {
           buffer[nbuf] = '/0';
           printf("receiving from server: %s \n",buffer);
           }
           memset(buffer , 0 , sizeof buffer);
    }

    return NULL;
}

void *sending(void *value)
{
    int nbuf = 0;
    char buffer[256];
    int *sock = (int *) value;

    fgets(buffer,256,stdin);
    nbuf = send(*sock, buffer , 256 , 0);

   while(1)
   {
        if(nbuf > 0)
        {
          buffer[nbuf] = '/0';
          printf("sending to server : %s \n",buffer);
          memset(buffer , 0 , sizeof buffer);
        }
    }

    return NULL;

}

int main()
{
    WSADATA wsaData;   // if this doesn't work
    SOCKET s ;
    char buffer[256];
    int sockfd;
    int sock;
    int nbuf = 0;

    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed.\n");
        exit(1);
    }
    printf("Initialsatie compleet client.\n");


        if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
        {
            printf("Foutmelding , socket werd niet gecreeërd: %d" , WSAGetLastError());
        }

        printf("Socket created.\n");


        struct addrinfo hints, *res;
        // first, load up address structs with getaddrinfo():
        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_UNSPEC;  // use IPv4 or IPv6, whichever
        hints.ai_socktype = SOCK_STREAM; // TCP
        hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

        //getaddrinfo("84.195.204.121", "24012", &hints, &res);
        //getaddrinfo("192.168.0.102", "24012", &hints, &res);
        getaddrinfo("192.168.1.171", "24012", &hints, &res);

        // make a socket:

        sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        connect(sockfd, res->ai_addr, res->ai_addrlen);

        pthread_t thread;
        pthread_t recieve;

              pthread_create(&thread , NULL , sending , &sockfd);
              pthread_create(&recieve, NULL , recieving , &sockfd);
              pthread_join(thread , NULL);
              pthread_join(recieve , NULL);

         WSACleanup(); // kill client

        return 0;

}