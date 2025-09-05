#include "lab.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Constructs the node struct.
 * AI use: Assisted by AI
 */
typedef struct Node{
    void *data;
    struct Node *next;
    struct Node *prev;
}Node;

/**
 * Constructs the list struct
 * AI use: No AI
 */
struct List {
    Node *SENTINEL;
    size_t size;
    ListType type;
};

/**
 * Creates a list and sets the Sentinel node.
 * AI usage: written by AI
 */
List *list_create(ListType type) {
    List *list = malloc(sizeof(List));
    Node *sentinel = malloc(sizeof(Node));

    sentinel->next = sentinel;
    sentinel->prev = sentinel;
    list->SENTINEL = sentinel;
    list->type = type;
    list->size = 0;
    return list;
}

/**
 * Destroys a list and sets everything free.
 * AI use: Assisted by AI
 */
void list_destroy(List *list, FreeFunc free_func) {
  Node *first = list->SENTINEL->next;
  while(first != list->SENTINEL){
    Node *next = first->next;
    if(free_func != NULL && first->data != NULL){
      free_func(first->data);
      free(first);
    }
    first = next;
  }
  free(list->SENTINEL);
  free(list);
}

/**
 * Adds a new node to the end of a list.
 * Returns true if successful and updates the length of the list.
 * AI use: Assisted by AI
 */
bool list_append(List *list, void *data){
  if(list == NULL){
    return false;
  }
  Node *newNode = malloc(sizeof(Node));
  newNode->data = data;

  Node *currentLast = list->SENTINEL->prev;
  
  newNode->prev = currentLast;
  currentLast->next = newNode;
  newNode->next = list->SENTINEL;
  list->SENTINEL->prev = newNode;
  list->size++;
  return true;
}

/**
 * Inserts a node into a list at a specific index. 
 * Returns true if the index exists.
 * AI use: No AI
 */
bool list_insert(List *list, size_t index, void *data){
  if(list == NULL){
    return false;
  }
  Node *newNode = malloc(sizeof(Node));
  newNode->data = data;

  Node *current = list->SENTINEL->next;

  if(index >= list->size){
    free(newNode);
    return false;
  }
  for(size_t i = 0; i<index; i++){
      current = current->next;
    }
  
  newNode->next = current;
  newNode->prev = current->prev;
  current->prev->next = newNode;
  current->prev = newNode;
  list->size++;
  return true;
}

/**
 * Removes a specific node in a list based on index.
 * AI use: Assisted by AI
 */
void *list_remove(List *list, size_t index){
  if(list == NULL){
    return false;
  }
  if(index >= list->size){
    return NULL;
  }

  Node *current = list->SENTINEL->next;
  for(size_t i = 0; i<index; i++){
      current = current->next;
    }
  
  current->next->prev = current->prev;
  current->prev->next = current->next;
  void *data = current->data;
  free(current);
  list->size--;
  return data;
}

/**
 * Gets a specific node in the list based on index.
 * AI use: Assisted by AI
 */
void *list_get(const List *list, size_t index){
  if(list == NULL){
    return NULL;
  }
  if(index >= list->size){
    return NULL;
  }

  Node *current = list->SENTINEL->next;

  for(size_t i = 0; i<index; i++){
      current = current->next;
    }
    // Node *data = current->data;
    return current->data;
}

/**
 * Returns the size of the list if not null.
 * AI use: No AI
 */
size_t list_size(const List *list){
  if(list == NULL){
    return false;
  }

  return list->size;
}

/**
 * Checks to see if the list is empty and returns true if it is.
 * AI use: Assisted by AI
 */
bool list_is_empty(const List *list){
  if(list == NULL){
    return false;
  }
  return list->size == 0;
}


