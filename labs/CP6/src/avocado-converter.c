#include "record/record.h"

int main(){
    record rcd;
    while(rcd_read(stdin, &rcd) == 1){
        rcd_bin_write(stdout, rcd);
    }
}