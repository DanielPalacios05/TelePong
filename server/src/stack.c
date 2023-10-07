// Stack implementation in C

#include <stdio.h>
#include <stdlib.h>
#include "../include/consts.h"



// Creating a stack
struct stack {
  int items[MAXUSERS];
  int top;
  int count;
};
typedef struct stack st;

void createEmptyStack(st *s) {
  s->top = -1;
}

// Check if the stack is full
int stackIsfull(st *s) {
  if (s->top == MAXUSERS - 1)
    return 1;
  else
    return 0;
}

// Check if the stack is empty
int stackIsempty(st *s) {
  if (s->top == -1)
    return 1;
  else
    return 0;
}

// Add elements into stack
void push(st *s, int newitem) {
  if (stackIsfull(s)) {
    printf("STACK FULL");
  } else {
    s->top+=1;
    s->items[s->top] = newitem;
    s->count++;
  }
  
}

// Remove element from stack
void pop(st *s,int *result) {
  if (stackIsempty(s)) {
    printf("\n STACK EMPTY \n");
  } else {
    *result=s->items[s->top];
    s->top-=1;
    
    s->count-=1;
  }
  
  printf("\n");
}

// Print elements of stack
void printStack(st *s) {
  printf("Stack: ");
  for (int i = 0; i < s->count; i++) {
    printf("%d ", s->items[i]);
  }
  printf("\n");
}

