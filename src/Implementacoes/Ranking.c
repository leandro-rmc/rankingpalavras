#include <stdlib.h>
#include <string.h>
#include "../Interfaces/Ranking.h"
#include "../Interfaces/Mapa.h"

//Move o ponteiro interno para o próximo espaço ou quebra de linha
static void movPtrProxSeparador(Ranking *ranking, FILE *arquivo){
    char temp;
    while (fscanf(arquivo,"%c",&temp) != EOF){
        if (temp == ' ' || temp == '\n')
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
        if (palavraAtual[i] == ' ' || palavraAtual[i] == '\n')
            parar = 1;
        if (parar == 1){
            palavraAtual[i] = '\0';
            break;
        }
        //Se a variável de iteração tiver chegado ao seu fim, mas a palavra a ser lida do vocabulário...
        //... não, o ponteiro interno do arquivo precisa ser movido para a próxima palavra.
        if (i == TAMANHO_MAXIMO_PALAVRA_ARQUIVO - 2 && palavraAtual[i] != '\0'){
            movPtrProxSeparador(ranking, arquivo);
        }
    }
    palavraAtual[i + 1] = '\0';
    //Adaptação do algorítmo para evitar a entrada de palavras nulas
    if (palavraAtual[0] == '\0')
        free(palavraAtual);
    else{
        palavraAtual = realloc(palavraAtual, strlen(palavraAtual) + 1);
        insere_termo(ranking->mapa,palavraAtual);
    }
    return resultado;
}
int obter_status_ranking(Ranking *ranking){
    return ranking->status;
};
int obter_minimo_caracteres_ranking(Ranking *ranking){
    return ranking->minimo_caracteres;
}
int definir_limites_caractere_ranking(Ranking *ranking, int minimo_caracteres){
    if (minimo_caracteres > 0){
        ranking->minimo_caracteres = minimo_caracteres;
        return 1;
    }
    else
        return -1;
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
    ranking->mapa = NULL;
    ranking->nome_arquivo = NULL;

    ranking->minimo_caracteres = MINIMO_CARACTERES_PADRAO;
    ranking->status = SemArquivo;
    ranking->mapa = malloc(sizeof(Mapa));
    inicia_mapa(ranking->mapa);

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

//Responsável por buscar uma única palavra e jogá-la em uma estrutura
SubContainerPalavra* buscar_palavra_filtrada(Ranking *ranking, int intevalo_minimo, int intervalo_maximo, char *palavra){
    char palavraAtual[TAMANHO_MAXIMO_PALAVRA_ARQUIVO + 1];
    SubContainerPalavra *sub_container_palavra = malloc(sizeof(SubContainerPalavra));
    int quantidade, id_termo;
    id_termo = encontra_termo(ranking->mapa, palavra);
    if (id_termo == -1)
        sub_container_palavra->quantidade = 0;
    else{
        le_termo(ranking->mapa, id_termo, palavraAtual, &quantidade);
        sub_container_palavra->quantidade = quantidade;
        sub_container_palavra->palavra = malloc(strlen(palavraAtual) + 1);
        strcpy(sub_container_palavra->palavra, palavraAtual);
    }
    return sub_container_palavra;
}

//Responsável por percorrer o mapa e jogar as palavras dentro de uma estrutura
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
        if ((quantidade >= intevalo_minimo && quantidade <= intervalo_maximo) && strlen(palavraAtual) >= obter_minimo_caracteres_ranking(ranking)){
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
