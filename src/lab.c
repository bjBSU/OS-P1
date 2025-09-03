#include "lab.h"
#include <stdio.h>
#include <stdlib.h>

//example of using FreeFunc:
//FreeFunc my_free = free_int;
//my_free(some_pointer); // Calls free_int(some_pointer)
typedef struct Node{
    void *data;
    struct Node *next;
    struct Node *prev;
}Node;

//is this the right idea for List struct?
struct List {
    Node *SENTINEL;
    size_t size;
    ListType type;
};

/**
 * AI usage: AI use
 * @brief Create a new list of the specified type.
 * @param type The type of list to create (e.g., LIST_LINKED_SENTINEL).
 * @return Pointer to the newly created list, or NULL on failure.
 */
List *list_create(ListType type) {
    List *list = malloc(sizeof(List));
    if (list == NULL) {
        return false; // Memory allocation failed
    }
    Node *sentinel = malloc(sizeof(Node));
    if(sentinel == NULL) {
        free(list);
        return false; // Memory allocation failed
    }
    sentinel->next = sentinel;
    sentinel->prev = sentinel;
    list->SENTINEL = sentinel;
    list->type = type;
    list->size = 0;
    return list;
}

void *list_destroy(List *list, FreeFunc free_func) {

  //check if the list exists 
  if(list == NULL){
    return false;
  }
  Node *first = list->SENTINEL->next;
  while(first != list->SENTINEL){
    Node *next = first->next;
    free_func(first->data);
    free(first);
    first = next;
  }
  free(list->SENTINEL);
  free(list);
}

bool list_append(List *list, void *data){
  if(list == NULL){
    return false;
  }
  Node *newNode = malloc(sizeof(Node));
  if(newNode == NULL){
    return false;
  }
  newNode->data = data;

  Node *currentLast = malloc(sizeof(Node));
  if(currentLast == NULL){
    return false;
  }
  currentLast = list->SENTINEL->prev;
  currentLast->next = newNode;
  newNode->next = list->SENTINEL;
  list->SENTINEL->prev = newNode;
  list->size++;
  return true;
}

bool list_insert(List *list, size_t index, void *data){
  if(list == NULL){
    return false;
  }
  Node *newNode = malloc(sizeof(Node));
  if(newNode == NULL){
    return false;
  }
  newNode->data = data;

  Node *current = malloc(sizeof(Node));
  if(current == NULL){
    return false;
  }

  current = list->SENTINEL->next;

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

void *list_remove(List *list, size_t index){
  
}
