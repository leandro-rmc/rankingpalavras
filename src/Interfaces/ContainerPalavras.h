#ifndef CONTAINERPALAVRAS_H_INCLUDED
#define CONTAINERPALAVRAS_H_INCLUDED

typedef struct SubContainerPalavra{
    int quantidade;
    char *palavra;
} SubContainerPalavra;

typedef struct ContainerPalavras{
    int total_repetindo;
    int total_diferente;
    SubContainerPalavra **listaSubContainerPalavra;
} ContainerPalavras;

void liberar_conteudo_sub_container_palavra(SubContainerPalavra *sub_container_palavra);
void liberar_conteudo_container_palavras(ContainerPalavras *container_palavras);

#endif // CONTAINERPALAVRAS_H_INCLUDED
