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
    for (i = 0; i <= TAMANHO_MAXIMO_PALAVRA_ARQUIVO - 2; i++){
        if (fscanf(arquivo,"%c",&palavraAtual[i]) == EOF){
            parar = 1;
            resultado = 0;
        }
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
    return resultado;
}
//Limpa o Ranking para ser usado novamente do zero (configurações permanecem)
void limpar_ranking(Ranking *ranking){
    ranking->nome_arquivo = NULL;
    if (ranking->status == ComArquivo)
        libera_mapa(ranking->mapa);
    ranking->mapa = malloc(sizeof(Mapa));
    inicia_mapa(ranking->mapa);
}
Ranking* obter_ranking(){
    Ranking *ranking = malloc(sizeof(Ranking));
    ranking->rankingConfig = NULL;
    ranking->mapa = NULL;
    ranking->nome_arquivo = NULL;

    ranking->status = SemArquivo;
    ranking->mapa = malloc(sizeof(Mapa));
    inicia_mapa(ranking->mapa);

    ranking->rankingConfig = malloc(sizeof(RankingConfig));
    ranking->rankingConfig->minimo_intervalo = MINIMO_INTERVALO_PADRAO;
    ranking->rankingConfig->maximo_intervalo = MAXIMO_INTERVALO_PADRAO;

    return ranking;
}
//Procura pelo arquivo com nome passado e obtém todas as palavras dele
int absorver_palavras_arquivo(Ranking *ranking, char *nome_arquivo){
    FILE *arquivo = fopen(nome_arquivo, "r+");
    if (ranking->status == ComArquivo)
        free(ranking->nome_arquivo);
    ranking->nome_arquivo = NULL;
    ranking->status = SemArquivo;

    //Arquivo existe ou deu erro ao abrir?
    if(arquivo == NULL)
        return -1;
    char temp;

    //Arquivo vazio?
    if (fscanf(arquivo, "%c", &temp) == EOF){
        return -1;
    }
    rewind(arquivo);

    //Guarda o nome do arquivo
    ranking->nome_arquivo = malloc(strlen(nome_arquivo));
    strcpy(ranking->nome_arquivo, nome_arquivo);
    limpar_ranking(ranking);
    while(absorver_palavra_arquivo(ranking,arquivo) == 1){};
    fclose(arquivo);
    ranking->status = ComArquivo;
    return 1;
}

ContainerPalavras* obter_palavras_filtradas(Ranking *ranking, int intevalo_minimo, int intervalo_maximo){
    char palavraAtual[TAMANHO_MAXIMO_PALAVRA_ARQUIVO + 1];
    ContainerPalavras *container_palavras = malloc(sizeof(ContainerPalavras));
    SubContainerPalavra *sub_container_palavra;
    container_palavras->total_repetindo = 0;
    container_palavras->total_diferente = 0;
    container_palavras->listaSubContainerPalavra = malloc(tamanho_mapa(ranking->mapa) * sizeof(SubContainerPalavra*));
    int quantidade, i;
    for (i = 0; i<= ranking->mapa->total - 1; i++){
        le_termo(ranking->mapa,i,palavraAtual,&quantidade);
        if (quantidade >= intevalo_minimo && quantidade <= intervalo_maximo){
            sub_container_palavra = malloc(sizeof(SubContainerPalavra));
            sub_container_palavra->quantidade = quantidade;
            sub_container_palavra->palavra = malloc(TAMANHO_MAXIMO_PALAVRA_ARQUIVO + 1);
            strcpy(sub_container_palavra->palavra, palavraAtual);
            container_palavras->listaSubContainerPalavra[container_palavras->total_diferente] = sub_container_palavra;
            container_palavras->total_diferente++;
            container_palavras->total_repetindo += quantidade;
        }
    }
    return container_palavras;
}
