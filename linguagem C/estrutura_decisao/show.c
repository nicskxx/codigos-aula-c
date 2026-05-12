#include <stdio.h>
#include <stdbool.h>
int main (){

bool comprouingressoantes = true;
bool comprouingressonahora = false;
int comprou = 0;
printf("comprou ingresso antes? 0->nao 1-> sim:\n");
scanf("%d", &comprou);
printf("comprou na hora?0->nao 1-> sim:\n");
scanf("%d", &comprou);

comprouingressonahora = comprou;
comprouingressoantes = comprou;

if (comprouingressoantes || comprouingressonahora){
    printf("vai assistir o show !!!");
}else {
    printf("NAO vai assistir o show!!!");
}

    return 0;
    
}