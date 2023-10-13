#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "myPongProtocol.c"
#include "constants.h"


char *convertInt2Char(int number){    
    char *text[10];
    int caracteres_escritos = snprintf(*text, sizeof(text), "%d", number);

    if (caracteres_escritos >= sizeof(text)) {
        fprintf(stderr, "Error: desbordamiento de búfer\n");
    }

    return *text;
}

int main()
{
    struct Response response;
    response = handleCommunication("SERVER CREATE_SOCKET");
    int server_socket = response.server_socket;
    char server_socketStr[20]; 
    snprintf(server_socketStr, sizeof(server_socketStr), "%d", server_socket);
    response.server_socket = 0;

    printf("Waiting for players to connect...\n");

    int numPlayers = 0;
    int gamePos = 0;

    for (int i = 0; i < (MAX_PLAYERS / 2); i++)
    {
        games[i].totalNumPlayers = 0;
    }

fr:
    if (numPlayers < MAX_PLAYERS)
    {
        memset(&response.player, 0, sizeof(struct Player)); // Asigna ceros a la estructura Player
        char message[100];
        snprintf(message, sizeof(message), "PLAYER RECEIVE %s", server_socketStr);
        response = handleCommunication(message);
        players[numPlayers] = response.player;

        printf("Player rec: %s || ", players[numPlayers].nickname);

        for (int i = 0; i < (MAX_PLAYERS / 2); i++)
        {
            printf("Paso por for en %d || ", i);
            printf("%d", games[i].totalNumPlayers);
            if (games[i].totalNumPlayers == 0)
            {
                players[numPlayers].playerNum = 1;
                players[numPlayers].playerPos = numPlayers;
                players[numPlayers].gameId = i + 100;
                games[i].gameId = i + 100;
                games[i].gamePos = i;
                games[i].player1 = players[numPlayers];
                games[i].totalNumPlayers++;
                break;
            }
            else if (games[i].totalNumPlayers == 1)
            {
                players[numPlayers].playerNum = 2;
                players[numPlayers].playerPos = numPlayers;
                players[numPlayers].gameId = i + 100;
                games[i].player2 = players[numPlayers];
                games[i].totalNumPlayers++;
                gamePos = i;
                break;
            }
        }
        
        char numPlayerText[1];
        strcpy(numPlayerText, convertInt2Char(players[numPlayers].playerNum));
        char gameIdText[4];
        strcpy(gameIdText, convertInt2Char(players[numPlayers].gameId));
        message[0] = '\0';
        strcpy(message, "SERVER GAME_INFO ");
        strcat(message, server_socketStr);
        strcat(message, " ");
        strcat(message, numPlayerText);
        strcat(message, " ");
        strcat(message, gameIdText);
        strcat(message, " ");
        strcat(message, response.address);
        printf("Mensaje =>>   %s   ",message);

        handleCommunication(message);
        printf("Gamepos ... %d || ", gamePos);
        if (players[numPlayers].playerNum == 2)
        {
            sendOpponent(server_socket, games[gamePos].player2.nickname, games[gamePos].player1);
            sendOpponent(server_socket, games[gamePos].player1.nickname, games[gamePos].player2);
        }

        printf("Player %s connected.\n", players[numPlayers].nickname);
        ++numPlayers;
    }
    goto fr;
}
