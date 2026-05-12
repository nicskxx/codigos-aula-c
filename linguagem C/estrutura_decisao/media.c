#include <stdio.h>

int main (){
 
float nota = 0;
int faltas = 0;
int ead = 0;

printf("qual a sua nota final do aluno?");
scanf("%F", &nota);

printf("quantas faltas o aluno teve?");
scanf("%i", &faltas);

printf("e o ead voce fez quantos porcento");
scanf("%i", & ead);

if (nota >= 50 && faltas <= 25 &&  ead == 100 ) {

printf("Esta aprovado");


} else {

    printf("esta reprovado");

}

    return 0;
    
}