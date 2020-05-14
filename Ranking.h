#ifndef RANKING_H_INCLUDED
#define RANKING_H_INCLUDED
#include <stdio.h>
#include "Mapa.h"
#include "ContainerPalavras.h"

enum status_ranking{SemArquivo, ComArquivo};

typedef struct _rankingConfig{
	int minimo_intervalo;
	int maximo_intervalo;
} RankingConfig;

typedef struct _ranking{
	Mapa *mapa;
	char *nome_arquivo;
	enum status_ranking status; // usar enum depois
	//0 = sem palavras, 1 = com palavras
	RankingConfig *rankingConfig;
} Ranking;

Ranking* obter_ranking();
void inicia_ranking(Ranking *ranking);
int absorver_palavras_arquivo(Ranking *ranking, char *nome_arquivo);
void limpar_ranking(Ranking *ranking);
void libera_ranking(Ranking *ranking);
void imprimir_ranking(Ranking *ranking, int intevalo_minimo, int intervalo_maximo);
ContainerPalavras* obter_palavras_filtradas(Ranking *ranking, int intevalo_minimo, int intervalo_maximo);

//void libera_palavras(Palavras palavras); //Importante após cada busca! Prefiro fazer static e de forma automatica pelo obter_palavras_filtradas
//Ou criar uma função pro usuário usar

#endif // RANKING_H_INCLUDED
