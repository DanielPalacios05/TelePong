#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define REQUESTSIZE 1024




struct address
{
    struct sockaddr addressSock;
    socklen_t client_len;
};


struct request
{
    int bytesAmount;
    char body[REQUESTSIZE];
    struct address clientAddress;   
};






int initialize_socket(char *PORT){
    struct addrinfo hints;

    memset(&hints,0,sizeof(hints));



    hints.ai_family =AF_INET ;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_socktype = SOCK_DGRAM;




    struct addrinfo *networkInfo;

    getaddrinfo(NULL,PORT,&hints,&networkInfo);

    int sock = socket(networkInfo->ai_family,networkInfo->ai_socktype,networkInfo->ai_protocol);

    if ( sock < 0){
        printf("problemas con el socket\n");
    }


    if(bind(sock,networkInfo->ai_addr,networkInfo->ai_addrlen)){
        printf("binding failed\n");
        perror("bind");
        return 1;
    }


    freeaddrinfo(networkInfo);


    return sock;

}


struct request listenForRequests(int sock){

    struct request actualRequest;
    struct sockaddr_storage client_address;
    actualRequest.clientAddress.client_len = sizeof(client_address);
  
    int bytes_read = recvfrom(sock,actualRequest.body,REQUESTSIZE,0,&actualRequest.clientAddress.addressSock,&actualRequest.clientAddress.client_len);
    actualRequest.bytesAmount=bytes_read;
    return actualRequest;
}

void sendResponseToUser(struct user *usr,int sock,char* response){
  
    int bytes_read = sendto(sock, response, sizeof(response),0,&usr->userSocket,sizeof(struct sockaddr_storage));
    
}




