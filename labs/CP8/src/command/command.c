#include "command/command.h"
#include "help/help.h"
#include "log/log.h"

void quit(command_func_args *args){
    fprintf(args->fout, "Quit\n");
}

int_list_iterator *get_iter_by_index_el(command_func_args args, size_t id){
    if(id > int_list_get_size(args.list)){
        fprintf(args.fout, "Index larger than the list size.\n");
        return NULL;
    }
    int_list_iterator *it = malloc(sizeof(int_list_iterator));
    if(it == NULL){
        fprintf(args.fout, "Сan't allocate memory for the iterator. Try later ahah.\n");
        return NULL; 
    }
    
    *it = int_list_begin(args.list);
    for(size_t curr_id = 0; curr_id != id; ++curr_id){
        int_list_iterator_next(it);
    }

    return it;
}

void print_list(command_func_args *args){
    int_list_iterator it = int_list_begin(args->list);

    fprintf(args->fout, "List: ");
    if(!int_list_iterator_is_equals(it, int_list_end(args->list))){
        if(args->it != NULL && int_list_iterator_is_equals(*args->it, it))
            fprintf(args->fout, "[(%d)]", int_list_iterator_get_val(it));
        else
            fprintf(args->fout, "[%d]", int_list_iterator_get_val(it));
        int_list_iterator_next(&it);
    } else{
        if(args->it != NULL && int_list_iterator_is_equals(it, *args->it))
            fprintf(args->fout, "[(END)] ");
        fprintf(args->fout, "is empty.\n");
        return;
    }
    while(!int_list_iterator_is_equals(it, int_list_end(args->list))){
        if(args->it != NULL && int_list_iterator_is_equals(*args->it, it))
            fprintf(args->fout, "->[(%d)]", int_list_iterator_get_val(it));
        else
            fprintf(args->fout, "->[%d]", int_list_iterator_get_val(it));
        int_list_iterator_next(&it);
    }
    if(args->it != NULL && int_list_iterator_is_equals(*args->it, int_list_end(args->list)))
        fprintf(args->fout, "->[(END)]");
    fprintf(args->fout, "\n");
}

void insert(command_func_args *args){
    if(args->cmd.id == -1){
        if(args->it == NULL){
            fprintf(args->fout, "Curr iterator is NULL. Get a new iterator (end | first | get-iter).\n");
        } else {
            if(int_list_iterator_insert_before(args->it, args->cmd.value) == false){
                fprintf(args->fout, "Can't insert.\n");
            }
        }
    } else {
        int_list_iterator *it = get_iter_by_index_el(*args, args->cmd.id);
        if(int_list_iterator_insert_before(it, args->cmd.value) == false){
            fprintf(args->fout, "Can't insert.\n");
        }
        free(it);
    }
}

void remove_elem(command_func_args *args){
    if(args->cmd.id == -1){
        if(args->it == NULL){
            fprintf(args->fout, "Curr iterator is NULL. Get a new iterator (end | first | get-iter).\n");
        } else {
            if(int_list_iterator_remove(args->it) == false){
                fprintf(args->fout, "Can't remove.\n");
            }
        }
    } else {
        int_list_iterator *it = get_iter_by_index_el(*args, args->cmd.id);
        if(int_list_iterator_remove(it) == false){
            fprintf(args->fout, "Can't remove.\n");
        }
        free(it);
    }
}

void reverse(command_func_args *args){
    int_list_reverse(args->list);
    free(args->it);
    args->it = NULL;
}

void get_size_list(command_func_args *args){
    fprintf(args->fout, "Size of list: %ld.\n", int_list_get_size(args->list));
}

void next_iter(command_func_args *args){
    if(args->it == NULL){
        fprintf(args->fout, "Curr iterator is NULL. Get a new iterator (end | first | get-iter).\n");
    }
    else if(int_list_iterator_is_equals(*args->it, int_list_end(args->list))){
        fprintf(args->fout, "Curr iterator points to the end of list.\n");
    }
    else{
        int_list_iterator_next(args->it);
    }
    return;
}

void help(command_func_args *args){
    print_help(args->fout);
}

bool allocate_it(command_func_args *args){
    if(args->it == NULL){
        args->it = malloc(sizeof(int_list_iterator));
        if(args->it == NULL){
            fprintf(args->fout, "Сan't allocate memory for the iterator. Try later ahah.\n");
            return false;
        }
    }
    return true;
}

