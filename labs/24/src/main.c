#include <stdio.h>
#include <stdlib.h>

#include "token/token.h"
#include "log/log.h"

void log_err_and_exit(const char *str){
    LOG_ERR(str);
    exit(1);
}

void clean_queue(token_queue *q){
    while(!token_queue_is_empty(q))
        token_queue_pop(q);
}

int main(){
    token_queue *q_read; // Считанные токены
    token_queue *q_rpn;  // Токены в обратной польской записи
    if (!token_queue_init(&q_read)) 
        log_err_and_exit("Can't init queue");
    if (!token_queue_init(&q_rpn))
        log_err_and_exit("Can't init queue");

    read_expr_res rer;
    while((rer = read_expr(q_read, stdin)) != RER_EOF){
        if(rer == RER_ERR)
            printf("Token %d is unknown.\n", token_queue_get_size(q_read)+1);
        else {
            sort_station_res ssr = sort_station(q_rpn, q_read);
            if(ssr == SSR_ERR_BR_BALANCE)
                printf("Err bracket balance.\n");
            else if(ssr == SSR_ERR_INIT)
                LOG_ERR("Can't init token stack. Try later.");
            else {
                print_expr(q_rpn, stdout);
            }
        }

        clean_queue(q_read);
        clean_queue(q_rpn);
    }
    token_queue_deinit(&q_rpn);
    token_queue_deinit(&q_read);
}