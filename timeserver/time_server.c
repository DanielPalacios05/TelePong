#include <networking.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


int main(){

    struct addrinfo hints;

    memset(&hints,0,sizeof(hints));



    hints.ai_family = AF_INET;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_socktype = SOCK_STREAM;



    struct addrinfo *networkInfo;

    getaddrinfo(0,"8080",&hints,&networkInfo);

    


    char server_address_buffer[100];

    getnameinfo(networkInfo->ai_addr,networkInfo->ai_addrlen,server_address_buffer,sizeof(server_address_buffer),0,0,NI_NUMERICHOST);

    printf("address:%s\n",server_address_buffer);

    printf("tipo de socket=%d %d\n",networkInfo->ai_protocol,networkInfo->ai_socktype);
    

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


    printf("listening now\n");


    if(listen(sock,2)){
        fprintf(stderr,"listening failed lolololol\n");
        return 1;
    }

    printf("now waiting fo a nigga....\n");

    struct sockaddr_storage client_address;

    socklen_t client_len = sizeof(client_address);
    
    int socket_client = accept(sock, (struct sockaddr*) &client_address,&client_len);

    if(socket_client < 0){
        printf("socket connection did not go well\n");
    }


    printf("some random mf connected\n");


    char address_buffer[100];

    getnameinfo((struct sockaddr*) &client_address,client_len,address_buffer,sizeof(address_buffer),0,0,NI_NUMERICHOST);

    printf("%s\n",address_buffer);


    printf("Reading request...\n");
    char request[1024];
    int bytes_received = recv(socket_client, request, 1024, 0);
    printf("Received %d bytes.\n", bytes_received);

    printf("received %s\n",request);



    time_t timer;
    time(&timer);
    char *time_msg = ctime(&timer);
    int bytes_sent = send(socket_client, time_msg, strlen(time_msg), 0);
    printf("Sent %d of %d bytes.\n", bytes_sent, (int)strlen(time_msg));


    close(socket_client);
    close(sock);

    


    return 0;
}