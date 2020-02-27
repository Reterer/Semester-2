#include <stdio.h>

typedef struct {

} s;

int main(int argc, char* argv[]){
    if (argc != 3){
        fprintf(stderr, "USAGE: %s <input file> <output file>\n", argv[0]);
        return 1;
    }
    FILE* inputf = fopen(argv[1], "r");
    if (inputf == NULL){
        fprintf(stderr, "can't open file %s\n", argv[0]);
        return 2;
    }
    
    FILE* inputf = fopen(argv[1], "r");
    if (inputf == NULL){
        fprintf(stderr, "can't open file %s\n", argv[0]);
        return 2;
    }


        

    return 0;
}
