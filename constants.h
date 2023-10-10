#ifndef CONSTANTS_H  // Evita la inclusión múltiple
#define CONSTANTS_H
#include <sys/socket.h>

struct Player {
    struct sockaddr_storage address;
    socklen_t address_len;
    char nickname[15];
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

#define MAX_PLAYERS 20
#define PORT 8080
#define BUFFER_SIZE 1024

#endif  // CONSTANTS_H