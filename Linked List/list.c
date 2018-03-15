/*
 * Linked list c file
 *    by Timothy Boye
 */

#include "list.h"

/*
 * Init the list
*/
int makeList(List* list)  { 
   list->head = NULL; 
   list->size = 0; 
  
   return SUCCESS; 
} 

/*
 * Get the list size (Such OOP wow)
*/
unsigned getListSize(List* list) {
    return list->size;
} 

/*
 * free ([ the list ]), release the space
*/
void freeList(List* list) {
    Node *current, *next;
    current = list->head;
    
    while(current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    free(list);
    list->head = NULL; 
    list->size = 0; 
}

/*
 * Add a value to the list, !!appends to the head!!
*/
int addtoList(List* list, char* source) {
    Node *new;
    
    if ((new = malloc(sizeof(Node))) == NULL) 
    { 
        return FAILURE;
    }
    
    new->value = source;
    new->next = list->head;
    list->head = new;
    
    list->size++;
    
    return SUCCESS;
}

/*
 * Search for a VALUE and remove the FIRST instance
 * if found, then join the node before and after.
*/
int deletefromList(List* list, char* target) {
    Node *current, *previous;
    previous = NULL;
    current = list->head;
    
    while(current != NULL && strcmp(current->value, target) != 0) {        
        previous = current;
        current = current->next;
    }
    
    if (current == NULL) {
        return FAILURE;
    }
    else if (previous == NULL) {  
        list->head = current->next;
        free(current);
    }
    else {
        previous->next = current->next;
        free(current);
    }
    
    (list->size)--;
    return SUCCESS;
}

/*
 * print the list to the console, one node per line
*/
void displayList(List* list) {
    Node *current;
    current = list->head;
    
    while(current != NULL) {   
        printf("%s\n", current->value);
        current = current->next;
    }
}

/*
 * find a VALUE in the list returns:
 *    NULL not found
 *    location of first matching node
*/
Node* searchList(List* list, char* target) {
    Node *current;
    current = list->head;
    
    while(current != NULL && strcmp(current->value, target) == 0) {        
        current = current->next;
    }
    
    return current;
}


int main() {
    List* list;
    
    list = malloc(sizeof(List));
    
    makeList(list);
    
    addtoList(list, "strings");
    addtoList(list, "of");
    addtoList(list, "list");
    addtoList(list, "linked");
    addtoList(list, "a");
    addtoList(list, "is");
    addtoList(list, "This");
        
    displayList(list);
    
    printf("list size: %d\n", getListSize(list));
    
    printf("remove a from list: %d, remove algebraic: %d\n", deletefromList(list, "a"),
                        deletefromList(list, "algebraic"));
    
    displayList(list);

    printf("list size now: %d\n", getListSize(list));
    
    printf("Empty List\n");

    freeList(list);
    
    printf("list size now: %d\n", getListSize(list));
}
