#include <stdlib.h>
#include "ContainerPalavras.h"

void liberar_conteudo_sub_container_palavra(SubContainerPalavra *sub_container_palavra){
    free(sub_container_palavra->palavra);
}
void liberar_conteudo_container_palavras(ContainerPalavras *container_palavras){
    int i;
    for (i = 0; i <= container_palavras->total_diferente; i++){
        liberar_conteudo_sub_container_palavra(container_palavras->listaSubContainerPalavra[0]);
    }
}
