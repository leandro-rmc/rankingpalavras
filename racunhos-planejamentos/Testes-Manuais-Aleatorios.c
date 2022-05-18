#include <stdio.h>
#include <stdlib.h>
#include "Mapa.h"

//Apenas para eu testar algumas funcionalidades, nada a ser visto por aqui.

Mapa mp;

void imprimirTodasPalavras(){
    char t[100];
    int c;
    for (int i = 0; i<= mp.total - 1; i++){
        le_termo(&mp,i,t,&c);
        printf("%s - %i\n", t, c);
    }
}

void imprimirStatusDoMapa(){
    printf("Total de itens: %i\n", tamanho_mapa(&mp));
    printf("Total de blocos: %i\n", mp.blocos);
}

int main()
{
    inicia_mapa(&mp);
    insere_termo(&mp, "Teste1");
    insere_termo(&mp, "Teste2");
    insere_termo(&mp, "Teste3");
    insere_termo(&mp, "Teste4");
    insere_termo(&mp, "Testa5");
    insere_termo(&mp, "Testa6");
    insere_termo(&mp, "Testw7");
    insere_termo(&mp, "Testw8");
    insere_termo(&mp, "Testw8a");
    insere_termo(&mp, "Testw9");
    insere_termo(&mp, "Testw9");
    insere_termo(&mp, "Testw9");
    insere_termo(&mp, "Testw42");
    insere_termo(&mp, "Testw420");
    remove_termo(&mp, "Testw9");
    escreve_cont(&mp, "Testw9", 1);
    escreve_cont(&mp, "Testw9", 10);
    printf("C = %i\n", le_contador(&mp,"Teste1"));
    escreve_cont(&mp, "Teste1", 11);
    incrementa(&mp,"Teste1");
    printf("C = %i\n", le_contador(&mp,"Teste1"));

    //Possível bug na função de desfragmentar
    //Update: Bug Corrigido, era realmente na função de desfragmentar
    remove_termo(&mp, "Teste9");
    //remove_termo(&mp, "Teste1");
    char t[100];
    int c;
    le_termo(&mp,2,t,&c);
    printf("Termo no indice escolhido: %s\n",t);

    imprimirTodasPalavras();
    imprimirStatusDoMapa();
    remove_termo(&mp, "Teste1");
    printf("Termo encontrado? %i\n", encontra_termo(&mp,"Testw8a"));
    libera_mapa(&mp);
    printf("Termo encontrado? %i\n", encontra_termo(&mp,"Testw9"));
    printf("Termo encontrado? %i\n", encontra_termo(&mp,"Testw8a"));
    libera_mapa(&mp);
    //printf("Contador: %s\n",mp.lista[0]->termo);
    //printf("Blocos: %i\n",mp.blocos);
    //printf("Encontra Termo: %i\n", encontra_termo(&mp,"Testw420"));
    return 0;
}
