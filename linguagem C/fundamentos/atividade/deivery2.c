#include <stdio.h>

float calcularvalorKm(int qtdeKmPercorridos) {
    if (qtdeKmPercorridos <= 100) return qtdeKmPercorridos * 0.20;
    if (qtdeKmPercorridos <= 200) return qtdeKmPercorridos * 0.45;
    if (qtdeKmPercorridos <= 300) return qtdeKmPercorridos * 0.80;
    return qtdeKmPercorridos * 1.05;
}

float calcularvalorentregas(int qtdeentregas) {
    if (qtdeentregas <= 10) return 7.99;
    if (qtdeentregas <= 20) return 16.99;
    if (qtdeentregas <= 30) return 25.00;
    return 41.99;
}

int main() {
    float totaldias = 0;
    float totalentragasseg = 0;
    float totalkmseg = 0;
    float totalentragaster = 0;
    float totalkmter = 0;
    float totalentragasqua = 0;
    float totalkmqua = 0;
    float totalentragasqui = 0;
    float totalkmqui = 0;
    float totalentragassex = 0;
    float totalkmsex = 0;
    float totalentragassab = 0;
    float totalkmsab = 0;
    float totalentragasdom = 0;
    float totalkmdom = 0;

    int kmsec = 0;
    int kmter = 0;
    int kmqua = 0;
    int kmqui = 0;
    int kmsex = 0;
    int kmsab = 0;
    int kmdom = 0;

    int entregasSE = 0;
    int entregasTE = 0;
    int entregasQUA = 0;
    int entregasQUI = 0;
    int entregasSEX = 0;
    int entregasSAB = 0;
    int entregasDOM = 0;

    int trabalhouSegunda = 0;
    int trabalhouTerca = 0;
    int trabalhouQuarta = 0;
    int trabalhouQuinta = 0;
    int trabalhouSexta = 0;
    int trabalhouSabado = 0;
    int trabalhouDomingo = 0;

    printf("Sou o algoritmo que ajuda o matias\n");

    printf("\nTrabalhou na segunda?(0 -> nao 1-> sim): ");
    scanf("%i", &trabalhouSegunda);
    if(trabalhouSegunda == 1) {
        totaldias++;
        printf("Quantas entregas fez? ");
        scanf("%i", &entregasSE);
        printf("Quantos KM percorridos? ");
        scanf("%i", &kmsec);
        totalentragasseg = calcularvalorentregas(entregasSE);
        totalkmseg = calcularvalorKm(kmsec);
    }

    printf("\nTrabalhou na terca?(0 -> nao 1-> sim): ");
    scanf("%i", &trabalhouTerca);
    if(trabalhouTerca == 1) {
        totaldias++;
        printf("Quantas entregas fez? ");
        scanf("%i", &entregasTE);
        printf("Quantos KM percorridos? ");
        scanf("%i", &kmter);
        totalentragaster = calcularvalorentregas(entregasTE);
        totalkmter = calcularvalorKm(kmter);
    }

    printf("\nTrabalhou na quarta?(0 -> nao 1-> sim): ");
    scanf("%i", &trabalhouQuarta);
    if(trabalhouQuarta == 1) {
        totaldias++;
        printf("Quantas entregas fez? ");
        scanf("%i", &entregasQUA);
        printf("Quantos KM percorridos? ");
        scanf("%i", &kmqua);
        totalentragasqua = calcularvalorentregas(entregasQUA);
        totalkmqua = calcularvalorKm(kmqua);
    }

    printf("\nTrabalhou na Quinta?(0 -> nao 1-> sim): ");
    scanf("%i", &trabalhouQuinta);
    if(trabalhouQuinta == 1) {
        totaldias++;
        printf("Quantas entregas fez? ");
        scanf("%i", &entregasQUI);
        printf("Quantos KM percorridos? ");
        scanf("%i", &kmqui);
        totalentragasqui = calcularvalorentregas(entregasQUI);
        totalkmqui = calcularvalorKm(kmqui);
    }

    printf("\nTrabalhou na sexta?(0 -> nao 1-> sim): ");
    scanf("%i", &trabalhouSexta);
    if(trabalhouSexta == 1) {
        totaldias++;
        printf("Quantas entregas fez? ");
        scanf("%i", &entregasSEX);
        printf("Quantos KM percorridos? ");
        scanf("%i", &kmsex);
        totalentragassex = calcularvalorentregas(entregasSEX);
        totalkmsex = calcularvalorKm(kmsex);
    }

    printf("\nTrabalhou no sabado?(0 -> nao 1-> sim): ");
    scanf("%i", &trabalhouSabado);
    if(trabalhouSabado == 1) {
        totaldias++;
        printf("Quantas entregas fez? ");
        scanf("%i", &entregasSAB);
        printf("Quantos KM percorridos? ");
        scanf("%i", &kmsab);
        totalentragassab = calcularvalorentregas(entregasSAB);
        totalkmsab = calcularvalorKm(kmsab);
    }

    printf("\nTrabalhou no Domingo?(0 -> nao 1-> sim): ");
    scanf("%i", &trabalhouDomingo);
    if(trabalhouDomingo == 1) {
        totaldias++;
        printf("Quantas entregas fez? ");
        scanf("%i", &entregasDOM);
        printf("Quantos KM percorridos? ");
        scanf("%i", &kmdom);
        totalentragasdom = calcularvalorentregas(entregasDOM);
        totalkmdom = calcularvalorKm(kmdom);
    }

    int totalentregas = entregasSE + entregasTE + entregasQUA + entregasQUI + entregasSEX + entregasSAB + entregasDOM;
    int totalkm = kmsec + kmter + kmqua + kmqui + kmsex + kmsab + kmdom;
    float totalgeral = (totalentragasseg + totalkmseg) + (totalentragaster + totalkmter) + (totalentragasqua + totalkmqua) + (totalentragasqui + totalkmqui) + (totalentragassex + totalkmsex) + (totalentragassab + totalkmsab) + (totalentragasdom + totalkmdom);

    printf("\nTotal entregas: %i", totalentregas);
    printf("\nTotal de kms: %i", totalkm);

    if (totaldias > 0) {
        float mediaEntregas = (float)totalentregas / totaldias;
        printf("\nMedia entregas por dia: %.2f", mediaEntregas);
        printf("\nMedia valor por dia: R$ %.2f", totalgeral / totaldias);

        if (totaldias == 7 && totalkm >= 200 && mediaEntregas >= 26) {
            printf("\nBonus de R$ 178,99 aplicado!");
        }
    }

    return 0;
}