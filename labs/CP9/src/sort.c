#include "sort.h"

void tb_sort(table tb){
    int l = 0;
    int r = tb.size-1;
    while(l < r) {
        int idx = l;
        for(int i = l; i < r; i++){
            if(tb_elem_is_smaller(tb.buf[i+1], tb.buf[i])){
                tb_elem t = tb.buf[i];
                tb.buf[i] = tb.buf[i+1];
                tb.buf[i+1] = t;
                idx = i+1;
            }
        }
        r = idx;
        for(int i = r; i > l; i--){
            if(tb_elem_is_smaller(tb.buf[i], tb.buf[i-1])){
                tb_elem t = tb.buf[i];
                tb.buf[i] = tb.buf[i-1];
                tb.buf[i-1] = t;
                idx = i-1;
            }
        }
        l = idx;
    }
}

int tb_binsearch(table tb, tb_elem el){
    int l = 0;
    int r = tb.size-1;
    int m;

    while(l < r){
        m = l + (r - l)/2;
        if(tb_elem_is_smaller(tb.buf[m], el)) l = m+1;
        else r = m;
    }
    if(tb_elem_is_eq(tb.buf[r], el)) 
        return r;
    return -1;
}

bool tb_is_sorted(table tb){
    for(int i = 1; i < tb.size; ++i){
        if(tb_elem_is_smaller(tb.buf[i-1], tb.buf[i]) || tb_elem_is_eq(tb.buf[i-1], tb.buf[i]))
            return false;
    }
    return true;
}