
#include <stdio.h>

int main() {
    float valorTotal = 0;
    float valorGasto =0;
    float valorPorPessoa =0;
    int totalPessoas = 0;

    printf("--- ROLE NO BK ---\n");
    printf("Quantas pessoas estao no grupo? ");
    scanf("%d", &totalPessoas);

    
    for (int i = 1; i <= totalPessoas; i++) {
        printf("Quanto a pessoa %d gastou? ", i);
        scanf("%f", &valorGasto);
        
       
        valorTotal += valorGasto;
    }

    
    valorPorPessoa = valorTotal / totalPessoas;

    printf("\n--- RESULTADO ---\n");
    printf("Total da conta: R$ %.2f\n", valorTotal);
    printf("Media por pessoa: R$ %.2f\n", valorPorPessoa);

    
    if (valorPorPessoa > 48.90) {
        printf("Cada um paga o seu!\n");
    } else {
        printf("Eu pago a conta!\n");
    }

    return 0;
}