#include <stdio.h>

int main (){
 int dia = 0;
 
 for (int i = 0; i < 7; i++)
 {
   
 
 
 printf("\nQual dia da samana? 1->dom, 7->sab");
 
 scanf("%i", &dia);

 switch (dia)
 {
 case 1:
    printf("\nDOMINGO triste");
    break;

 case 2:
 printf("\nsegundona, pra cima");
    break;

 case 3:
 printf("\nterça,meh");
    break;

 case 4:
 printf("\nquartou");
    break;

 case 5:
 printf("\nquintaa, quase la");
    break;

case 6:
    printf("\nsextou!!!");
    break;
case 7:
printf("\nsabadou dia de faxina");
break;

 }
 }

    return 0;
    
}