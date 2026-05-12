#include <stdio.h>

int main () {

    printf("imprimindo numeros pares e impares");

    for (int i = 0; i <= 100; i++)
    {
        if (i % 2 == 0)
        {
            printf("\n par : %i", i);
    
        }else{
            printf("\n impar: %i", i);
        }
    }


    return 0;
}