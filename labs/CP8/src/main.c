#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "command/command.h"
#include "list/int_list.h"

#define INVITATION_CHAR '>'

#define MAX_SIZE_INPUT_BUF  256
#define MAX_LEN_COMMAND_STR 40
#define MAX_LEN_VALUE_STR   30


typedef enum {
    READ_EMPTY = -1,
    READ_0_ARG = 1,
    READ_1_ARG = 2,
    READ_2_ARG = 3,
} read_code_status;

int _split_line(char *line_buff, char *command_info, int *id, int *value){
    int read_code = sscanf(line_buff, "%39s %d %d\n", command_info, id, value);
    
    // Если аргумент всего 1, то им может бать как и id, так и value
    if(read_code == READ_1_ARG){
        *value = *id;
    }

    return read_code;
}

bool _cmp_in_and_cmd(const char *input, const command_info cmd){
    return (strcmp(input, cmd.str_alt) == 0) || (strcmp(input, cmd.str) == 0);
}

command get_command(FILE *fin, FILE *fout){
    command res;
    res.type  = CMD_UNKNOWN;
    res.id    = -1;
    res.value = 0;

    // Считываем строку
    char line_buff[MAX_SIZE_INPUT_BUF] = "";
    fprintf(fout, "%c ", INVITATION_CHAR);
    if(fgets(line_buff, MAX_SIZE_INPUT_BUF, fin) == NULL){
        printf("End of the file.\n");
        res.type = CMD_QUIT;
        return res;
    }

    // Парсим строку
    char command_str[MAX_LEN_COMMAND_STR] = "";
    int read_code = _split_line(line_buff, command_str, &res.id, &res.value);
    
    if(read_code == READ_EMPTY){
        res.type = CMD_NONE;
        return res;
    }

    // Находим команду, которую ввел пользователь и проверям на корректность аргументов
    for(int cmd_id = 0; cmd_info_arr[cmd_id].type != CMD_NONE; cmd_id++){
        if(cmd_info_arr[cmd_id].flags & CANT_WRITE)
            continue;

        // Если команда подходит, то проверяем корректность аргументов
        if(_cmp_in_and_cmd(command_str, cmd_info_arr[cmd_id])){
            // Если команда не принимает аргументов
            if(read_code == READ_0_ARG && (cmd_info_arr[cmd_id].flags & GET_0_ARG)){
                res.type = cmd_info_arr[cmd_id].type;
                break;
            }
            // Если команда принимает один аргумент
            else if(read_code == READ_1_ARG && (cmd_info_arr[cmd_id].flags & GET_1_ARG)){
                // Если комманда принимает первым аргументом value
                if(cmd_info_arr[cmd_id].flags & VAL_CAN_1ST_ARG){
                    res.id = -1;
                }
                // Иначе она принимает первым аргументом id, проверяем его
                else {
                    if(res.id < 0) {
                        res.type = CMD_NEGATIVE_ID;
                        break;
                    }
                }
                
                // Если всё хорошо, то говорим, что мы выбрали нужную команду
                res.type = cmd_info_arr[cmd_id].type;
                break;
            }
            // Если команда принимает два аргумента
            else if(read_code == READ_2_ARG && (cmd_info_arr[cmd_id].flags & GET_2_ARG)){ 
                if(res.id < 0){
                    res.type = CMD_NEGATIVE_ID;
                    break;    
                }
                
                res.type = cmd_info_arr[cmd_id].type;
                break;
            }
            // Иначе (если введенны некоректные аргументы)
            res.type = CMD_ERR;
            break;
        }
    }
    
    // Возвращаем CMD_UNKNOWN либо найденную команду
    return res;
}

void handle_command(command_func_args *args){
    cmd_info_arr[args->cmd.type].handle(args);
}

void init_cmd_args(command_func_args *cmd_args){
    cmd_args->cmd.type  = CMD_NONE;
    cmd_args->fout      = stdout;
    cmd_args->it        = NULL;
    int_list_init(&cmd_args->list);
}

void deinit(command_func_args cmd_args){
    free(cmd_args.it);
    int_list_deinit(&cmd_args.list);
}

int main(){
    command_func_args cmd_args;
    init_cmd_args(&cmd_args);

    while (cmd_args.cmd.type != CMD_QUIT){
        cmd_args.cmd = get_command(stdin, stdout);
        handle_command(&cmd_args);
    }
    deinit(cmd_args);
    return 0;
}