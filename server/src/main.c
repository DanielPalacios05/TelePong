
#include "users.c"
#include <netdb.h>
#include <stdio.h>
#include "ddetp.c"
#include "string.h"
#include "logger.c"
#include "rooms.c"
#include <pthread.h>
char* PORT;

struct users userList;
struct room rooms[1];
Logger logger;

struct requestArgs
{
    int sock;
    struct request request;
};









void handle_request(int sock,struct request *req){
    
    char copyString[REQUESTSIZE];
    strcpy(copyString,(req->body));
    //printf("data from %s: %s\n",&req,copyString);
    char *ptr;
    char* tempPr = copyString;

    ptr = strtok_r(tempPr," ",&tempPr);

    printf("%s\n",ptr);



    
    if(strcmp(ptr,"SETNICK")== 0){
        //printf("%s\n",ptr);

        //va a crear un usuario
        struct user new_user;

        ptr = strtok_r(tempPr," ",&tempPr);

        strcpy(new_user.nickname,ptr);

        

        new_user.userSocket = req->clientAddress.addressSock;

        add_user(new_user,&userList);

        printAllUsers(&userList);
        ptr = strtok_r(tempPr," ",&tempPr);


    }else if (strcmp(ptr,"EXIT") == 0){

        ptr = strtok_r(tempPr," ",&tempPr);
        int newId = atoi(ptr);

        delete_user(&userList,newId);

        printAllUsers(&userList);
         
        char numUsersStr[4];

        sprintf(numUsersStr,"%d",userList.numUsers);

        sendResponseToUser(&userList.user_list[userList.numUsers],sock,strcat("0 ", numUsersStr));


        
           
    }else if (strcmp(ptr,"ASSIGN") == 0){

        ptr = strtok_r(tempPr," ",&tempPr);
        int newId = atoi(ptr);

        if(rooms[0].numPlayers == 0){

            sendResponseToUser(&userList.user_list[0],sock,"0 0 WAIT");
            

        }            
    }
    else
    {
        printf("No se entiende%s\n",req->body);
    }


    
}

void* threadBody(void* args){

    
    struct requestArgs* requestArgs = ((struct requestArgs*)args);

    char addressBuffer[100];
    char portBuffer[100];
    getnameinfo(&requestArgs->request.clientAddress.addressSock,requestArgs->request.clientAddress.client_len,addressBuffer,sizeof(addressBuffer),portBuffer, sizeof(portBuffer),NI_NUMERICHOST | NI_NUMERICSERV);

    char logString[500];
    concat(logString,5, &addressBuffer," ",&portBuffer,": ",requestArgs->request.body);    

    logToFile(logger,logString);

    handle_request(requestArgs->sock,&requestArgs->request);

    free(requestArgs);


    pthread_exit(NULL);
}

int main(int argc, char* argv[]){

    if(argc > 3){
        fprintf(stderr, "Too many arguments\n");
        exit(1);
    }


    //Initialize PORT AND Logger
    PORT = argv[1];
    logger.printEnabled = 1;
    logger.logfile = NULL;
    logger.filename = NULL;

    setFile(&logger, argv[2]);

    char message[500];
    
    concat(message,2,"Logging to file: ",logger.filename);


    logToFile(logger,message);

    memset(&message,0,sizeof(message));

    
    createEmptyStack(userList.freeIdStack);

    int sock = initialize_socket(PORT);

    concat(message,2,"Server listening to port: ",PORT);
    logToFile(logger,message);
 



    while (1)
    {  
        struct request incomingRequest = listenForRequests(sock);
        if(incomingRequest.bytesAmount > 0){

            struct requestArgs *newRequest = malloc(sizeof(struct requestArgs));

            newRequest->request = incomingRequest;
            newRequest->sock = sock;

            pthread_t tid;
            pthread_create(&tid, NULL, threadBody, (void *)newRequest);
        
        }
        
    }
    



    return 0;
}