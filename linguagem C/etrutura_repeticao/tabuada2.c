#include <stdio.h>

int main (){
int tabuada = 4;
int tabuada2 = 1;
int res = 0;


     while (res <= 40)   {
         res = tabuada2 * tabuada;
             printf("\n %i x %i = %i", tabuada2, tabuada, res); 
         tabuada2++;
     }
     
     return 0;
}