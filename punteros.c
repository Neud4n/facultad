// This is real C shit

#include <stdio.h>

void swap(int* a, int* b){
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

int setNum(int* num){
    printf("Ingrese un número\n");
    scanf("%d",&(*num));
}

void main()
{
    int a, b;
    setNum(&a);
    setNum(&b);
    printf("a --> %i\nb --> %i\n", a, b);
    swap(&a, &b);
    printf("Después del intercambio...\n");
    printf("a --> %i\nb --> %i\n", a, b);
}