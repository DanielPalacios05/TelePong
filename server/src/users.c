#include "../include/users.h"

#include "utils.c"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <netdb.h>
#define MAXUSERS 10

struct user{
    char nickname[10];
    struct sockaddr userSocket;
    
};

struct users{

    struct user user_list[MAXUSERS];

    int numUsers;

};



void printUser(struct user *u) {

    char ipAddr[16];

    get_in_addr(&(u->userSocket),ipAddr);


    printf("Nickname: %s, IP: %s\n", u->nickname, ipAddr);
}

void printAllUsers(struct users *userList){

    printf("User list of %d: \n",userList->numUsers);

    for (int i = 0; i < userList->numUsers; i++)
    {
        printUser(&((userList->user_list)[i]));
    }
    

}

int add_user(struct user new_user, struct users *userList){

    userList->user_list[userList->numUsers] = new_user;

    userList->numUsers += 1;

    return 0;

}


//be careful, array is left empty
int delete_user(struct users *userList,int id){

      /* Copy next element value to current element */
        for(int i=id-1; i<userList->numUsers-1; i++)
        {
             userList->user_list[i] =  userList->user_list[i + 1];
        }

        /* Decrement array size by 1 */
         userList->numUsers--;
    4

    return 0;


}
