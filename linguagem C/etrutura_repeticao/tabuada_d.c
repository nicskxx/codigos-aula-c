#include <stdio.h>

int main (){
    int num = 0;
    

    

    do{ 

    printf("qual tabuada deseja fazer");
    scanf("%i", &num);

    for (int t = 0; t <= num * 10 ; t += num)
    {
        printf("\n %i x %i = %i", num, t / num , t );
        
    }
    printf("\ndeseja continuar 0 para sair");
    scanf("%i", &num);
    
        
    } while (num !=0);
    printf("FIM");
    


    return 0;
    