
#include "users.c"
#include <netdb.h>
#include <stdio.h>
#include "ddetp.c"
#include "string.h"
#include "logger.c"
#include "rooms.c"
struct users userList;
struct room rooms[1];
Logger logger;


void handle_request(int sock,struct request *req){
    
    char copyString[REQUESTSIZE];
    strcpy(copyString,(req->body));
    //printf("data from %s: %s\n",&req,copyString);

    char *ptr = strtok(copyString," ");

    printf("%s\n",ptr);



    
    if(strcmp(ptr,"SETNICK")== 0){
        //printf("%s\n",ptr);

        //va a crear un usuario
        struct user new_user;

        char *ptr = strtok(NULL," ");

        strcpy(new_user.nickname,ptr);

        

        new_user.userSocket = req->clientAddress.addressSock;

        add_user(new_user,&userList);

        printAllUsers(&userList);
        ptr = strtok(NULL, " ");
    }else if (strcmp(ptr,"EXIT") == 0){

        char *ptr = strtok(NULL," ");
        int newId = atoi(ptr);

        delete_user(&userList,newId);

        printAllUsers(&userList);
         
        char numUsersStr[4];

        sprintf(numUsersStr,"%d",userList.numUsers);

        sendResponseToUser(&userList.user_list[userList.numUsers],sock,strcat("0 ", numUsersStr));


        
           
    }else if (strcmp(ptr,"ASSIGN") == 0){

        char *ptr = strtok(NULL," ");
        int newId = atoi(ptr);

        if(rooms[0].numPlayers == 0){

            sendResponseToUser(&userList.user_list[0],sock,"0 0 WAIT");
            

        }





        
           
    }

    {
        printf("No se entiende%s\n",req->body);
    }
    deallocateRequest(req);


    
}

int main(){

    //InitializeLogger
    logger.printEnabled = 1;
    logger.logfile = NULL;
    logger.filename = NULL;

    setFile(&logger, "log.log");

    logToFile(logger, "Logging to file");

    


    createEmptyStack(userList.freeIdStack);

    int sock = initialize_socket();


    while (1)
    {
        logToFile(logger,"Server initiated at: ");
        struct request *incomingRequest = listenForRequests(sock);

        if(incomingRequest->bytesAmount > 0){
        
            handle_request(sock,incomingRequest);
        }
    }
    

  










    return 0;
}