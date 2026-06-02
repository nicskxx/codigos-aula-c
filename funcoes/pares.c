#include <stdio.h>

void mostrarPares(int limite1, int limite2) {
    int inferior, superior;

    if (limite1 < limite2) {
        inferior = limite1;
        superior = limite2;
    } else {
        inferior = limite2;
        superior = limite1;
    }

    printf("Numeros pares entre %d e %d:\n", inferior, superior);

    if (inferior % 2 != 0) {
        inferior++;
    }

    for (int i = inferior; i <= superior; i += 2) {
        printf("%d ", i);
    }
    printf("\n");
}

int main() {
    int n1, n2;

    printf("Digite o primeiro numero: ");
    scanf("%d", &n1);

    printf("Digite o segundo numero: ");
    scanf("%d", &n2);

    mostrarPares(n1, n2);

    return 0;
}
