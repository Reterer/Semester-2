#include <stdio.h>
#include <stdlib.h>
#include <log/log.h>

#include "config.h"

void transformation_matrix(config cnfg);

config handle_args(int argc,char* argv[]){
    config res = { stdin, stdout};
    if(argc == 1)
        return res;
    if(argc == 3){
        res.in = fopen(argv[1], "r");
        res.out = fopen(argv[2], "w");

        if(res.in == NULL)
            LOG_ERR("can't open input file");
        if(res.out == NULL)
            LOG_ERR("can't open input file");
        if(res.out == NULL || res.in == NULL)
            exit(1);

        return res;
    }

    printf("USAGE:\n");
    printf("\t   %s <in file> <out file>\n", argv[0]);
    printf("\tor %s \n", argv[0]);
    printf("EXAMPLES:\n");
    printf("\t   %s in_matrix.txt out_matrix.txt\n", argv[0]);
    printf("\t   %s < in_matrix.txt\n", argv[0]);
    return res;
}

int main(int argc,char* argv[]){
    config cnfg = handle_args(argc, argv);
    transformation_matrix(cnfg);
    return 0;
}