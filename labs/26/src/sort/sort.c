#include "udt/udt.h"

void insert(udt *in, udt *out){
    // Элемент для вставки в out
    data_type elem = udt_pop(in);
    
    // Смещаем элемент, пока есть куда смещать
    // Или пока он меньше предщественника
    int i = 0;
    data_type buf;
    while(!udt_is_empty(out)){
        buf = udt_pop(out);
        if(elem.key < buf.key){
            i++;
            udt_push(in, buf);
        } else {
            udt_push(out, buf);
            break;
        }
    }

    // Вставляем элемент на свое место
    udt_push(out, elem);

    while(i > 0){
        udt_push(out, udt_pop(in));    
        i--;
    }
}

void sort(udt *in){
    udt *out;
    udt_init(&out);
    
    while(!udt_is_empty(in))
        insert(in, out);

    while(!udt_is_empty(out)){
        udt_push(in, udt_pop(out));
    }
    udt_deinit(&out);
}