#include <stdio.h>

float calcular(int identificador, float num1, float num2) {
    switch (identificador) {
        case 1:
            return num1 + num2; 

        case 2:
            return num1 - num2; 

        case 3:
            return num1 * num2; 

        case 4:
            if (num2 == 0) {
                printf("Erro: divisao por zero.\n");
                return 0;
            }
            return num1 / num2; // Divisão

        default:
            printf("Operacao invalida.\n");
            return 0;
    }
}

int main() {
    int operacao;
    float num1, num2, resultado;

    printf("Escolha a operacao:\n");
    printf("1 - Soma\n");
    printf("2 - Subtracao\n");
    printf("3 - Multiplicacao\n");
    printf("4 - Divisao\n");
    printf("Digite o identificador: ");
    scanf("%d", &operacao);

    printf("Digite o primeiro numero: ");
    scanf("%f", &num1);

    printf("Digite o segundo numero: ");
    scanf("%f", &num2);

    resultado = calcular(operacao, num1, num2);

    printf("Resultado: %.2f\n", resultado);

    return 0;
}