#ifndef CONSTANTS_H  // Evita la inclusión múltiple
#define CONSTANTS_H
#define MAX_PLAYERS 20
#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_ADDR_LEN 100
#define REQUESTSIZE 1024
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
    char serverSocketStr[100];
    char address[200];
    char client_len[100];
    char msg[100];
};

struct address
{
    struct sockaddr addressSock;
    socklen_t client_len;
};


struct request
{
    int bytesAmount;
    char body[REQUESTSIZE];
    struct address clientAddress;   
};

struct Player players[MAX_PLAYERS];
struct Game games[MAX_PLAYERS/2];

#endif  // CONSTANTS_H