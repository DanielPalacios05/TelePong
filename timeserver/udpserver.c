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


//socket ip,port, -> bind() -> recvfrom .......... close() 

int main(){

    struct addrinfo hints;

    memset(&hints,0,sizeof(hints));



    hints.ai_family =AF_INET ;
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


    printf("trying to receive data\n");


    fr:



   
 

    struct sockaddr_storage client_address;

    socklen_t client_len = sizeof(client_address);

    char read_data[1024];

  
    int bytes_read = recvfrom(sock,read_data,1024,0,(struct sockaddr*) &client_address,&client_len);



    char address_buffer[100],port_buffer[100];

    getnameinfo((struct sockaddr*) &client_address,client_len,address_buffer,sizeof(address_buffer),port_buffer, sizeof(port_buffer),NI_NUMERICHOST | NI_NUMERICSERV);

    printf("%s %s said: %s \n",address_buffer,port_buffer,read_data);


    memset(read_data, 0, sizeof(read_data));

    goto fr;

    


    return 0;
}