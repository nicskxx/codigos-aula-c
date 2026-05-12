#include <stdio.h>
int main (){

    // variaveis
    float atv1 = 0;
    float atv2 = 0;
    printf("qual a nota da atv 1?");
    scanf("%f", &atv1);
    printf("Qual a nota da atv 2?");
scanf("%f", &atv2);
//processamento
float total_atvs = (atv1+atv2);
float media = total_atvs/2;
//saida
if(media <= 6.9){

    printf("que pena sua media e %.2f", media);
    printf("----reprovado");

}else{
   
    printf("sua media e %.2f", media);
    printf("----aprovado");

}

    return 0;
} 