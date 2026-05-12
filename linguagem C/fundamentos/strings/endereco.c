#include <stdio.h>
#include <locale.h>

int main() {

set locale(LC_ALL, "");
char nome[10] = "Nicolas"
char logradouro[20] = "Rua anhembi 365"
char bairro[12] = "são jorge"
char cidade[11] = "piracicaba"
char uf[3] = "SP"

printf("---minhas informações residenciais---");
printf("\n logradouro: %s", logradouro);
printf("\nBairro: %s", bairro);
printf("cidade: %s",cidade);
printf("uf: %s", uf);




    return 0;
}