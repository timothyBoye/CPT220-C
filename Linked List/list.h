/* 
 * Linked list h file
 *    by Timothy Boye
 */
#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h>
#include <string.h>

#define SUCCESS 1 
#define FAILURE -1

typedef struct node {
    char* value;
    struct node * next;
} Node;

typedef struct list {
    Node* head;
    unsigned size;
} List;


int makeList(List* list);
unsigned getListSize(List* list); 
void freeList(List* list);

int addtoList(List* list, char* source);
int deletefromList(List* list, char* target);

void displayList(List* list);
Node* searchList(List* list, char* target);
