#include "../include/users.h"
#include "utils.c"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <netdb.h>
#include "stack.c"
#include "../include/consts.h"


struct user{
    char nickname[10];
    struct sockaddr userSocket;

};

struct users{

    struct user user_list[MAXUSERS];

    int numUsers;

    int amountAssigned;

    st freeIdStack[MAXUSERS];

};



void printUser(struct user *u) {

    char ipAddr[16];

    get_in_addr(&(u->userSocket),ipAddr);


    printf("Nickname: %s, IP: %s\n", u->nickname, ipAddr);
}

void printAllUsers(struct users *userList){

    printf("User list of %d: \n",userList->numUsers);

    for (int i = 0; i < userList->amountAssigned; i++)
    {
        int isbusy = 1;
        for (int j = 0; j < userList->freeIdStack->count; j++){
            
            if(i == userList->freeIdStack->items[j]){
                isbusy=0;
                break;
            }
            
        }

        if(isbusy){
            printUser(&((userList->user_list)[i]));
        }

        
        
    }
    

}

int add_user(struct user new_user, struct users *userList){

    int newId;

    if(stackIsempty(userList->freeIdStack)){
        newId=userList->numUsers;
        userList->amountAssigned++;
    }else{
        pop(userList->freeIdStack,&newId);
        
    }

    userList->user_list[newId] = new_user;

    printf("user %s id %d\n\n",new_user.nickname,newId);


    userList->numUsers++;
    

    return 0;

}


//be careful, array is left empty
int delete_user(struct users *userList,int id){

    push(userList->freeIdStack,id);

    printStack(userList->freeIdStack);

    userList->numUsers--;

    return 0;


}