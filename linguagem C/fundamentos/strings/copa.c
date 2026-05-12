#include <stdio.h>
#include <locale.h>

int main () {

setlocale(LC_ALL, "pt_BR.UTF-8");
char grupoBrasil[4][50];
int resultados [3][2];

printf("vamos preencher o grupo do Brasil na copa");

for (int i = 0; i < 4; i++)
{
    printf("\nQual seleção?");
    scanf(" %s", grupoBrasil);


}

printf("que legal vamos agora aos jogos e seus resultados");

for (int i = 0; i < 3; i++)
{
    printf("\nPartida %i: %s x %s, i+1, grupoBrasil[0], grupoBrasil[i+1]");
    scanf("%i x %i", &resultados[i][1], &resultados[i][1]);

}

printf("\n%s %i x %i %s",
grupoBrasil[0], resultados[0][i], resultados[1][i], grupoBrasil[i+1]);

if (resultados[1][0] == resultados[i][1])
{
    totalpontosbrasil   
}




    return 0;
}