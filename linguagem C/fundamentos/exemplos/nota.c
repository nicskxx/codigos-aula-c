#include <stdio.h>
int main (){

    // variaveis
    int atv1 = 0;
    int atv2 = 0;
    printf("qual a nota da atv 1?");
    scanf("%i", &atv1);
    printf("Qual a nota da atv 2?");
scanf("%i", &atv2);
//processamento
int total_atvs = (atv1+atv2);
int media = (atv1+atv2)/2;
//saida
printf("A soma da nota é %i", total_atvs);
printf(" sua media e %i", media);
    return 0;
} 