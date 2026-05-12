#include <stdio.h>
#include <locale.h>

int main () {

setlocale(LC_ALL, "pt_BR.UF-8");

char unidade [1000];
char localização [1000];
char anoescolar [1000];
char periodo [1000];


printf("Em qual unidade sesi você estuda?");
scanf(" %[^\n]", unidade);
printf("\nonde fica?");
scanf(" %[^\n]", localização);
printf("em qual ano escolar você está?");
scanf(" %[^\n]", anoescolar);
printf("e em qual periodo esta do curso?");
scanf(" %[^\n]", periodo);

printf("informações dadas pelo usuário");
printf("\nunidade escolar: %s", unidade);
printf("\nlocaização: %s", localização);
printf("\nano escolar: %s", anoescolar);
printf("\n periodo: %s", periodo);



return 0;
}