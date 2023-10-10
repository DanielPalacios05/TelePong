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
#include "myPongProtocol.c"
#include "constants.h"

int main() {

    int server_socket = createServerSocket();

    printf("Waiting for players to connect...\n");

    struct Player players[MAX_PLAYERS];
    struct Game games[MAX_PLAYERS/2];
    int numPlayers = 0;

    fr:

    players[0] = receivePlayer(server_socket);

    if (playerIndex == -1 && numPlayers < MAX_PLAYERS) {
        players[numPlayers].address = client_address;
        players[numPlayers].address_len = client_len;
        playerIndex = numPlayers;
        ++numPlayers;
    }

    // Send player number (1 or 2) to the client
    char playerNumber = playerIndex + 1;
    sendto(server_socket, &playerNumber, sizeof(playerNumber), 0, (struct sockaddr*)&players[playerIndex].address, players[playerIndex].address_len);

    printf("Player %d connected.\n", playerIndex + 1);

    // Forward the opponent's movement to the player
    sendto(server_socket, read_data, bytes_read, 0, (struct sockaddr*)&players[1 - playerIndex].address, players[1 - playerIndex].address_len);

    memset(read_data, 0, sizeof(read_data));
    goto fr;
}
