#include <stdio.h>
#include <stdlib.h>
#include "Mapa.h"
#include "Ranking.h"

//Funções super básicas apenas para não ficar em branco aqui
//A segunda metade do trabalho usará todas as funções do TAD

typedef struct _test{
    int quantidade;
    char *test;
} Test;

int main()
{

    Ranking *ranking = obter_ranking();
    inicia_ranking(ranking);
    absorver_palavras_arquivo(ranking, "teste.txt");
    Palavras *palavras = obter_palavras_filtradas(ranking, ranking->rankingConfig->minimo_intervalo, ranking->rankingConfig->maximo_intervalo);
    printf("Total repetindo: %i\n",palavras->total_repetindo);
    printf("Total diferente: %i\n",palavras->total_diferente);
    int i;
    printf("[Lista de Palavras]\n");
    for (i = 1; i <= palavras->total_diferente; i++){
        printf("%s - ", palavras->palavras[i-1]->palavra);
        printf("%i\n", palavras->palavras[i-1]->quantidade);
    }
    char temp;
    printf("ENTER para finalizar...");
    scanf("%c",&temp);
    return 0;
}
