#include <stdio.h>
#include <stdlib.h>
#include "Mapa.h"

//Funções super básicas apenas para não ficar em branco aqui
//A segunda metade do trabalho usará todas as funções do TAD

Mapa mp;

void imprimirTodasPalavras(){
    char t[100];
    int c;
    for (int i = 0; i<= mp.total - 1; i++){
        le_termo(&mp,i,t,&c);
        printf("%s - %i\n", t, c);
    }
}

int main()
{
    inicia_mapa(&mp);
    insere_termo(&mp, "Teste (X)");
    insere_termo(&mp, "Teste (Y)");
    insere_termo(&mp, "Teste (Z)");
    insere_termo(&mp, "Teste (Z)");
    insere_termo(&mp, "Teste (Z)");
    insere_termo(&mp, "Teste (W)");
    insere_termo(&mp, "Teste (W)");
    insere_termo(&mp, "Teste (W)");
    insere_termo(&mp, "Teste (W)");

    remove_termo(&mp, "Teste (y)");
    imprimirTodasPalavras();
    return 0;
}
