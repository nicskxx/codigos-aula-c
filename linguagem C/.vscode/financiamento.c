#include <stdio.h>

int main()
{

    const float Juros_Veiculo = 0.015;
    const float Juros_Imovel = 0.005;

    int resposta;
    int opcao = 0;
    int meses = 0;
    float valor, renda, parcela, total;
    int aprovado = 0;
    char nome[50];

    

        printf("Digite o nome do cliente");
        scanf("%s", nome);

        printf("Digite a renda mensal do cliente");
        scanf("%f", &renda);

        printf("1 - Caminhao\n");
        printf("2 - Carro\n");
        printf("3 - Moto\n");
        printf("4 - Casa\n");
        printf("5 - Apartamento\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        printf("Digite o valor do financiamento");
        scanf("%f", &valor);

        do
        {
            printf("Digite a quantiedade de meses:");
            scanf("%d", &meses);

            switch (opcao)
            {
            case 1:

                if (meses >= 100 && meses <= 200)
                    aprovado = 1;

                else
                    printf("prazo inválido para caminhão\n");

                break;

            case 2:
                if (meses >= 6 && meses <= 48)
                    aprovado = 1;
                else
                    printf("prazo inválido para carro\n");

                break;
            case 3:
                if (meses >= 3 && meses <= 24)
                    aprovado = 1;

                else
                    printf("prazo inválido para moto\n");
                break;

            case 4:
                if (meses >= 150 && meses <= 360)
                    aprovado = 1;

                else
                    printf("prazo inválido para casa\n");
                break;

            case 5:
                if (meses >= 100 && meses <= 300)
                    aprovado = 1;

                else
                    printf("prazo inválido para caminhão\n");
                break;

            default:
                printf("opcao invalida");
                break;
            }

        } while (aprovado == 0);

         float entrada = 0;
        printf("DESEJA DAR ENTRADA: se sim digite o valor da entrada se não digite 0");
        scanf("%f", &entrada);

        if (opcao >= 1 && opcao <= 3)
        {
            valor = valor - entrada;
            total =  valor + (valor * Juros_Veiculo * meses);
        
        }
        else
        {
            valor = valor - entrada;
            total =  valor + (valor * Juros_Imovel * meses);
           
        }

       
        

        parcela = total / meses;

        if (parcela <= renda * 0.30)
        {
            printf("\n----------Financiamento Aprovado----------\n");
            printf("Clientes: %s\n", nome);
            printf("Valor total: R$ %.2f\n", total);
            printf("Quantiedade de parcelas: %d\n", meses);
            printf("Valor das Parcelas: R$ %.2f\n", parcela);
            printf("entrada : R$ %.2f", entrada);
        }
        else
        {

            printf("\n----------Financiamento Negado------------\n");
            printf("\nCliente %s a parcela ultrapassa 30 porcento de sua renda mensal\n", nome);
            printf("Valor total: R$ %.2f\n", total);
            printf("Quantiedade de parcelas: %d\n", meses);
            printf("Valor das Parcelas: R$ %.2f\n", parcela);
            printf("entrada : R$ %.2f", entrada);
        }

       printf("\n--------DESENVOVIDO POR NICOLAS DE CAMPOS------- \n");

   

    return 0;
}