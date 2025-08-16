#include <stdio.h>

int sum(int a, int b);

int main()
{
    int a, b;
    if (scanf("%d %d", &a, &b) != 2)
    {
        printf("n/a\n");
        return 0;
    }

    printf("%d %d %d ", a + b, a - b, a * b);
    if (b != 0)
        printf("%d\n", a / b) ;
    else
        printf("n/a\n");

    return 0;
}

int sum(int a, int b){
    return (2 * a * b) / (a - b);
}
