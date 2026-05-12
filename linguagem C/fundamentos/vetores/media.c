#include <stdio.h>

int main() {
    float notas[4];
    float soma = 0;
    float media;
    int i;

    printf("--- Calculo de Media Dinamica ---\n");

    for (i = 0; i < 4; i++) {
        printf("Digite a %d nota: ", i + 1);
        scanf("%f", &notas[i]);
        soma += notas[i];
    }

    media = soma / 4;

    printf("\nnotas inseridas: ");
    for (i = 0; i < 4; i++) {
        printf("%.2f ", notas[i]);
    }

    printf("\nMedia final: %.2f\n", media);

    return 0;
}