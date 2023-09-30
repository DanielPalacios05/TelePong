#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 12345

void error(char *message) {
    perror(message);
    exit(1);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        error("Error creating socket");
    }

    // Setup server address struct
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket to IP and port
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        error("Error binding socket");
    }

    // Listen for incoming connections
    if (listen(server_socket, 2) == -1) {
        error("Error listening for connections");
    }

    printf("Server listening on port %d\n", PORT);

    // Accept client connections
    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
    if (client_socket == -1) {
        error("Error accepting client connection");
    }

    printf("Client connected\n");

    // Main loop for communication
    while (1) {
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));

        // Receive data from client
        int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) {
            error("Error receiving data from client");
        }

        // Print received message
        printf("Received move made by the client: %s\n", buffer);

        // Process received data (implement game logic here)
        // ...

        // Send updated game state back to client
        char game_state[] = "Paddle1X Paddle1Y Paddle2X Paddle2Y BallX BallY";
        if (send(client_socket, game_state, sizeof(game_state), 0) == -1) {
            error("Error sending data to client");
        }
    }

    // Close sockets
    close(client_socket);
    close(server_socket);

    return 0;
}
