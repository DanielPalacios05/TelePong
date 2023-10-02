
#include "users.c"
#include <netdb.h>
#include <stdio.h>
#include "ddetp.c"
#include "string.h"
struct users userList;
char read_data[1024];
struct sockaddr clientAddress;

void handle_request(char *read_data,int bytesResponse,struct sockaddr *clientAddress){

    char* copyString = (char*)malloc(sizeof(read_data));
    strcpy(copyString,read_data);

    char *ptr = strtok(copyString," ");


    
    if(strcmp(ptr,"SETNICK")== 0){
        printf("%s\n",ptr);

        //va a crear un usuario

        char *ptr = strtok(NULL," ");

        struct user new_user;

        strcpy(new_user.nickname,ptr);

        new_user.userSocket = *clientAddress;

        add_user(new_user,&userList);

        printAllUsers(&userList);

        ptr = strtok(NULL, " ");
    }else if (strcmp(read_data,"B") == 0){
        
    }else
    {
        printf("No se entiende%s\n",read_data);
    }
    
}

int main(){


    struct user myUser;

    int sock = initialize_socket();


    while (1)
    {
        int bytes_read = listenForRequests(sock,read_data,&clientAddress);

        if(bytes_read > 0){

        
            handle_request(read_data,bytes_read,&clientAddress);
        }
    }
    

  










    return 0;
}