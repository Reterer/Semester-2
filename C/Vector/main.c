#include <stdio.h>
#include "vector.h"

int main(){
    Vector* v = NULL;
    VectorInit(&v, 10);
    VectorFill(v, 123);
    for(size_t i = 0; i < VectorSizeGet(v); ++i){
        printf("%f\n", VectorGet(v, i));
    }
    return 0;
}
