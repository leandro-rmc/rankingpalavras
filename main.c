#include <stdio.h>
#include <stdlib.h>
#include "Mapa.h"

int main()
{
    Mapa mp;
    inicia_mapa(&mp);
    insere_termo(&mp, "Teste1");
    insere_termo(&mp, "Teste2");
    insere_termo(&mp, "Teste3");
    insere_termo(&mp, "Teste4");
    insere_termo(&mp, "Testa5");
    insere_termo(&mp, "Testa6");
    insere_termo(&mp, "Testw7");
    insere_termo(&mp, "Testw8");
    insere_termo(&mp, "Testw9");
    insere_termo(&mp, "Testw42");
    insere_termo(&mp, "Testw420");
    printf("Contador: %s\n",mp.lista[0]->termo);
    printf("Blocos: %i\n",mp.blocos);
    printf("Encontra Termo: %i\n", encontra_termo(&mp,"Testw420"));
    return 0;
}
