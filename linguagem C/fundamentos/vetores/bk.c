#include <stdio.h> 

int main()
{

    char lanches [4] [20] = {
        "Rodeio", "whooper", "cheddar duplo", "Big King"
    };

    printf("Meus lanches favoritos são:");

    for (int i = 0; i < 4; i++)
    {
       printf("\n %s", lanches[i]);
    }
    


    return 0;
}