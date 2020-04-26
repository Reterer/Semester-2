#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "command/command.h"
#include "list/int_list.h"
#include "help/help.h"

#define INVITATION_CHAR '>'

#define MAX_SIZE_INPUT_BUF  1280
#define MAX_LEN_COMMAND_STR 40
#define MAX_LEN_VALUE_STR   1024


int _split_line(char *line_buff, char *command_info, int *id, int *value){
    int read_code = sscanf(line_buff, "%39s %d %d\n", command_info, id, value);
    if(read_code == 2){
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

    char line_buff[MAX_SIZE_INPUT_BUF] = "";
    fprintf(fout, "%c ", INVITATION_CHAR);
    if(fgets(line_buff, MAX_SIZE_INPUT_BUF, fin) == NULL){
        printf("End of the file\n");
        res.type = CMD_QUIT;
        return res;
    }

    char command_str[MAX_LEN_COMMAND_STR] = "";
    int read_code = _split_line(line_buff, command_str, &res.id, &res.value);
    for(int cmd_id = 0; cmd_info_arr[cmd_id].type != CMD_NONE; cmd_id++){
        if(cmd_info_arr[cmd_id].flags & CANT_WRITE)
            continue;

        if(_cmp_in_and_cmd(command_str, cmd_info_arr[cmd_id])){
            if((read_code == 1 && (cmd_info_arr[cmd_id].flags & GET_0_ARG))\
            || (read_code == 3 && (cmd_info_arr[cmd_id].flags & GET_2_ARG))\
            ){ 
                res.type = cmd_info_arr[cmd_id].type;
                break;
            }
            else if(read_code == 2 && (cmd_info_arr[cmd_id].flags & GET_1_ARG)){
                if(cmd_info_arr[cmd_id].flags & VAL_CAN_1ST_ARG)
                    res.id = -1;
                res.type = cmd_info_arr[cmd_id].type;
                break;
            }
            res.type = CMD_ERR;
            break;
        }
    }
    // printf("%s %d %d | %d | %d\n", command_str, res.id, res.value, res.type, read_code);
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