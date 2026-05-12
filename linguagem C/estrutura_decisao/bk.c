#include <stdio.h>

int main (){

    float valorrodeio = 0;
    float batatagrande = 0;
    float refri = 0;
    float sobremesa = 0;


printf("qual o valor do lanche");

scanf("%f", &valorrodeio);

printf("e a sobremesa?");

scanf("%f", &sobremesa);

printf("e o refri?");

scanf("%f", &refri);

printf("e a batata, nao pode faltar");

scanf("%f", &batatagrande);

float valorfinal = valorrodeio + refri + batatagrande + sobremesa;

if (valorfinal < 40){
    printf("pode comprar esta barato R$ %.2f", valorfinal);
}else if (valorfinal >= 40 && valorfinal <= 55){
    printf("EEeeh Razoavel R$ %.2f", valorfinal);
}else if (valorfinal > 55){
    printf("Caaaaaaaaroooooo R$ %.2f", valorfinal);
}





    return 0;
    
}