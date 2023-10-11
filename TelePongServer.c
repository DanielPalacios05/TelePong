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

int main()
{

    int server_socket = createServerSocket();

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
        players[numPlayers] = receivePlayer(server_socket);

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

        sendGameInfo(server_socket, players[numPlayers]);
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
