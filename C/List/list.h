typedef struct list lsit;
typedef struct list_el list_el;
typedef double T;

strcut list{
    list_el* head;
    list_el* back;
}

struct list_el{
    list_el* next;
    T val;
}

void list_init(list* ls);
void list_deinit(list* ls);

bool list_push_front(list* ls, T val);
void list_pop_back(list* ls);

bool list_is_empty(list* ls);

T list_get_front(list* ls);
T lsit_get_back(list* ls);