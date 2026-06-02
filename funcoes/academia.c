#include <stdio.h>

float custoPorTreino(float mensalidade, int vezesSemana) {
    return mensalidade / (vezesSemana * 4);
}

float valorAnual(float parcela) {
    return parcela * 12;
}

int main() {
    float mensalViva = 49.99;
    float mensalSaude = 59.99;
    float mensalFitness = 69.99;

    float anualViva = valorAnual(39.99);
    float anualSaude = valorAnual(48.99);
    float anualFitness = valorAnual(58.99);

    printf("VIVA SAUDE\n");
    printf("Mensal: R$ %.2f\n", mensalViva);
    printf("Anual: R$ %.2f\n", anualViva);
    printf("Custo por treino: R$ %.2f\n\n", custoPorTreino(mensalViva, 3));

    printf("SAUDE EM DIA\n");
    printf("Mensal: R$ %.2f\n", mensalSaude);
    printf("Anual: R$ %.2f\n", anualSaude);
    printf("Custo por treino: R$ %.2f\n\n", custoPorTreino(mensalSaude, 4));

    printf("FITNESS PRO\n");
    printf("Mensal: R$ %.2f\n", mensalFitness);
    printf("Anual: R$ %.2f\n", anualFitness);
    printf("Custo por treino: R$ %.2f\n", custoPorTreino(mensalFitness, 7));

    return 0;
}