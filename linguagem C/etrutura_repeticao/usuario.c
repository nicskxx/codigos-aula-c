#include <stdio.h>

int main (){
    int inicio = 0;
    int fim = 0;
 
    printf("um numero de até 4 digitos ");
    printf("\n inicio-");
    scanf("%d", inicio);

    
    if (inicio < 0) 
    {
        printf("invalido");
    }else {
        printf("qual numero para o fim?(deve ser maior que o numero inicial)");
        scanf("%i", &fim);

        if (fim >= inicio)
        {
         for (int i = inicio; i <= fim; i++)
         {
            printf("numeros %i\n", i);
         }
         
            
        }else{

            printf("numeros invalidos");
            printf("inicio %i, Fim %i", inicio, fim);
        }
        
     

    }
    

    
    

    return 0;
    
}