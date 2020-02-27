#include <stdlib.h>
#include "queue.h"

Queue* makeQueue(){
    Queue* res = (Queue*) malloc(sizeof(Queue));
    res->first = (Item*) malloc(sizeof(Item));
    res->first->next = NULL;
    res->last = res->first;
    res->size = 0;

    return res;
}

void delQueue(Queue* q) {
    Item* next = NULL;
    Item* curr = q->first;
    while(curr) {
        next = curr->next;
        free(curr);
        curr = next;
    }
    free(q);
}

TYPE pop(Queue* q) { 
    TYPE res = q->first->value;
    Item* newFirst = q->first->next;
    free(q->first);
    q->first = newFirst;
    q->size--;
    return res;
}

int push(Queue* q, TYPE v){
    Item* newItem = (Item*) malloc(sizeof(Item));
    if (!newItem)
        return 0;
    q->last->value = v;
    q->last = q->last->next = newItem;
    q->size++;
    return 1;
}

int empty(Queue* q){
    return q->size;
}
