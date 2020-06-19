#ifdef T
#include <stdbool.h>

#define QUEUE TEMPLATE(T,queue)
#define QUEUE_EL TEMPLATE(T,queue_el)

typedef struct QUEUE_EL QUEUE_EL;
typedef struct QUEUE QUEUE;

struct QUEUE_EL{
    T val;
    QUEUE_EL *next;
};

struct QUEUE{
    int size;
    QUEUE_EL *first;
    QUEUE_EL *last;
};

bool TEMPLATE(T,queue_init)(QUEUE **q);
void TEMPLATE(T,queue_deinit)(QUEUE **q);

bool TEMPLATE(T,queue_is_empty)(QUEUE *q);
int TEMPLATE(T,queue_get_size)(QUEUE *q);

T TEMPLATE(T,queue_front)(QUEUE *q);
T TEMPLATE(T,queue_pop)(QUEUE *q);
 
bool TEMPLATE(T,queue_push_back)(QUEUE *q, T val);

#undef QUEUE
#undef QUEUE_EL
#endif