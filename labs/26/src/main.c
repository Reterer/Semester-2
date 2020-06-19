#include <stdio.h>
#include <stdlib.h>

#include "log/log.h"
#include "udt/udt.h"
#include "sort/sort.h"

void print_error_and_exit(char *str){
    LOG_ERR(str);
    exit(1);
}

void read(udt *u){
    data_type dt;
    while(scanf("%d %d\n", &dt.key, &dt.val) == 2){
        if(udt_push(u, dt) == false)
            print_error_and_exit("Can't push element");
    }
}

void print(udt *u){
    data_type dt;
    while(!udt_is_empty(u)){
        dt = udt_pop(u);
        printf("%d\t%d\n", dt.key, dt.val);
    }
}

int main(){
    udt *u;
    if(!udt_init(&u))
        print_error_and_exit("Can't init UDT");

    read(u);
    sort(u);
    
    printf("KEY\tVAL\n");
    print(u);

    udt_deinit(&u);
    return 0;
}