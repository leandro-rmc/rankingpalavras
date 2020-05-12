#ifndef RANKING_H_INCLUDED
#define RANKING_H_INCLUDED
#include <stdio.h>
#include "Mapa.h"

typedef struct _rankingConfig{
    char separador_palavras;
	int minimo_caracteres;
	int maximo_caracteres;
} RankingConfig;

typedef struct _ranking{
	Mapa *mapa;
	char *nome_arquivo;
	RankingConfig *rankingConfig;
} Ranking;

Ranking* obter_ranking();
void inicia_ranking(Ranking *ranking);
int absorver_palavras_arquivo(Ranking *ranking, char *nome_arquivo);
void limpar_ranking(Ranking *ranking);
void libera_ranking(Ranking *ranking);
#endif // RANKING_H_INCLUDED
