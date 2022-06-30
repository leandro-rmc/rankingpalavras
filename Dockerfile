FROM gcc:latest as base
WORKDIR /RankingPalavras

COPY src .
RUN mkdir /RankingPalavras/build && gcc *.c Implementacoes/*.c Interfaces/*.h -o /RankingPalavras/build/app

FROM ubuntu:latest
WORKDIR /RankingPalavras
COPY --from=base /RankingPalavras/bdteste.txt /RankingPalavras/build .

ENTRYPOINT ["/RankingPalavras/app"]