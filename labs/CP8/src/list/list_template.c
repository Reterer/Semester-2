#include <stdlib.h>
#include <stdint.h>
#include "list/list_template.h"
#include "log/log.h"

#define LISTPTR TEMPLATE(T, listptr)
#define LIST    TEMPLATE(T, list)

#ifndef MIN_CAP
#define MIN_CAP 4
#endif

#ifndef NOT_AN_INDEX
#define NOT_AN_INDEX SIZE_MAX
#endif

#define LIST_ITERATOR TEMPLATE(T,list_iterator)


bool TEMPLATE(T, list_init)(LISTPTR *lptr){
    *lptr = malloc(sizeof(LIST));
    if(*lptr == NULL)
        return false;
    
    (*lptr)->buf = NULL;
    (*lptr)->cap = 0;
    (*lptr)->size = 0;
    (*lptr)->first = NOT_AN_INDEX;
    (*lptr)->last = NOT_AN_INDEX;
    (*lptr)->empty = NOT_AN_INDEX;
    return true;
}

void TEMPLATE(T, list_deinit)(LISTPTR *lptr){
    if(*lptr == NULL)
        return;
    
    free((*lptr)->buf);
    free(*lptr);
    *lptr = NULL;
}

static bool TEMPLATE(T,list_grow)(LISTPTR l){
    size_t new_cap = l->cap * 3 / 2;
    if(new_cap < MIN_CAP)
        new_cap = MIN_CAP;

    LIST_EL *new_buf = realloc(l->buf, sizeof(LIST_EL)*new_cap);
    if(new_buf == NULL){
        LOG_ERR("Can't realloc buff");
        return false;
    }
    
    l->buf = new_buf;
    for(size_t i = l->cap; i < new_cap; ++i){
        l->buf[i].next = l->empty;
        l->empty = i;
    }
    l->cap = new_cap;
    return true;
}

static size_t TEMPLATE(T,list_get_new_id)(LISTPTR l){
    size_t res = NOT_AN_INDEX;
    if(l->empty == NOT_AN_INDEX){
        if(TEMPLATE(T,list_grow)(l) == false)
            return NOT_AN_INDEX;
    }

    res = l->empty;
    l->empty = l->buf[l->empty].next;

    l->buf[res].next = NOT_AN_INDEX;
    return res;
} 

bool TEMPLATE(T,list_push_front)(LISTPTR l, T val){
    size_t new_el = TEMPLATE(T,list_get_new_id)(l);
    if(new_el == NOT_AN_INDEX)
        return false;

    l->buf[new_el].next = l->first;
    l->buf[new_el].val  = val;
    
    l->first = new_el;
    if(l->size == 0)
        l->last = new_el;

    l->size++;
    return true;
}

bool TEMPLATE(T,list_push_back)(LISTPTR l, T val){
    size_t new_el = TEMPLATE(T,list_get_new_id)(l);
    if(new_el == NOT_AN_INDEX)
        return false;
    
    l->buf[new_el].next = NOT_AN_INDEX;
    l->buf[new_el].val = val;

    if(l->last != NOT_AN_INDEX){
        l->buf[l->last].next = new_el;
        l->last = new_el;
    }
    else{
        l->last = new_el;
        l->first = new_el;
    }
 
    l->size++;
    return true;
}

void TEMPLATE(T,list_remove_id)(LISTPTR l, size_t elem){
    l->buf[elem].next = l->empty;
    l->empty = elem;
}

T TEMPLATE(T,list_pop_front)(LISTPTR l){
    T res;
    if(l->size == 0){
        LOG_ERR("buff index out of bounds");
        exit(1);
    }

    res = l->buf[l->first].val;
    
    size_t old_first = l->first;
    l->first = l->buf[old_first].next;
    if(l->size == 1)
        l->last = NOT_AN_INDEX;

    TEMPLATE(T,list_remove_id)(l, old_first);
    l->size--;

    return res;
}

bool TEMPLATE(T,list_is_empty)(LISTPTR l){
    return  l->size == 0;
}

