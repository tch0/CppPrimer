#include <stdio.h>
int main(int argc, char** argv)
{
    int a = 10LL;
    int b = a*10;
    printf("%d\n", b);
    printf("arguments count: %d\n", argc);
    if (argc >= 2)
    {
        printf("%s\n", argv[1]);
    }
    printf("hello");
    return -1;
}