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

struct Player receivePlayer(int server_socket){
    struct sockaddr_storage client_address;
    socklen_t client_len = sizeof(client_address);
    char read_data[BUFFER_SIZE];

    int bytes_read = recvfrom(server_socket, read_data, sizeof(read_data), 0, (struct sockaddr*)&client_address, &client_len);
    struct Player player;
    // Copiar los valores de client_address y client_len en player.address y player.address_len
    memcpy(&player.address, &client_address, sizeof(client_address));
    player.address_len = client_len;

    // Copiar el nickname desde read_data a player.nickname
    strncpy(player.nickname, read_data, sizeof(player.nickname) - 1);
    player.nickname[sizeof(player.nickname) - 1] = '\0'; // Asegurarse de que la cadena esté terminada con '\0'

    // Asignar valores adecuados a player.playerNum y player.playerPos según tu lógica
    player.playerNum = 0; // Por ejemplo, aquí se inicializa en 0
    player.playerPos = 0; // Por ejemplo, aquí se inicializa en 0

    return player;
}
