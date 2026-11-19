#include <stdio.h>

/* Extern storage class */
extern int global_token;
int global_token = 1000;

/* Static local variable */
int next_static(void)
{
    static int token = 1000;
    return ++token;
}

/* Automatic local variable */
int next_auto(void)
{
    int token = 1000;
    return ++token;
}

/* Extern global variable */
int next_global(void)
{
    return ++global_token;
}

int main(void)
{
    int s1 = next_static();
    int s2 = next_static();
    int s3 = next_static();

    int a1 = next_auto();
    int a2 = next_auto();
    int a3 = next_auto();

    int g1 = next_global();
    int g2 = next_global();
    int g3 = next_global();

    register int i;

    printf("static: %d %d %d\n", s1, s2, s3);
    printf("auto: %d %d %d\n", a1, a2, a3);
    printf("extern: %d %d %d\n", g1, g2, g3);

    printf("register loop: ");
    for (i = 1; i <= 3; ++i)
        printf("%d ", i);

    printf("\n");
    return 0;
}