void get_fisrt_iter(command_func_args *args){
    if(allocate_it(args) == false)
        return;
    *args->it = int_list_begin(args->list);    
}

void get_end_iter(command_func_args *args){
    if(allocate_it(args) == false)
        return;
    *args->it = int_list_end(args->list);
}

void get_iter(command_func_args *args){
    args->it = get_iter_by_index_el(*args, args->cmd.id);
}

void get_val(command_func_args *args){
    if(args->cmd.id == -1){
        if(args->it == NULL){
            fprintf(args->fout, "Curr iterator is NULL. Get a new iterator (end | first | get-iter).\n");
        } else {
            if(int_list_iterator_is_equals(*args->it, int_list_end(args->list)))
                fprintf(args->fout, "Curr iterator points to the end of list.\n");
            else
                fprintf(args->fout, "%d\n", int_list_iterator_get_val(*args->it));
        }
    } else {
        int_list_iterator *it = get_iter_by_index_el(*args, args->cmd.id);
        if(it != NULL){
            if(int_list_iterator_is_equals(*it, int_list_end(args->list)))
                fprintf(args->fout, "This index points to the end of list.\n");
            else
                fprintf(args->fout, "%d\n", int_list_iterator_get_val(*it));
        }
        free(it);
    }
}

void set_val(command_func_args *args){
    if(args->cmd.id == -1){
        if(args->it == NULL){
            fprintf(args->fout, "Curr iterator is NULL. Get a new iterator (end | first | get-iter).\n");
        } else {
            if(int_list_iterator_is_equals(*args->it, int_list_end(args->list)))
                fprintf(args->fout, "Curr iterator points to the end of list.\n");
            else
                int_list_iterator_set_val(*args->it, args->cmd.value);
        }
    } else {
        int_list_iterator *it = get_iter_by_index_el(*args, args->cmd.id);
        if(it != NULL){
            if(int_list_iterator_is_equals(*it, int_list_end(args->list)))
                fprintf(args->fout, "This index points to the end of list.\n");
            else
                int_list_iterator_set_val(*it, args->cmd.value);
        }
        free(it);
    }
}

void free_iter(command_func_args *args){
    free(args->it);
    args->it = NULL;
}

void unknown(command_func_args *args){
    fprintf(args->fout, "Unknown command, see help\n");
}

void err(command_func_args *args){
    fprintf(args->fout, "Invalid arguments, see help\n");
}

void none(command_func_args *args){
    ;
}

const command_info cmd_info_arr[] = {
    {"quit", "q", CMD_QUIT, GET_0_ARG, quit},
    {"print", "p", CMD_PRINT, GET_0_ARG, print_list},
    {"insert", "i", CMD_INSERT, GET_1_ARG | GET_2_ARG | VAL_CAN_1ST_ARG, insert},
    {"remove", "rm", CMD_REMOVE, GET_0_ARG | GET_1_ARG, remove_elem},
    {"reverse", "rv", CMD_REVERSE, GET_0_ARG, reverse},
    {"get-size-list", "size", CMD_SIZE, GET_0_ARG, get_size_list},
    {"next-iter", "n", CMD_NEXT, GET_0_ARG, next_iter},
    {"help", "h", CMD_HELP, GET_0_ARG, help},
    {"get-first-iter", "f", CMD_FIRST, GET_0_ARG, get_fisrt_iter},
    {"get-end-iter", "e", CMD_END, GET_0_ARG, get_end_iter},
    {"get-iter", "get-iter", CMD_GET_ITER, GET_1_ARG, get_iter},
    {"get-val", "get", CMD_GET_VALUE, GET_0_ARG | GET_1_ARG, get_val},
    {"set-val", "set", CMD_SET_VALUE, GET_1_ARG | GET_2_ARG | VAL_CAN_1ST_ARG, set_val},
    {"free-iter", "free", CMD_FREE_ITER, GET_0_ARG, free_iter},
    {"__UNKNOWN__", "", CMD_UNKNOWN, CANT_WRITE, unknown},
    {"__ERR__", "", CMD_ERR, CANT_WRITE, err},
    {"__NONE__", "", CMD_NONE, CANT_WRITE, none},
};