#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include "constants.h"

int createClientSocket(){
    int client_socket;
    struct sockaddr_in server_address;

    // Crear un socket
    if ((client_socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("Error al crear el socket");
        exit(EXIT_FAILURE);
    }
    return client_socket;
}

int createServerSocket(){
    int server_socket = socket(AF_INET, SOCK_DGRAM, 0);

    if (server_socket == -1) {
        perror("Error al crear el socket");
    }

    // Configurar la dirección y el puerto en los que se escucharán los datagramas
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT); // Puerto deseado
    server_address.sin_addr.s_addr = INADDR_ANY; // Escuchar en todas las interfaces

    // Vincular el socket a la dirección y puerto
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("Error al vincular el socket");
        close(server_socket); 
    }

    return server_socket;
}
