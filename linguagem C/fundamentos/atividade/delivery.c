#include <stdio.h>

float calcularvalorKm(int qtdeKmPercorridos){

if (qtdeKmPercorridos <= 100)
{
    return qtdeKmPercorridos * 0.20;

}

if (qtdeKmPercorridos > 100 && qtdeKmPercorridos <= 200)
{
    return qtdeKmPercorridos * 0.45;
}

if (qtdeKmPercorridos > 200 && qtdeKmPercorridos <= 300)
{
    return qtdeKmPercorridos * 0.80;
}

if (qtdeKmPercorridos > 300)
{
    return qtdeKmPercorridos * 1.05;
}

}


float calcularvalorentregas(int qtdeentregas){

if (qtdeentregas <= 10)

{
   return 7.99;
}

if (qtdeentregas > 10 && qtdeentregas <=20)
{
    return 16.99;
}

if (qtdeentregas > 30)
{
    return 41.99;
}




}


int main (){




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
int kmsec =0;
int kmter =0;
int kmqua =0;
int kmqui =0;
int kmsex =0;     
int kmsab =0;
int kmdom =0;
int entregasSE = 0;
int entregasTE = 0;
int entregasQUA = 0;
int entregasQUI = 0;
int entregasSEX = 0;
int entregasSAB = 0;
int entregasDOM = 0;
int trabalhouSegunda = 0;
int trabalhouTerça = 0;
int trabalhouQuarta = 0;
int trabalhouQuinta = 0;
int trabalhouSexta = 0;
int trabalhouSabado = 0;
int trabalhouDomingo = 0;

printf("Sou o algoritmo que ajuda o matias\n");

printf("Trabalhou na segunda?(0 -> nao 1-> sim)");
scanf("%i", &trabalhouSegunda)
if(trabalhouSegunda == 1){
    totaldias++
    printf("quantas entregas fez?");
    scanf("%i", &entregasSe);

    printf("e quantos KM percorridos?");
    scanf("%i",&kmsec);
totalentragasseg = calcularvalorentregas(totalentragasseg);
totalkmseg = calcularvalorKm(kmsec);

}

printf("Trabalhou na terça?(0 -> nao 1-> sim)");
scanf("%i", &trabalhouTerça)

if(trabalhouTerça == 1){
    totaldias++
    printf("quantas entregas fez?");
    scanf("%i", &entregasTE);

    printf("e quantos KM percorridos?");
    scanf("%i",&kmter);

    totalentragaster = calcularvalorentregas(totalentragaster);
totalkmter = calcularvalorKm(kmter);

}


printf("Trabalhou na quarta?(0 -> nao 1-> sim)");
scanf("%i", &trabalhouQuarta)

if(trabalhouQuarta == 1){
    totaldias++
    printf("quantas entregas fez?");
    scanf("%i", &entregasQUA);

    printf("e quantos KM percorridos?");
    scanf("%i",&kmqua);


    totalentragasqua = calcularvalorentregas(totalentragasqua);
totalkmqua = calcularvalorKm(kmqua);

}


printf("Trabalhou na Quinta?(0 -> nao 1-> sim)");
scanf("%i", &trabalhouQuinta)

if(trabalhouQuinta == 1){
    totaldias++
    printf("quantas entregas fez?");
    scanf("%i", &entregasQUI);

    printf("e quantos KM percorridos?");
    scanf("%i",&kmqui);

    totalentragasqui = calcularvalorentregas(totalentragasqui);
    totalkmqui = calcularvalorKm(kmqi);

}


printf("Trabalhou na sexta?(0 -> nao 1-> sim)");
scanf("%i", &trabalhouSexta)

if(trabalhouSexta == 1){
    totaldias++
    printf("quantas entregas fez?");
    scanf("%i", &entregasSEX);

    printf("e quantos KM percorridos?");
    scanf("%i",&kmsex);

    totalentragassex = calcularvalorentregas(totalentragassex);
totalkmsex = calcularvalorKm(kmsex);


}


printf("Trabalhou na sabado?(0 -> nao 1-> sim)");
scanf("%i", &trabalhouSabado)

if(trabalhouSabado == 1){
    totaldias++
    printf("quantas entregas fez?");
    scanf("%i", &entregasSAB);

    printf("e quantos KM percorridos?");
    scanf("%i",&kmsab);

    totalentragassab = calcularvalorentregas(totalentragassab);
totalkmsex = calcularvalorKm(kmsab);

}


printf("Trabalhou na Domingo?(0 -> nao 1-> sim)");
scanf("%i", &trabalhouDomingo)
if(trabalhouDomingo == 1){
    totaldias++
    printf("quantas entregas fez?");
    scanf("%i", &entregasDOM);

    printf("e quantos KM percorridos?");
    scanf("%i",&kmdom);

totalentragasdom = calcularvalorentregas(totalentragasdom);
totalkmdom = calcularvalorKm(kmdom);

}

printf("\nsegunda-feira: %s", trabalhouSegunda == 1? "sim": "nao");
printf("\nQuantiedade de entregas: %i", entregasSE);
printf("\n KM percorridos: %i", kmsec);
printf("\n Valor a receber: R$ %.2f", totalentragasseg + totalkmseg);

printf("\nterça-feira: %s", trabalhouTerça == 1? "sim": "nao");
printf("\nQuantiedade de entregas: %i", entregasTE);
printf("\n KM percorridos: %i", kmter);
printf("\n Valor a receber: R$ %.2f", totalentragaster + totalkmter);

printf("\nquarta-feira: %s", trabalhouQuarta == 1? "sim": "nao");
printf("\nQuantiedade de entregas: %i", entregasQUA);
printf("\n KM percorridos: %i", kmqua);
printf("\n Valor a receber: R$ %.2f", totalentragasqua + totalkmqua);

printf("\nQuinta-feira: %s", trabalhouQuinta == 1? "sim": "nao");
printf("\nQuantiedade de entregas: %i", entregasQUI);
printf("\n KM percorridos: %i", kmqui);
printf("\n Valor a receber: R$ %.2f", totalentragasqui + totalkmqui);

printf("\nsexta-feira: %s", trabalhouSexta == 1? "sim": "nao");
printf("\nQuantiedade de entregas: %i", entregasSEX);
printf("\n KM percorridos: %i", kmsex);
printf("\n Valor a receber: R$ %.2f", totalentragassex + totalkmsex);

printf("\nsabadao: %s", trabalhouSabado == 1? "sim": "nao");
printf("\nQuantiedade de entregas: %i", entregasSAB);
printf("\n KM percorridos: %i", kmsab);
printf("\n Valor a receber: R$ %.2f", totalentragassab + totalkmsab);

printf("\nDomingo: %s", trabalhouDomingo == 1? "sim": "nao");
printf("\nQuantiedade de entregas: %i", entregasDOM);
printf("\n KM percorridos: %i", kmdom);
printf("\n Valor a receber: R$ %.2f", totalentragasdom + totalkmdom);



int totalentregas = entregasQUA+entregasTE+entregasQUA+entregasQUI+entregasSEX+entregasSAB+entregasDOM
printf("\nTotal entregas: %i", totalentregas);

int totalkm = kmsec+kmter+kmqua+kmqui+kmsex+kmsab+kmdom
printf("\nTotal de kms: %i", totalkm);

printf("media entregas por dia %i", totalentregas / totaldias);
float totalgeral = totalentragasdom + totalkmdom + totalentragassab + totalkmsab + totalentragassex + totalkmsex + totalentragasqui + totalkmqui + totalentragasqua + totalkmqua + totalentragaster + totalkmter + totalentragasseg + totalkmseg;

int media = totalentregas / totaldias;
if (totaldias == 7 && totalkm >= 200 &&  media >= 26)
{
    printf("Bonus de R$178,99");
}


printf("\nMedia valor por dia %.2f", totalgeral);







    return 0;
    
}