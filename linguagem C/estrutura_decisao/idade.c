#include <stdio.h>

int main (){

    int idade = 0;

    printf("qual sua idade?");

    scanf("%i", &idade);

    if( idade >= 18) {
        printf("voce e maior de idade, pode trabalhar");
    } else {
        printf("voce e menor de idade,aproveite");
    }
    return 0;

}