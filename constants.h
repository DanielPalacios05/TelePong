#ifndef CONSTANTS_H  // Evita la inclusión múltiple
#define CONSTANTS_H
#define MAX_PLAYERS 20
#define PORT 8080
#define PORT2 "8080"
#define BUFFER_SIZE 1024
#define MAX_ADDR_LEN 100
#include <sys/socket.h>

struct Player {
    struct sockaddr_storage address;
    socklen_t address_len;
    char nickname[15];
    int playerNum;
    int playerPos;
    int gameId;
    char addressText[200];
    char addressLenText[100];
};

struct Game {
    int gameId;
    int gamePos;
    struct Player player1;
    struct Player player2;
    int p1Score;
    int p2Score;
    int totalNumPlayers;
};

struct Response {
    struct Player player;
    int server_socket;
    char address[200];
    char client_len[100];
};

struct Player players[MAX_PLAYERS];
struct Game games[MAX_PLAYERS/2];

#endif  // CONSTANTS_H