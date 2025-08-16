# include<stdio.h>

int max(int a, int b);

int main(void)
{
    int a, b;
    if (scanf("%d %d", &a, &b) != 2)
    {
        printf("n/a\n");
        return 0;
    }


    printf("%d\n", max(a, b));
    return 0;

}

int max(int a, int b){
    return (a > b) ? a : b;
}
