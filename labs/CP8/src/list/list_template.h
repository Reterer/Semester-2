#include <stdlib.h>
#include <stdbool.h>
#include "template/template.h"

#define LISTPTR TEMPLATE(T,listptr)
#define LIST    TEMPLATE(T,list)
#define LIST_EL TEMPLATE(T,list_el)

typedef struct LIST_EL LIST_EL;
typedef struct LIST LIST;
typedef LIST *LISTPTR;

struct LIST_EL {
    T val;
    size_t next;
};

struct LIST {
    LIST_EL *buf;
    size_t cap;
    size_t size;
    size_t first;
    size_t last;
    size_t empty;
};

#define LIST_ITERATOR TEMPLATE(T,list_iterator)
typedef struct LIST_ITERATOR LIST_ITERATOR;

struct LIST_ITERATOR {
    LISTPTR list;
    size_t prev_el;
};

bool TEMPLATE(T,list_init)(LISTPTR *lptr);
void TEMPLATE(T,list_deinit)(LISTPTR *lptr);

bool TEMPLATE(T,list_push_front)(LISTPTR l, T val);
bool TEMPLATE(T,list_push_back)(LISTPTR l, T val);

T TEMPLATE(T,list_pop_front)(LISTPTR l);

bool TEMPLATE(T,list_is_empty)(LISTPTR l);
size_t TEMPLATE(T,list_get_size)(LISTPTR l);

void TEMPLATE(T,list_reverse)(LISTPTR l);

LIST_ITERATOR TEMPLATE(T,list_begin)(LISTPTR l);
LIST_ITERATOR TEMPLATE(T,list_end)(LISTPTR l);


// ********************ITERATORS**********************

T TEMPLATE(T,list_iterator_get_val)(LIST_ITERATOR it);
void TEMPLATE(T,list_iterator_set_val)(LIST_ITERATOR it, T val);

void TEMPLATE(T,list_iterator_next)(LIST_ITERATOR *it);
bool TEMPLATE(T,list_iterator_is_equals)(LIST_ITERATOR a, LIST_ITERATOR b);

bool TEMPLATE(T,list_iterator_insert_before)(LIST_ITERATOR *it, T val);
bool TEMPLATE(T,list_iterator_remove)(LIST_ITERATOR *it);

#undef LIST_ITERATOR
#undef LISTPTR
#undef LIST