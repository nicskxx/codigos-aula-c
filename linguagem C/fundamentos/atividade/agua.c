#include <stdio.h> 

int main (){ 

//entrada de dados 

const float valorlitro = 0.60; 
int qtdepessoas = 0; 
const int multa = 400; 
const int desconto = 250; 
const float vaormulta = 150; 
const float valordesconto = 50;
 const int periodo30 = 30;
  float valorconta = 0;
   int quantiedadelitros = 0; 
   const int faixaexcessiva= 400; 
   const int faixaeconomica = 250;
    int idade = 0; 

//processamento 

printf("Ola vamos calcular sua conta de agua\n");  

printf("\n----------------------------\n)"; 

printf("Quantas pessoas moram em sua residencia? ");  

scanf("%i", &qtdepessoas); 

for (int i = 0; i < qtdepessoas; i++) {  

printf("Legal e agora qual idade da pessoas %i", i);  

scanf("%i", &idade); 

if (idade <= 10){ 

quantiedadelitros += 18;} 
 
else if (idade >10 && idade <= 18){ 
 
quantiedadelitros += 30;} 
 
else if (idade > 18 && idade <= 25){ 
 
quantiedadelitros += 42;} 
 
else (idade > 25); 
{ 
 
quantiedadelitros += 24;} 
 
valorconta = valorlitro*quantiedadelitros*periodo30; 
 
//saida 
if (quantiedadelitros >= faixaexcessiva) 
{ 
  printf("faixa de consumo: excessiva\n");  
  printf("TOTA DE PESSOAS NA RESIDENCIA: %i\n", qtdepessoas); 
  printf("quantiedade de consumo em litros: %i\n", quantiedadelitros); 
  printf("valor conta mensal: R$ %.3f",valorconta); 
  printf("valor da multa pro ter gastado mais que 400l aplicado de : R$%i",vaormulta);  
} 
else if (quantiedadelitros <= faixaeconomica) 
{ 
  printf("\nfaixa de consumo economica\n");  
  printf("TOTA DE PESSOAS NA RESIDENCIA: %i\n", qtdepessoas); 
  printf("quantiedade de consumo em litros: %i\n", quantiedadelitros); 
  printf("valor conta mensal: R$%.2f\n",valorconta); 
  printf("\nvalor do desconto por ter gastado apenas 250l ou menos aplicado de :R$i",desconto); 
} 
else  
{ 
printf("faixa de consumo:normal\n"); 
printf("TOTA DE PESSOAS NA RESIDENCIA: %i\n", qtdepessoas); 
printf("quantiedade de consumo em litros: %i\n", quantiedadelitros); 
printf("valor conta mensal: R$%.2f\n",valorconta); 
} 
 

} 

return 0;
 

} 

 