#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define PORT "8080"




int initialize_socket(){
    struct addrinfo hints;

    memset(&hints,0,sizeof(hints));



    hints.ai_family =AF_INET ;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_socktype = SOCK_DGRAM;



    struct addrinfo *networkInfo;

    getaddrinfo(0,PORT,&hints,&networkInfo);

    int sock = socket(networkInfo->ai_family,networkInfo->ai_socktype,networkInfo->ai_protocol);

    if ( sock < 0){
        printf("problemas con el socket\n");
    }

    printf("bind socket\n");

    if(bind(sock,networkInfo->ai_addr,networkInfo->ai_addrlen)){
        printf("binding failed\n");
        perror("bind");
        return 1;
    }


    freeaddrinfo(networkInfo);


    return sock;

}


int listenForRequests(int sock,char *read_data,struct sockaddr *clientAddress){

    struct sockaddr_storage client_address;

    socklen_t client_len = sizeof(client_address);


  
    int bytes_read = recvfrom(sock,read_data,1024,0,clientAddress,&client_len);

    return bytes_read;
}


