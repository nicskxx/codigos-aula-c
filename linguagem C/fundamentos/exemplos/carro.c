#include <stdio.h>
int main (){
    float valorCarro = 0;
    int parcelas = 0;
    const float entrada30 = 0.30;

    printf("qual valor do carro?");
    scanf("%f", &valorCarro);
    printf("em quantas parcelas deseja pagar?");
    scanf("%i", &parcelas);

    float valorentrada = valorCarro*entrada30;
    float ValorMudado = valorCarro-valorentrada;

    printf("Para adquirir esse carro voce precisara dar %.3f como entrada", valorentrada);

    float valorparcelado = ValorMudado/parcelas;
    printf("\no valor de cada parcela será %.3f", valorparcelado);
    
    return 0;
    

}