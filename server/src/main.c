
#include "users.c"
#include <netdb.h>
#include <stdio.h>
#include "ddetp.c"
#include "string.h"
#include "rooms.c"
struct users userList;
struct room rooms[1];


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

        sendResponseToUser(&userList.user_list[userList.numUsers],sock,strcat("0",(char*) userList.numUsers));


        
           
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


    createEmptyStack(userList.freeIdStack);

    int sock = initialize_socket();


    while (1)
    {
        struct request *incomingRequest = listenForRequests(sock);

        if(incomingRequest->bytesAmount > 0){
        
            handle_request(sock,incomingRequest);
        }
    }
    

  










    return 0;
}