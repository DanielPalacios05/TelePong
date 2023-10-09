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

#define MAX_PLAYERS 20

struct Player {
    struct sockaddr_storage address;
    socklen_t address_len;
    int playerNum;
    int playerPos;
};

struct Game {
    char gameId;
    int gamePos;
    struct Player player1;
    struct Player player2;
    int p1Score;
    int p2Score;
};

int main() {
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_socktype = SOCK_DGRAM;

    struct addrinfo *networkInfo;

    getaddrinfo(0, "8080", &hints, &networkInfo);

    char server_address_buffer[100];
    getnameinfo(networkInfo->ai_addr, networkInfo->ai_addrlen, server_address_buffer, sizeof(server_address_buffer), 0, 0, NI_NUMERICHOST);

    printf("Server address: %s\n", server_address_buffer);

    int sock = socket(networkInfo->ai_family, networkInfo->ai_socktype, networkInfo->ai_protocol);

    if (sock < 0) {
        printf("Error creating socket\n");
        return 1;
    }

    printf("Binding socket\n");

    if (bind(sock, networkInfo->ai_addr, networkInfo->ai_addrlen)) {
        printf("Binding failed\n");
        perror("bind");
        return 1;
    }

    freeaddrinfo(networkInfo);

    printf("Waiting for players to connect...\n");

    struct Player players[MAX_PLAYERS];
    struct Game games[MAX_PLAYERS/2];
    int numPlayers = 0;

    fr:

    struct sockaddr_storage client_address;
    socklen_t client_len = sizeof(client_address);
    char read_data[1024];

    int bytes_read = recvfrom(sock, read_data, sizeof(read_data), 0, (struct sockaddr*)&client_address, &client_len);

    int playerIndex = -1;
    for (int i = 0; i < numPlayers; ++i) {
        if (memcmp(&players[i].address, &client_address, sizeof(struct sockaddr_storage)) == 0) {
            playerIndex = i;
            break;
        }
    }

    if (playerIndex == -1 && numPlayers < MAX_PLAYERS) {
        players[numPlayers].address = client_address;
        players[numPlayers].address_len = client_len;
        playerIndex = numPlayers;
        ++numPlayers;
    }

    // Send player number (1 or 2) to the client
    char playerNumber = playerIndex + 1;
    sendto(sock, &playerNumber, sizeof(playerNumber), 0, (struct sockaddr*)&players[playerIndex].address, players[playerIndex].address_len);

    printf("Player %d connected.\n", playerIndex + 1);

    // Forward the opponent's movement to the player
    sendto(sock, read_data, bytes_read, 0, (struct sockaddr*)&players[1 - playerIndex].address, players[1 - playerIndex].address_len);

    memset(read_data, 0, sizeof(read_data));
    goto fr;
}
