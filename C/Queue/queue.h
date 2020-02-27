#pragma once
#define TYPE int

typedef struct Item {
    TYPE value;
    struct tem* next;
} Item;

typedef struct Queue {
    Item* first;
    Item* last;
    int size;
} Queue;

Queue* makeQueue();
void delQueue(Queue* q);

TYPE pop(Queue* q);
int push(Queue* q, TYPE v);
int empty(Queue* q);
