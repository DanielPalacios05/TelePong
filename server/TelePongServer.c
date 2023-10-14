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
#include "utils.c"


void handle_request(int sock,struct request *req){
    
    char copyString[REQUESTSIZE];
    strcpy(copyString,(req->body));
    //printf("data from %s: %s\n",&req,copyString);
    char *ptr;
    char* tempPr = copyString;

    ptr = strtok_r(tempPr," ",&tempPr);

    printf("%s\n",ptr);
    
}


void* threadBody(void* args){

    
    struct Response *response_ptr = (struct Response *)args;
    struct Response response;
    response = handleCommunication(response_ptr->msg);

    char token[100];
    strcpy(token, players[0].addressText);
    char *colon_position = strchr(token, ':');
    *colon_position = '\0'; // Reemplazar ':' por un carácter nulo

    char *ip_str = token;
    char *port_str = colon_position + 1;


    char logString[500];
    //concat(logString,5, &addressBuffer," ",&portBuffer,": ",requestArgs->request.body);    

    //logToFile(logger,logString);

    //handle_request(requestArgs->sock,&requestArgs->request);

    //free(requestArgs);


    pthread_exit(NULL);
}



void hola(){
    char token[100];
    strcpy(token, players[0].addressText);
    char *colon_position = strchr(token, ':');
    *colon_position = '\0'; // Reemplazar ':' por un carácter nulo

    char *ip_str = token;
    char *port_str = colon_position + 1;
    printf("IP: %s - PORT: %s - NAME: %s\n", ip_str, port_str, players[0].nickname);
}


int main()
{
    struct Response response;
    response = handleCommunication("SERVER CREATE_SOCKET");
    int server_socket = response.server_socket;
    char server_socketStr[20]; 
    snprintf(server_socketStr, sizeof(server_socketStr), "%d", server_socket);
    response.server_socket = 0;
    char message[100];

    printf("Waiting for players to connect...\n");

    int numPlayers = 0;
    int gamePos = 0;

    for (int i = 0; i < (MAX_PLAYERS / 2); i++)
    {
        games[i].totalNumPlayers = 0;
    }

fr:
    strcpy(message, "SERVER LISTEN_MSG ");
    concat(message, 1, server_socketStr);
    response = handleCommunication(message);
    
    if(strcmp(response.msg, "SERVER INIT_PLAYER") == 0){
        printf("Mensaje ::::  %s \n", response.msg);
        if (numPlayers < MAX_PLAYERS)
        {
            memset(&response.player, 0, sizeof(struct Player)); // Asigna ceros a la estructura Player
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
            
            char numPlayerText[2];
            convertInt2Char(players[numPlayers].playerNum, numPlayerText, sizeof(numPlayerText));
            printf(" Player num INT  %d", players[numPlayers].playerNum);
            char gameIdText[4];
            convertInt2Char(players[numPlayers].gameId, gameIdText, sizeof(gameIdText));
            strcpy(message, "SERVER GAME_INFO ");
            concat(message, 7, server_socketStr, " ", numPlayerText, " ", gameIdText, " ", players[numPlayers].addressText);
            printf("Mensaje =>>   %s   ",message);

            handleCommunication(message);
            printf("Gamepos ... %d || ", gamePos);
            if (players[numPlayers].playerNum == 2)
            {   
                strcpy(message, "PLAYER SEND_OPP ");
                concat(message, 5, server_socketStr, " ", games[gamePos].player2.nickname, " ", games[gamePos].player1.addressText);
                printf("Mensaje =>>   %s   ",message);
                handleCommunication(message);
                //sendOpponent(server_socket, games[gamePos].player2.nickname, games[gamePos].player1);

                strcpy(message, "PLAYER SEND_OPP ");
                concat(message, 5, server_socketStr, " ", games[gamePos].player1.nickname, " ", games[gamePos].player2.addressText);
                printf("Mensaje =>>   %s   ",message);
                handleCommunication(message);
                //sendOpponent(server_socket, games[gamePos].player1.nickname, games[gamePos].player2);
            }

            printf("Player %s connected.\n", players[numPlayers].nickname);
            hola();
            
            ++numPlayers;
        }
    }else{

        
        strcpy(response.serverSocketStr, server_socketStr);
        struct Response *response_ptr = &response; // Obtén un puntero a la estructura
        pthread_t tid;
        pthread_create(&tid, NULL, threadBody, (void *)response_ptr);

    }
    goto fr;
}

