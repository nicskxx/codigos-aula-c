#include <stdio.h>
#include <locale.h>

void ola(){

    printf("Seja bem vindo");


}

void calcularMedia (float n1, float n2){


float media = (n1 + n2) / 2;


printf("A média é: %.2f", media);

}

int main (){
setlocale (LC_ALL, "pt_BR.UTF-8");

ola();

float n1 = 0;
float n2 = 0;

printf("\nEscreva a primeira nota");
scanf("%f", &n1);

printf("\nEscreva a segunda nota");
scanf("%f", &n2);



calcularMedia(n1, n2);




    return 0;
}