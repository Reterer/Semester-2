#include <stdio.h>

void gotoxy(int x, int y)
{
    printf("%c[%d;%df", 0x1B, y, x);
}

int main(void)
{
    while (1)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        gotoxy(x, y);
    }
    return 0;
}