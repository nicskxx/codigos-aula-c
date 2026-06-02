#include <stdio.h>

void calcularOrcamento() {
    float placaVideo = 139.90;
    float caixaSom = 99.90;
    float kitMouseTeclado = 149.90;
    float monitor = 679.90;

    float total = placaVideo + caixaSom + kitMouseTeclado + monitor;
    float totalAVista = total * 0.85;
    float parcela12x = total / 12;

    printf("ORCAMENTO DAS PECAS\n\n");

    printf("Placa de video: R$ %.2f\n", placaVideo);
    printf("Caixa de som: R$ %.2f\n", caixaSom);
    printf("Kit mouse e teclado: R$ %.2f\n", kitMouseTeclado);
    printf("Monitor 21 polegadas: R$ %.2f\n\n", monitor);

    printf("Valor total: R$ %.2f\n", total);
    printf("Valor a vista (15%% de desconto): R$ %.2f\n", totalAVista);
    printf("Parcelado em 12x: R$ %.2f por parcela\n\n", parcela12x);

    printf("Compra em grupo (6 pessoas)\n");
    printf("Valor por pessoa a vista: R$ %.2f\n", totalAVista / 6);
    printf("Valor por pessoa parcelado: R$ %.2f\n", total / 6);
}

int main() {
    calcularOrcamento();
    return 0;
}