#include "myPongProtocol.c"
#include <string.h>
#include <stdlib.h>


void *createGame(){
    while(1){
    }
}


void* main(){

    int server_socket = createServerSocket();

    while(1){
        int new_socket = acceptNewClients(server_socket);

        // Crear un nuevo hilo para manejar al cliente
        pthread_t thread;
        int *client_socket = malloc(sizeof(int));
        *client_socket = new_socket;

        if (pthread_create(&thread, NULL, createGame, (void *)client_socket) < 0) {
            perror("Error al crear el hilo");
            free(client_socket);
            close(new_socket);
        }
    }
}