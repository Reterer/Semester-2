#define T int
#define T_COMPARE(X,Y) (X==Y)
#include <vector/vector_template.c>
#undef T_COMPARE
#undef T

#define T double
#define T_COMPARE(X,Y) (X==Y)
#include <vector/vector_template.c>
#undef T_COMPARE
#undef T