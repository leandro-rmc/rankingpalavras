# Ranking de Palavras - Estrutura de Dados

## O que é?


Seu objetivo é buscar palavras dentro de um arquivo de texto e efetuar uma série de operações em memória. É um trabalho que foi passado para certas turmas de Estrutura de Dados e eu aproveitei para fazer e ganhar experiência. Foi dado um enunciado e uma série de assinaturas de funções que deveriam ser codificadas do zero, mas eu fui além do que foi pedido, além de mudar um pouco a arquitetura.

## Funcionamento

Você deve passar o caminho do arquivo de texto no momento da inicialização por argumento de linha de comando ou a qualquer momento através da interface do próprio programa. O arquivo de texto deve ter as palavras separadas por espaço ou quebra de linha. O programa "absorverá" essas palavras e as jogará na estrutura Mapa, onde ficarão até que o usuário decida atualizar ou absorver palavras de outro arquivo. Toda manipulação é feita em cima do conteúdo dessa estrutura; o arquivo é aberto uma única vez ou manualmente sempre que o usuário quiser. Um arquivo de texto chamado "bdteste.txt" contém palavras aleatórias para facilitar o uso inicial. OBS: Tenho plena ciência de que não é uma boa prática jogar o conteúdo inteiro de um arquivo para dentro da memória sem qualquer tipo de controle. Para o propósito deste programa, o ideal seria impor uma limitação ao tamanho do arquivo com as palavras. O programa não é muito recente e o estou utilizando para estudar e treinar outras coisas, como Docker e boas práticas.

## Docker

Para facilitar o uso (e para eu ganhar mais experiência com essa ferramenta), o programa pode ser utilizado pelo Docker em containers Linux. Será utilizado o GCC para efetuar a compilação.

Dentro do diretório do projeto, use o seguinte comando para montar a imagem:

```powershell
docker build . -t leandromusser/ranking_palavras
```


Caso não queira fazer o clone do projeto, pode-se baixar a imagem pelo  [Docker Hub](https://hub.docker.com/r/leandromusser/ranking_palavras). usando o seguinte comando:
```powershell
docker pull leandromusser/ranking_palavras:latest
```


Após um desses dois passos, use o seguinte comando para instanciar o container:
```powershell
docker run --name ranking_palavras -it --rm leandromusser/ranking_palavras
```


O diretório do programa é /RankingPalavras e o arquivo de texto deve ser enviado para lá. Para isso, eu utilizo o comando **docker cp**, que permite copiar arquivos da máquina hospedeira para dentro do container:
```powershell
docker cp teste.txt ranking_palavras:/RankingPalavras
```
Onde está **teste.txt**, substituir pelo caminho do seu arquivo de texto (nesse caso, ele está no diretório atual). O **ranking_palavras** é o nome do container, que eu defini no passo acima pelo parâmetro --name. O **/RankingPalavras** é o diretório do programa dentro do container.

## Interface
![Interface do programa criado](https://user-images.githubusercontent.com/36391793/82130501-4e289500-97a2-11ea-95f8-11d2b2cabd12.png)
