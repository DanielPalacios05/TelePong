#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

int createClientSocket(){
    int client_socket;
    struct sockaddr_in server_address;

    // Crear un socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error al crear el socket");
        exit(EXIT_FAILURE);
    }
    return client_socket;
}

int createServerSocket(){
    int server_socket; 
    struct sockaddr_in servaddr;  
    // socket create and verification
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");

    bzero(&servaddr, sizeof(servaddr));
   
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(50000);
   
    // Binding newly created socket to given IP and verification
    if ((bind(server_socket, (struct sockaddr*)&servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");
    
    // Now server is ready to listen and verification
    if ((listen(server_socket, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");

    return server_socket;
}

int acceptNewClients(int server_socket){
    int new_socket, len;
    struct sockaddr_in cli;
    
    len = sizeof(cli);
   
    // Accept the data packet from client and verification
    new_socket = accept(server_socket, (struct sockaddr *)&cli, &len);
    if (new_socket < 0) {
        printf("server accept failed...\n");
        exit(0);
    }
    else
        printf("server accept the client...\n");
    

    return new_socket;
}
