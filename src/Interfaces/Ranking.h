#ifndef RANKING_H_INCLUDED
#define RANKING_H_INCLUDED
#include <stdio.h>
#include <limits.h>
#include "Mapa.h"
#include "ContainerPalavras.h"
#define TAMANHO_MAXIMO_PALAVRA_ARQUIVO 50
#define MINIMO_INTERVALO_PADRAO 1
#define MAXIMO_INTERVALO_PADRAO INT_MAX
#define MINIMO_CARACTERES_PADRAO 1

enum status_ranking{SemArquivo, ComArquivo};

typedef struct _ranking{
	Mapa *mapa;
	int minimo_caracteres;
	char *nome_arquivo;
	int status;
} Ranking;

Ranking* obter_ranking();
void inicia_ranking(Ranking *ranking);
int absorver_palavras_arquivo(Ranking *ranking, char *nome_arquivo);
void limpar_ranking(Ranking *ranking);
void libera_ranking(Ranking *ranking);
void imprimir_ranking(Ranking *ranking, int intevalo_minimo, int intervalo_maximo);
int obter_status_ranking(Ranking *ranking);
int obter_minimo_caracteres_ranking(Ranking *ranking);
int definir_limites_caractere_ranking(Ranking *ranking, int minimo_caracteres);
ContainerPalavras* obter_palavras_filtradas(Ranking *ranking, int intevalo_minimo, int intervalo_maximo);
SubContainerPalavra* buscar_palavra_filtrada(Ranking *ranking, int intevalo_minimo, int intervalo_maximo, char *palavra);
#endif // RANKING_H_INCLUDED
