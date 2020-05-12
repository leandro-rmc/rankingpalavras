#ifndef RANKING_H_INCLUDED
#define RANKING_H_INCLUDED
#include <stdio.h>
#include "Mapa.h"

typedef struct _rankingConfig{
	int minimo_intervalo;
	int maximo_intervalo;
} RankingConfig;

typedef struct _ranking{
	Mapa *mapa;
	char *nome_arquivo;
	RankingConfig *rankingConfig;
} Ranking;

/*Refatorar para retornar um vetor de palavras ao invés de imprimir diretamente na tela
typedef struct _palavra{
    int quantidade;
    char *palavra;
} Palavra;
*/

Ranking* obter_ranking();
void inicia_ranking(Ranking *ranking);
int absorver_palavras_arquivo(Ranking *ranking, char *nome_arquivo);
void limpar_ranking(Ranking *ranking);
void libera_ranking(Ranking *ranking);
void imprimir_ranking(Ranking *ranking, int intevalo_minimo, int intervalo_maximo);
void obter_quantidade(Ranking *ranking, int *total_repetindo, int *total_diferente, int intevalo_minimo, int intervalo_maximo);
#endif // RANKING_H_INCLUDED
