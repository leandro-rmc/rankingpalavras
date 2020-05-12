#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "Ranking.h"
#include "Mapa.h"
#define TAMANHO_MAXIMO_PALAVRA_ARQUIVO 50
#define SEPARADOR_PALAVRAS_ARQUIVO '\n'
#define MINIMO_INTERVALO_PADRAO 1
//Uma mudança no tipo de dado da quantidade na estrutura do Mapa poderá quebrar o código abaixo
//O certo seria obter o tipo de dados dela ao invés de tratar sempre como inteiro
#define MAXIMO_INTERVALO_PADRAO INT_MAX

//Move o ponteiro interno do arquivo para o início da próxima palavra
static void movPtrProxPalavraVocabulario(Ranking *ranking, FILE *arquivo){
    char temp;
    while (fscanf(arquivo,"%c",&temp) != EOF){
        if (temp == SEPARADOR_PALAVRAS_ARQUIVO)
            break;
    }
}
//Absorve 1 palavra do arquivo
static int absorver_palavra_arquivo(Ranking *ranking, FILE *arquivo){
    int parar = 0, i, resultado = 1;
    char *palavraAtual = malloc(sizeof(char) * TAMANHO_MAXIMO_PALAVRA_ARQUIVO + 1);
    //printf("Teste");
    for (i = 0; i <= TAMANHO_MAXIMO_PALAVRA_ARQUIVO - 2; i++){
        if (fscanf(arquivo,"%c",&palavraAtual[i]) == EOF){
            parar = 1;
            resultado = 0;
        }
        //printf("0");
        if (palavraAtual[i] == SEPARADOR_PALAVRAS_ARQUIVO)
            parar = 1;
        if (parar == 1){
            palavraAtual[i] = '\0';
            break;
        }
        //Se a variável de iteração tiver chegado ao seu fim, mas a palavra a ser lida do vocabulário...
        //... não, o ponteiro interno do arquivo precisa ser movido para a próxima palavra.
        if (i == TAMANHO_MAXIMO_PALAVRA_ARQUIVO - 2 && palavraAtual[i] != '\0'){
            movPtrProxPalavraVocabulario(ranking, arquivo);
        }
    }
    palavraAtual[i + 1] = '\0';
    palavraAtual = realloc(palavraAtual, strlen(palavraAtual) + 1);
    insere_termo(ranking->mapa,palavraAtual);
    printf("%s",palavraAtual);
    return resultado;
}
//Limpa o Ranking para ser usado novamente do zero (configurações permanecem)
void limpar_ranking(Ranking *ranking){
    ranking->nome_arquivo = NULL;
    if (ranking->mapa != NULL)
        libera_mapa(ranking->mapa);
    ranking->mapa = malloc(sizeof(Mapa));
    inicia_mapa(ranking->mapa);
}
void libera_ranking(Ranking *ranking){
    limpar_ranking(ranking);
    free(ranking->mapa);
    free(ranking);
}
Ranking* obter_ranking(){
    Ranking *ranking = malloc(sizeof(Ranking));
    inicia_ranking(ranking);
    return ranking;
}
void inicia_ranking(Ranking *ranking){
    free(ranking->mapa);
    free(ranking->rankingConfig);

    ranking->mapa = malloc(sizeof(Mapa));
    inicia_mapa(ranking->mapa);
    ranking->nome_arquivo = NULL;

    //Refatorar para remover o Hardcode
    ranking->rankingConfig = malloc(sizeof(RankingConfig));
    ranking->rankingConfig->minimo_intervalo = MINIMO_INTERVALO_PADRAO;
    ranking->rankingConfig->maximo_intervalo = MAXIMO_INTERVALO_PADRAO;
}
//Procura pelo arquivo com nome passado e obtém todas as palavras dele
int absorver_palavras_arquivo(Ranking *ranking, char *nome_arquivo){
    FILE *arquivo = fopen(nome_arquivo, "r+");
    ranking->nome_arquivo = NULL;

    //Arquivo existe ou deu erro ao abrir?
    if(arquivo == NULL){
        printf("Nao encontrado. %i\n",MAXIMO_INTERVALO_PADRAO);
        return -1;
    }
    char temp;

    //Arquivo vazio?
    if (fscanf(arquivo, "%c", &temp) == EOF){
        printf("Arquivo vazio.\n");
        return -1;
    }
    rewind(arquivo);
    //Guarda o nome do arquivo
    ranking->nome_arquivo = malloc(strlen(nome_arquivo));
    strcpy(ranking->nome_arquivo, nome_arquivo);
    limpar_ranking(ranking);
    while(absorver_palavra_arquivo(ranking,arquivo) == 1){};
    fclose(arquivo);
    scanf("%c",&temp);
    return 1;
}

void imprimir_ranking(Ranking *ranking, int intevalo_minimo, int intervalo_maximo){
    char palavra[TAMANHO_MAXIMO_PALAVRA_ARQUIVO + 1];
    int quantidade, i;
    for (i = 0; i<= ranking->mapa->total - 1; i++){
        le_termo(ranking->mapa,i,palavra,&quantidade);
        if (quantidade >= intevalo_minimo && quantidade <= intervalo_maximo)
            printf("%s - %i\n", palavra, quantidade);
    }
}

void obter_quantidade(Ranking *ranking, int *total_repetindo, int *total_diferente, int intevalo_minimo, int intervalo_maximo){
    int quantidade, i, _total_repetindo = 0, _total_diferente = 0;
    for (i = 0; i<= ranking->mapa->total - 1; i++){
        le_termo(ranking->mapa,i,NULL,&quantidade);
        if (quantidade >= intevalo_minimo && quantidade <= intervalo_maximo){
            _total_repetindo += quantidade;
            _total_diferente++;
        }
    }
    *total_repetindo = _total_repetindo;
    *total_diferente = _total_diferente;
}
