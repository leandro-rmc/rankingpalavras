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

#endif // CONTAINERPALAVRAS_H_INCLUDED
