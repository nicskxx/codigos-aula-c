#include <stdio.h>

void mostrarTabuada(int numero, int inicio, int fim) {
    int inferior, superior;

    if (inicio < fim) {
        inferior = inicio;
        superior = fim;
    } else {
        inferior = fim;
        superior = inicio;
    }

    printf("\nTabuada do %d (de %d ate %d):\n", numero, inferior, superior);

    for (int i = inferior; i <= superior; i++) {
        printf("%d x %d = %d\n", numero, i, numero * i);
    }
}

int main() {
    int num, ini, fim;

    printf("Digite o numero da tabuada: ");
    scanf("%d", &num);

    printf("Digite o inicio da tabuada: ");
    scanf("%d", &ini);

    printf("Digite o fim da tabuada: ");
    scanf("%d", &fim);

    mostrarTabuada(num, ini, fim);

    return 0;
}
