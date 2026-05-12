#include <stdio.h>

int main() {
    int lados;
    float soma, angulo_individual;
    int diagonal;

    printf("--- Calculadora de Ângulos de Polígonos ---\n");
    printf("Digite o número de lados da figura: ");
    scanf("%d", &lados);
   

    // Validação: um polígono deve ter no mínimo 3 lados
    if (lados < 3) {
        printf("\nErro: Uma figura geométrica precisa de pelo menos 3 lados.\n");
    } else
        // Cálculo da soma dos ângulos internos
        soma = (lados - 2) * 180;

        // Cálculo do ângulo individual (considerando um polígono regular)
        angulo_individual = soma / lados;

        printf("\nResultados para um polígono de %d lados:\n", lados);
        printf("- Soma dos ângulos internos: %.2f°\n", soma);
        printf("- Cada ângulo interno (se for regular): %.2f°\n", angulo_individual);
       
        if (lados<3) {
            printf("\nErro tu é burro: Uma figura geométrica precisa de pelo menos 3 lados.");
        } else{
        diagonal = (lados*(lados-3))/2;
        printf("\n A diagonal é: %d", diagonal );
        }

       
    
   

    printf("\n------------------------------------------\n");
     return 0;
}