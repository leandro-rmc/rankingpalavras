#include <stdlib.h>
#include <string.h>
#include "Ranking.h"
#include "Mapa.h"

//Move o ponteiro interno do arquivo para o início da próxima palavra
static void movPtrProxPalavraVocabulario(Ranking *ranking, FILE *arquivo){
    char temp;
    while (fscanf(arquivo,"%c",&temp) != EOF){
        if (temp == ranking->rankingConfig->separador_palavras)
            break;
    }
}
//Absorve 1 palavra do arquivo
static int absorver_palavra_arquivo(Ranking *ranking, FILE *arquivo){
    int parar = 0, i, resultado = 1;
    char *palavraAtual = malloc(sizeof(char) * ranking->rankingConfig->maximo_caracteres + 1);
    //printf("Teste");
    for (i = 0; i <= ranking->rankingConfig->maximo_caracteres - 2; i++){
        if (fscanf(arquivo,"%c",&palavraAtual[i]) == EOF){
            parar = 1;
            resultado = 0;
        }
        //printf("0");
        if (palavraAtual[i] == ranking->rankingConfig->separador_palavras)
            parar = 1;
        if (parar == 1){
            palavraAtual[i] = '\0';
            break;
        }
        //Se a variável de iteração tiver chegado ao seu fim, mas a palavra a ser lida do vocabulário...
        //... não, o ponteiro interno do arquivo precisa ser movido para a próxima palavra.
        if (i == ranking->rankingConfig->maximo_caracteres - 2 && palavraAtual[i] != '\0'){
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
    ranking->rankingConfig->separador_palavras = '\n';
    ranking->rankingConfig->minimo_caracteres = 1;
    ranking->rankingConfig->maximo_caracteres = 50;
}
//Procura pelo arquivo com nome passado e obtém todas as palavras dele
int absorver_palavras_arquivo(Ranking *ranking, char *nome_arquivo){
    FILE *arquivo = fopen(nome_arquivo, "r+");
    ranking->nome_arquivo = NULL;

    //Arquivo existe ou deu erro ao abrir?
    if(arquivo == NULL){
        printf("Nao encontrado.\n");
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
