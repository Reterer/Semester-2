#include "command/command.h"
#include "help/help.h"
#include "log/log.h"

void quit(command_func_args *args){
    fprintf(args->fout, "Quit\n");
}

// Чем больше я знакомлюсь с Go,
// Тем чаще мне хочется написать val int, а не int val
typedef struct {
    int_list_iterator it;
    bool ok;
} get_iter_by_index_el_result;

// Данная функция возвращает ok = false, если итератор не может быть получен
// в пративном случае it и ok = true
get_iter_by_index_el_result get_iter_by_index_el(command_func_args args, size_t id){
    get_iter_by_index_el_result res;

    if(id > int_list_get_size(args.list)){
        fprintf(args.fout, "Index larger than the list size.\n");
        
        res.ok = false;
        return res;
    }
    
    res.ok = true;
    res.it = int_list_begin(args.list);
    for(size_t curr_id = 0; curr_id != id; ++curr_id){
        int_list_iterator_next(&res.it);
    }

    return res;
}

void _print_elem_list(command_func_args *args, int_list_iterator it, char *prefix){
    if(int_list_iterator_is_equals(it, int_list_end(args->list))){
        if(args->it != NULL && int_list_iterator_is_equals(*args->it, it))
            fprintf(args->fout, "%s[(END)]", prefix);
        return;
    }

    if(args->it != NULL && int_list_iterator_is_equals(*args->it, it))
        fprintf(args->fout, "%s[(%d)]", prefix, int_list_iterator_get_val(it));
    else
        fprintf(args->fout, "%s[%d]", prefix, int_list_iterator_get_val(it));
}

void print_list(command_func_args *args){
    int_list_iterator it = int_list_begin(args->list);

    fprintf(args->fout, "List: ");
    
    if(int_list_is_empty(args->list)){
        _print_elem_list(args, it, "");
        fprintf(args->fout, " is empty.\n");
        return;
    }

    _print_elem_list(args, it, "");
    while(!int_list_iterator_is_equals(it, int_list_end(args->list))){
        int_list_iterator_next(&it);
        _print_elem_list(args, it, "->");
    }
    fprintf(args->fout, "\n");
}
 
void insert(command_func_args *args){
    // Если не был указан id
    if(args->cmd.id == -1){
        if(args->it == NULL){
            fprintf(args->fout, "Curr iterator is NULL. Get a new iterator (end | first | get-iter).\n");
        } else {
            if(int_list_iterator_insert_before(args->it, args->cmd.value) == false)
                fprintf(args->fout, "Can't insert.\n");
        }
    // Иначе находим вставляем по id
    } else {
        get_iter_by_index_el_result res = get_iter_by_index_el(*args, args->cmd.id);
        if(res.ok){
            bool is_succ = false;
            // Если текущий итератор есть и полученный итератор совпадает с ним, то неплохо было бы обновить и его
            if(args->it != NULL && int_list_iterator_is_equals(*args->it, res.it))
                is_succ = int_list_iterator_insert_before(args->it, args->cmd.value);
            else
                is_succ = int_list_iterator_insert_before(&res.it, args->cmd.value);
            
            if(is_succ == false)
                fprintf(args->fout, "Can't insert.\n");
        }
    }
}

void remove_elem(command_func_args *args){
    if(args->cmd.id == -1){
        if(args->it == NULL){
            fprintf(args->fout, "Curr iterator is NULL. Get a new iterator (end | first | get-iter).\n");
        } else {
            if(int_list_iterator_remove(args->it) == false)
                fprintf(args->fout, "Can't remove.\n");
        }
    } else {
        get_iter_by_index_el_result res = get_iter_by_index_el(*args, args->cmd.id);
        if(res.ok){
            bool is_succ = false;
            if(args->it != NULL && int_list_iterator_is_equals(*args->it, res.it))
                is_succ = int_list_iterator_remove(args->it);
            else
                is_succ = int_list_iterator_remove(&res.it);
            
            if(is_succ == false)
                fprintf(args->fout, "Can't remove.\n");
        }
    }
}

// Разворачивает список по итераторам [l, r)
void reverse(command_func_args *args){
    int_list_iterator l = int_list_begin(args->list);
    int_list_iterator r = int_list_end(args->list);
    
    // Общая идея:
    // 1) Удалем первый елемент
    // 2) Вставляем его перед концом, 
    //      при этом сохраняя prev итератор и заменяя его на новый конец
    // 3) Повторяем 1 и 2 шаг пока l.next != r 
    // То есть получается этакое ДП, где на k-й итерации нужно развернуть [l, a), 
    // а [a,r0) - уже развернутый участок списка, где a = r - k + 1 
    // Пример:
    // [(1)]->[2]->[3]-[(4)]
    // l               r
    // [(2)]->[3]->[(1)]->[4]
    // [(3)]->[(2)]->[1]->[4]
    // l      r

    int_list_iterator l_next = l;
    int_list_iterator_next(&l_next);
    while(!int_list_iterator_is_equals(l_next, r)){
        int tmp = int_list_iterator_get_val(l);
        int_list_iterator_remove(&l);

        l_next = l;
        int_list_iterator_next(&l_next);

        int_list_iterator old_r = r;
        int_list_iterator_insert_before(&r, tmp);
        r = old_r;
    }
    
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

// Создание нового итератора
bool allocate_it(command_func_args *args){
    if(args->it != NULL)
        free(args->it);

    args->it = malloc(sizeof(int_list_iterator));
    if(args->it == NULL){
        fprintf(args->fout, "Сan't allocate memory for the iterator. Try later :c\n");
        return false;
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
    get_iter_by_index_el_result res = get_iter_by_index_el(*args, args->cmd.id);
    if(!res.ok)
        return;

    if(allocate_it(args) == false)
        return;
    
    *args->it = res.it;
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
        get_iter_by_index_el_result res = get_iter_by_index_el(*args, args->cmd.id);
        if(res.ok == false)
            return;
        
        if(int_list_iterator_is_equals(res.it, int_list_end(args->list)))
            fprintf(args->fout, "This index points to the end of list.\n");
        else
            fprintf(args->fout, "%d\n", int_list_iterator_get_val(res.it));
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
        get_iter_by_index_el_result res = get_iter_by_index_el(*args, args->cmd.id);
        if(res.ok == false)
            return;
        
        if(int_list_iterator_is_equals(res.it, int_list_end(args->list)))
            fprintf(args->fout, "This index points to the end of list.\n");
        else
            int_list_iterator_set_val(res.it, args->cmd.value);
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

void negative_id(command_func_args *args){
    fprintf(args->fout, "The id can only be positive.\n");
}

void none(command_func_args *args){
    ;
}

// Моё творение, этот массив служит для объявления команд
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
    {"__NEGATIVE_ID__", "", CMD_NEGATIVE_ID, CANT_WRITE, negative_id},
    {"__NONE__", "", CMD_NONE, CANT_WRITE, none},
};
// Может быть тут есть лишние команды, либо нет каких-то,
// Но всё, что надо сделать для добавления новой команды:
// Написать её обработчик, добавить её в этот массив и в enum command_type 