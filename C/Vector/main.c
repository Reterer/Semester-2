#include <stdio.h>
#include "vector.h"

int main(){
    VectorInt* vec = makeVectorInt(10);
    VectorIntSet(vec, 0, 666);
    for(int i = 0; i < vec->size; ++i){
	printf("%i %i\n", i, VectorIntGet(vec, i));
    }
    VectorIntResize(vec, 15);
    for(int i = 0; i < vec->size; ++i){
	printf("%i %i\n", i, VectorIntGet(vec, i));
    }
    delVectorInt(vec);
    return 0;   
}
