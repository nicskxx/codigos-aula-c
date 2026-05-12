#include <stdio.h>

int main (){

    float cabelo = 29.99;
    float sobrancelha = 11.99;
    float dreads = 99.99;
    float risco = 4.99;
    float barba = 19.99;
    float bigode = 4.99;
    float luzes =50.00;
    float nevou = 59.90;
    int resposta = 0;
    float total = 0;
    int parcela = 0;
  


   
    
printf("Olá somos da KNM barber, e você gostaria de cortar seu cabelo conosco?(0 para sim 1 para não)");
 scanf("%d", &resposta);

 if (resposta == 0){
    printf("\nbelaza adicionado ao carrinho");
    total = cabelo;
 } else if (resposta == 1){
    printf("\nok  corte, não foi adicionado");
 } else {
    printf("\ninvalida resposta");
 }
 
 printf("\ne gostaria de adicionar sobrancelha ao carrinho?(0 para sim 1 para não)");
 scanf("%d", &resposta);

 if (resposta == 0){
    printf("\nbelaza adicionado ao carrinho");
    total = total + sobrancelha;
 } else if (resposta == 1){
    printf("\nok  sobrancelha, não foi adicionado");
 } else {
    printf("\ninvalida resposta");
 }

 printf("\nE gostaria de fazer dreads?(0 para sim 1 para não)");
 scanf("%d", &resposta);

 if (resposta == 0){
    printf("\nbelaza adicionado ao carrinho");
    total = total + dreads;
 } else if (resposta == 1){
    printf("\nok  dreads, não foi adicionado");
 } else {
    printf("\ninvalida resposta");
 }

 printf("\nE o risco na sobrancelha?(0 para sim 1 para não)");
 scanf("%d", &resposta);

 if (resposta == 0){
    printf("\nbelaza adicionado ao carrinho");
    total = total + risco;
 } else if (resposta == 1){
    printf("\nok  , não foi adicionado");
 } else {
    printf("\ninvalida resposta");
 }

 printf("\ngostaria de fazer a barba?(0 para sim 1 para não)");
 scanf("%d", &resposta);

 if (resposta == 0){
    printf("\nbelaza adicionado ao carrinho");
    total = total + barba;
 } else if (resposta == 1){
    printf("\nok  , não foi adicionado");
 } else {
    printf("\ninvalida resposta");
 }

 printf("\ngostaria de fazer o bigode?(0 para sim 1 para não)");
 scanf("%d", &resposta);

 if (resposta == 0){
    printf("\nbelaza adicionado ao carrinho");
    total = total + bigode;
 } else if (resposta == 1){
    printf("\nok  , não foi adicionado");
 } else {
    printf("\ninvalida resposta");
 }

 printf("\ngostaria de fazer nevou?(0 para sim 1 para não)");
 scanf("%d", &resposta);

 if (resposta == 0){
    printf("\nbelaza adicionado ao carrinho");
    total = total + nevou;
 } else if (resposta == 1){
    printf("\nok  , não foi adicionado");
 } else {
    printf("\ninvalida resposta");
 }

 printf("\ngostaria de fazer luzes?(0 para sim 1 para não)");
 scanf("%d", &resposta);

 if (resposta == 0){
    printf("\nbelaza adicionado ao carrinho");
    total = total + luzes;
 } else if (resposta == 1){
    printf("\nok  , não foi adicionado");
 } else {
    printf("invalida resposta");
 }
 printf("\nO valor de seu carrinho ficou no total %.2f", total);

 printf("\nGostaria de pagar a vista ou parcelado(0 para a vista 1 parcelado)");
 scanf("%i", &resposta);
 if (resposta == 1){
   printf("\nem quantas vezes gostaria de parcelar?");
   scanf("%i", &parcela);
   float totalparcelado = total/parcela;
   printf("\n-------CALCULANDO---------\n");
   printf("O total é %.2f", totalparcelado);
 } else  {
    float totalavista = total * 0.05;
    float totalfinal = total - totalavista;
    printf("Beleza dessa maneira forneceos 5 porcento de desconto.");
    printf("\n--------calculando----------");
    printf("\nO valor final é de %.2f", totalfinal);
 }
 

         return 0;


}