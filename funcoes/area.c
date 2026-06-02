#include <stdio.h>
#include <locale.h>

void area (float raio, float quadrado){
 
    float areacirculo = 3.14 * (raio * raio);
    float areaqudrado = quadrado * quadrado;



}

int main (){

setlocale (LC_ALL, "pt_BR.UTF-8");

float lado = 0;
float raio = 0;

printf("Quanto vale o lado do quadrado?");
scanf("%f", &lado);
printf("sua area é de: %.2f", raio);

    return 0;
}