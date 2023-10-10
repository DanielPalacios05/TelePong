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
    int gameId = 0;

    fr:
    if (numPlayers < MAX_PLAYERS){
        players[numPlayers] = receivePlayer(server_socket);
        

        for (int i = 0; i < (MAX_PLAYERS/2); i++) {
            if(games[i].totalNumPlayers == 0){
                players[numPlayers].playerNum = 1;
                players[numPlayers].playerPos = numPlayers;
                players[numPlayers].gameId = i+100;
                games[i].gameId = i+100;
                games[i].gamePos = i;
                games[i].player1 = players[numPlayers];
                games[i].totalNumPlayers++;
                break;
            }else if(games[i].totalNumPlayers == 1){
                players[numPlayers].playerNum = 2;
                players[numPlayers].playerPos = numPlayers;
                players[numPlayers].gameId = i+100;
                games[i].player2 = players[numPlayers];
                games[i].totalNumPlayers++;
                break;
            }
        }

        sendGameInfo(server_socket, players[numPlayers]);
        
        printf("Player %s connected.\n", players[numPlayers].nickname);
        ++numPlayers;
        
    }
    goto fr;
}
