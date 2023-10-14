#include <netdb.h>
#include <stdio.h>
#include "myPongProtocol.c"
#include "string.h"
#include "logger.c"
#include <pthread.h>
#include "constants.h"

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

    char* PORT2;
    //Initialize PORT AND Logger
    PORT2 = argv[1];
    logger.printEnabled = 1;
    logger.logfile = NULL;
    logger.filename = NULL;

    setFile(&logger, argv[2]);

    char message[500];
    
    concat(message,2,"Logging to file: ",logger.filename);


    logToFile(logger,message);

    memset(&message,0,sizeof(message));

    int sock = initialize_socket(PORT2);

    concat(message,2,"Server listening to port: ",PORT2);
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