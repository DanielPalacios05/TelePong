#include <sys/socket.h>


struct user;

struct users;




int append_user(char nickname[] , struct sockaddr userSocket,struct users *userList);

int delete_user(struct users *userList,int id);

struct user find_user_by_id(int id);