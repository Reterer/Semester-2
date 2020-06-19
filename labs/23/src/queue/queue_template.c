#ifdef T
#include <stdlib.h>

#include "log/log.h"
#include "queue/queue_template.h"

#define QUEUE TEMPLATE(T,queue)
#define QUEUE_EL TEMPLATE(T,queue_el)

bool TEMPLATE(T,queue_init)(QUEUE **q){
    *q = malloc(sizeof(QUEUE));
    if(*q == NULL)
        return false;

    (*q)->first = NULL;
    (*q)->last  = NULL;
    (*q)->size  = 0;
    return true;
}

void TEMPLATE(T,queue_deinit)(QUEUE **q){
    if(*q == NULL)
        return;
    
    QUEUE_EL *curr_el = (*q)->first;
    while(curr_el != NULL){
        QUEUE_EL *temp = curr_el->next;
        free(curr_el);
        curr_el = temp;
    }

    free(*q);
    *q = NULL;
}

bool TEMPLATE(T,queue_is_empty)(QUEUE *q){
    return q->size == 0;
}

int TEMPLATE(T,queue_get_size)(QUEUE *q){
    return q->size;
}

void TEMPLATE(T,chek_on_empty_queue)(QUEUE *q){
    if(q == NULL || q->size == 0){
        LOG_ERR("queue is empty or queue == NULL");
        exit(1);
    }
}

T TEMPLATE(T,queue_front)(QUEUE *q){
    TEMPLATE(T,chek_on_empty_queue)(q);
    return q->first->val;
}

T TEMPLATE(T,queue_pop)(QUEUE *q){
    TEMPLATE(T,chek_on_empty_queue)(q);
    
    QUEUE_EL *second = q->first->next; 
    T res = q->first->val;
    
    free(q->first);
    q->first = second;
    
    if(q->size == 1){
        q->last = NULL;
    }
    q->size--;

    return res;
}
 
bool TEMPLATE(T,queue_push_back)(QUEUE *q, T val){
    QUEUE_EL *new_el = malloc(sizeof(QUEUE_EL));
    if(new_el == NULL)
        return false;
    
    new_el->val = val;
    new_el->next = NULL;

    if(q->size == 0)
        q->first = new_el;
    else
        q->last->next = new_el;
    
    q->last = new_el;
    q->size++;

    return true;
}

#undef QUEUE
#undef QUEUE_EL
#endif