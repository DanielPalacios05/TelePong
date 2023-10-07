#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <pthread.h>


void* thread_body(void* arg) {
    printf("Hello from a thread!\n");

    return NULL;

}

void initializeMainSock(){
      struct addrinfo hints;
      
      memset(&hints,0,sizeof(hints));



    hints.ai_family = AF_INET;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_socktype = SOCK_DGRAM;



    struct addrinfo *networkInfo;

    getaddrinfo(0,"8080",&hints,&networkInfo);

    


    char server_address_buffer[100];

    getnameinfo(networkInfo->ai_addr,networkInfo->ai_addrlen,server_address_buffer,sizeof(server_address_buffer),0,0,NI_NUMERICHOST);

    printf("address:%s\n",server_address_buffer);

    

 
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


}


int main(){


    while (true){


    }

}