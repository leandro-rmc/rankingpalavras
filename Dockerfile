FROM gcc:latest as base
<<<<<<< HEAD
WORKDIR /RankingPalavras

COPY src .
RUN mkdir /RankingPalavras/build && gcc *.c Implementacoes/*.c Interfaces/*.h -o /RankingPalavras/build/app

FROM ubuntu:latest
WORKDIR /RankingPalavras
COPY --from=base /RankingPalavras/bdteste.txt /RankingPalavras/build .

ENTRYPOINT ["/RankingPalavras/app"]
=======
WORKDIR /app

COPY src .
RUN mkdir /app/build && gcc *.c Implementacoes/*.c Interfaces/*.h -o /app/build/ranking-palavras

FROM ubuntu:latest
WORKDIR /app
COPY --from=base /app/bdteste.txt /app/build .

ENTRYPOINT ["/app/ranking-palavras"]
>>>>>>> bc2f409b85428f4c1f62d1a23a51d18404cbcd82