size_t TEMPLATE(T,list_get_size)(LISTPTR l){
    return l->size;
}

void TEMPLATE(T,list_reverse)(LISTPTR l){
    size_t prev_el = NOT_AN_INDEX;
    size_t curr_el = l->first;
    while(curr_el != NOT_AN_INDEX){
        size_t next_el = l->buf[curr_el].next;
        l->buf[curr_el].next = prev_el;
        
        prev_el = curr_el;
        curr_el = next_el;
    }

    size_t temp;
    temp = l->first;
    l->first = l->last;
    l->last  = temp;
}

LIST_ITERATOR TEMPLATE(T,list_begin)(LISTPTR l){
    LIST_ITERATOR li = {l, NOT_AN_INDEX};
    return li;
}

LIST_ITERATOR TEMPLATE(T,list_end)(LISTPTR l){
    LIST_ITERATOR li = {l, l->last};
    return li;
}

// ********************ITERATORS**********************

size_t TEMPLATE(T,list_iterator_get_curr_el)(LIST_ITERATOR it){
    size_t curr_el = NOT_AN_INDEX;
    if(it.prev_el == NOT_AN_INDEX){
        curr_el = it.list->first;
    }else{
        curr_el = it.list->buf[it.prev_el].next;
    }

    return curr_el;
}

T TEMPLATE(T,list_iterator_get_val)(LIST_ITERATOR it){
    size_t curr_el = TEMPLATE(T,list_iterator_get_curr_el)(it);
    if(curr_el == NOT_AN_INDEX){
        LOG_ERR("iterator out of bounds");
        exit(1);
    }

    return it.list->buf[curr_el].val;
}

void TEMPLATE(T,list_iterator_set_val)(LIST_ITERATOR it, T val){
    size_t curr_el = TEMPLATE(T,list_iterator_get_curr_el)(it);
    if(curr_el == NOT_AN_INDEX){
        LOG_ERR("iterator  out of bounds");
        exit(1);
    }

    it.list->buf[curr_el].val = val;
}

void TEMPLATE(T,list_iterator_next)(LIST_ITERATOR *it){
    if(it == NULL)
        return;

    it->prev_el = TEMPLATE(T,list_iterator_get_curr_el)(*it);
}

bool TEMPLATE(T,list_iterator_is_equals)(LIST_ITERATOR a, LIST_ITERATOR b){
    return a.list == b.list && a.prev_el == b.prev_el;
}


bool TEMPLATE(T,list_iterator_insert_before)(LIST_ITERATOR *it, T val){
    if(it == NULL)
        return false;
    
    size_t new_el  = TEMPLATE(T,list_get_new_id)(it->list);
    if(new_el == NOT_AN_INDEX)
        return false;
    size_t curr_el = TEMPLATE(T,list_iterator_get_curr_el)(*it);
    
    if(it->prev_el == it->list->last){
        it->list->last = new_el;
    }

    if(it->prev_el == NOT_AN_INDEX)
        it->list->first = new_el;
    else 
        it->list->buf[it->prev_el].next = new_el;

    it->list->buf[new_el].next  = curr_el;
    it->prev_el = new_el;

    it->list->buf[new_el].val = val;
    it->list->size++;
    return true;
}

bool TEMPLATE(T,list_iterator_remove)(LIST_ITERATOR *it){
    if(it == NULL)
        return false;
    
    size_t curr_el = TEMPLATE(T,list_iterator_get_curr_el)(*it);
    if(curr_el == NOT_AN_INDEX)
        return false;
    
    if(curr_el == it->list->last){
        it->list->last = it->prev_el;
    }

    if(it->prev_el == NOT_AN_INDEX)
        it->list->first = it->list->buf[curr_el].next;
    else
        it->list->buf[it->prev_el].next = it->list->buf[curr_el].next;

    TEMPLATE(T,list_remove_id)(it->list, curr_el);
    it->list->size--;
    return true;
}


#undef LIST_ITERATOR
#undef LISTPTR
#undef LIST