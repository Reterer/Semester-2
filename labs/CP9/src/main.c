#include "table.h"
#include "sort.h"


int main(){
    table tb;
    tb_read(&tb);
    tb_sort(tb);
    
    printf("\n");
    tb_print(tb);

    tb_elem el;
    while(scanf("%d %s", &el.key1, el.key2) == 2){
        int idx = tb_binsearch(tb, el);
        if(idx < 0){
            printf("Элементы не найдены\n");
            continue;
        }
        while(tb_elem_is_eq(tb.buf[idx], el)){
            printf("%d %s %s\n", tb.buf[idx].key1, tb.buf[idx].key2, tb.buf[idx].value);
            idx++;
        }
    }

    tb_deinit(&tb);
}