#include <string.h>
#include "table.h"


bool tb_elem_is_smaller(tb_elem a, tb_elem b){
    if(a.key1 == b.key1){
        return strcmp(a.key2, b.key2) < 0;
    }
    return a.key1 < b.key1;
}

bool tb_elem_is_eq(tb_elem a, tb_elem b){
    return a.key1 == b.key1 && strcmp(a.key2, b.key2) == 0;
}

bool tb_read(table* tb){
    tb_elem* table;
    int size;

    if(scanf("%d", &size) != 1 || size < 0){
        printf("Неверный формат\n");
        return false;
    }

    table = malloc(sizeof(tb_elem)*size);
    for(int i = 0; i < size; ++i){
        if(scanf("%d %s %s", &table[i].key1, table[i].key2, table[i].value) != 3){
        printf("Неверный формат\n");
        free(table);
        return false;        
        }
    }

    tb->buf = table;
    tb->size = size;
    return true;
}

void tb_deinit(table* tb){
    free(tb->buf);
}

void tb_print(table tb){
    for(int i = 0; i < tb.size; ++i){
        printf("%d %s %s\n", tb.buf[i].key1, tb.buf[i].key2, tb.buf[i].value);
    }
}
