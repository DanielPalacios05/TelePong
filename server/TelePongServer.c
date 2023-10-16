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
#include "logger.c"
char* PORT;
Logger logger;

int numPlayers = 0;
int gamePos = 0;


void handle_request(char *sock, char *msg, struct Player player){
    


    if (strcmp(msg, "UP") == 0 || strcmp(msg, "DOWN") == 0 || strcmp(msg, "NONE") == 0) {

        char temp[200];
        memset(temp,0,200);


        concat(temp, 6, "PLAYER SEND_MOVE ", msg, " ", sock, " ", player.addressText);
        handleCommunication(temp);
    }
    
}


void* threadBody(void* args){

    
    struct Response *response_ptr = (struct Response *)args;
    struct Response incomingResponse = *response_ptr;



    concat(incomingResponse.msg,2," ",incomingResponse.address);

    logToFile(logger,incomingResponse.msg);

    struct Response response = handleCommunication(incomingResponse.msg);


    char* server_socketStr = incomingResponse.serverSocketStr;
    
    char message[100];
    memset(message,0,100);
    struct Player player;
    char buffer[100];
    memset(buffer,0,100);

    if(response.player.gameId == 0 && response.gameId == 0){
        printf("Mensaje ::::  %s \n", response.msg);
        if (numPlayers < MAX_PLAYERS)
        {
            players[numPlayers] = response.player;

            printf("Player rec: %s || ", players[numPlayers].nickname);

            for (int i = 0; i < (MAX_PLAYERS / 2); i++)
            {
                //printf("Paso por for en %d || ", i);
                //printf("%d", games[i].totalNumPlayers);
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
            memset(numPlayerText,0,2);
            convertInt2Char(players[numPlayers].playerNum, numPlayerText, sizeof(numPlayerText));
            //printf(" Player num INT  %d", players[numPlayers].playerNum);
            char gameIdText[4];
            memset(gameIdText,0,4);
            convertInt2Char(players[numPlayers].gameId, gameIdText, sizeof(gameIdText));
            strcpy(message, "SERVER GAME_INFO ");
            concat(message, 7, server_socketStr, " ", numPlayerText, " ", gameIdText, " ", players[numPlayers].addressText);
            //printf("Mensaje =>>   %s   ",message);

            handleCommunication(message);
            //printf("Gamepos ... %d || ", gamePos);
            if (players[numPlayers].playerNum == 2)
            {   
                strcpy(message, "PLAYER SEND_OPP ");
                concat(message, 5, server_socketStr, " ", games[gamePos].player2.nickname, " ", games[gamePos].player1.addressText);
                printf("Mensaje =>>   %s   ",message);
                handleCommunication(message);
                //sendOpponent(server_socket, games[gamePos].player2.nickname, games[gamePos].player1);

                strcpy(message, "PLAYER SEND_OPP ");
                concat(message, 5, server_socketStr, " ", games[gamePos].player1.nickname, " ", games[gamePos].player2.addressText);
                //printf("Mensaje =>>   %s   ",message);
                handleCommunication(message);
                //sendOpponent(server_socket, games[gamePos].player1.nickname, games[gamePos].player2);
            }

            printf("Player %s connected.\n", players[numPlayers].nickname);
            
            ++numPlayers;
        }
    }
   else{

    if(response.playerNum == 1){
        strcpy(buffer, games[response.gameId-100].player1.addressText);
        player = games[response.gameId-100].player2;
    }else{
        strcpy(buffer, games[response.gameId-100].player2.addressText);
        player = games[response.gameId-100].player1;
    }

    char *colon_position = strchr(buffer, ':');
    *colon_position = '\0'; // Reemplazar ':' por un carácter nulo

    char *ip_str = buffer;
    char *port_str = colon_position + 1;


    char logString[500];
    
    concat(logString,5, ip_str," ",port_str,": ",response_ptr->msg);    

    logToFile(logger,logString);

    handle_request(response_ptr->serverSocketStr, response.msg, player);
        
    }




    free(args);

    pthread_exit(NULL);
}



int checkArguments(int argc, char* argv[]){

    if(argc < 3){
        fprintf(stderr, "Too few arguments\n");
        return 1;
    }
    if(argc > 3){
        fprintf(stderr, "Too many arguments\n");
        return 1;
    }

    return 0;
    
}

int main(int argc, char* argv[])
{

    if(checkArguments(argc,argv)){
        exit(1);
    }

    //Initialize PORT AND Logger
    PORT = argv[1];
    logger.printEnabled = 1;
    logger.logfile = NULL;
    logger.filename = NULL;

    setFile(&logger, argv[2]);

    char logMessage[500];
    memset(logMessage,0,500);
    
    concat(logMessage,2,"Logging to file: ",logger.filename);

    logToFile(logger,logMessage);


    char createSocketMessage[30];

    memset(createSocketMessage,0,30);


    concat(createSocketMessage,2,"SERVER CREATE_SOCKET ",PORT);
    
    
    struct Response response;
    response = handleCommunication(createSocketMessage);
    int server_socket = response.server_socket;
    char server_socketStr[4]; 
    snprintf(server_socketStr, sizeof(server_socketStr), "%d", server_socket);
    response.server_socket = 0;
    



    for (int i = 0; i < (MAX_PLAYERS / 2); i++)
    {
        games[i].totalNumPlayers = 0;
    }

    logToFile(logger,"Waiting for players to connect...");

while(1){
    char message[100];
    strcpy(message, "SERVER LISTEN_MSG ");
    concat(message, 1, server_socketStr);
    response = handleCommunication(message);
    
        strcpy(response.serverSocketStr, server_socketStr);
        struct Response *newResponse =  malloc(sizeof(struct Response));
        memset(&message,0,100);
        *newResponse = response;
        

        pthread_t tid;
        pthread_create(&tid, NULL, threadBody, (void *)newResponse);

}
}

