#include <stdio.h>

int main (){
int numero = 0;


     do   {
         
             printf("digite um numero ou 0 para sair:"); 
             scanf("%i", &numero);
         
     }while(numero !=0);
     printf("FIM");
     
     return 0;
}