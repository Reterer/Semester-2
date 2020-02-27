#pragma once
#define TYPE int

typedef struct {
    TYPE value;
    Item* next;
} Item;

typedef struct {
    Item* first;
    Item* last;
    size_t size;
} Queue;

Queue* makeQueue();
void delQueue(*Queue);

TYPE pop(Queue* q);
int push(Queue* q, TYPE v);
int empty(Queue* q);
