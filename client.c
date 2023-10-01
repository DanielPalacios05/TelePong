#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 50000
#define MAX_BUFFER_SIZE 1024

void *main() {
    int socket_fd;
    struct sockaddr_in server_address;

    // Crear un socket
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error al crear el socket");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    // Especificar la dirección IP del servidor
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        perror("Error al convertir la dirección IP");
        exit(EXIT_FAILURE);
    }

    // Conectar al servidor
    if (connect(socket_fd, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Error al conectar al servidor");
        exit(EXIT_FAILURE);
    }
}
