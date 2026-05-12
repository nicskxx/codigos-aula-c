#include <stdio.h>
int main (){
//entrada
float salario = 0;
int temo = 0 ;
const float juros = 0.0068;
const float guarda25;

printf("quanto voce gostaria de guardar?");

scanf("%f", &salario);

printf("\nolá por quanto tempo gostaria de guardar?");

scanf("%i", temo);
//processamento
float totaljurosPercentual = temo * juros;
float salario25 = salario * guarda25;
float totaldinheiro = temo * salario25;
float totaljurosvalor = totaldinheiro * totaljurosPercentual;
float totalcomjuros = totaljurosvalor + totaldinheiro;







//saida
printf("total juros em %2.f\n", totaljurosPercentual);
printf("valor guardado sem juros R$ %2.f \n",totaldinheiro);
printf("meses %i \n",temo);
printf("valor guardado com juros %.2f \n",totaljurosvalor);
printf("valor guardado com juros %.2f",totalcomjuros);

return 0;
}
