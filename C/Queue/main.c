#include <stdio.h>
#include "queue.h"

int main() {
    Queue* q = makeQueue();
    push(q, 10);
    printf("%i\n", q->size);
    printf("%i\n", pop(q));
    delQueue(q);
    return 0;
}
