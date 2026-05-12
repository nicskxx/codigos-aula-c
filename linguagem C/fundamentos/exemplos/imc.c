/*
calcua o imc de uma pessoa com valores fixos nas variaveis e mostre o valor ao final*/
#include <stdio.h>
int main (){
    float peso = 61;
    float altura = 1.75;
    float imc = (peso/(altura*altura));
    printf("o imc e %f",imc);
    return 0;
} 