#include <stdio.h>
int main (){
    float peso = 0;

    float altura = 0;

    float Imc = (peso/(altura*altura));

    printf("qual sua atura");

    scanf("%f", &altura);

    printf("e seu peso?");
    scanf("%f", &peso);


    if (Imc >= 18.5 && Imc <= 24.9){

    printf("peso norma");
    }
    
   if (Imc >= 25.0 && Imc <= 29.9)
   {
    printf("peso idea");
   }
   if (Imc >= 30){

    printf("sobrepeso");
   }

printf("seu imc %.2f", Imc);
    

    return 0;
} 