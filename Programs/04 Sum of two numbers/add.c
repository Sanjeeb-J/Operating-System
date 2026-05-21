#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    int a, b;
    if (argc != 3)
    {
        printf("Usage: %s <num1> <num2>\n", argv[0]);
        return 1;
    }
    a = atoi(argv[1]);
    b = atoi(argv[2]);
    printf("Sum = %d\n", a + b);
    return 0;

    // Compile both
    // gcc add.c -o add
    // gcc adder.c -o myadder

    // Run
    // ./myadder 10 20
}