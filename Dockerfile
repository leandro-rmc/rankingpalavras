FROM gcc:latest as base
WORKDIR /app

COPY src .
RUN mkdir /app/build && gcc *.c Implementacoes/*.c Interfaces/*.h -o /app/build/ranking-palavras

FROM ubuntu:latest
WORKDIR /app
COPY --from=base /app/bdteste.txt /app/build .

ENTRYPOINT ["/app/ranking-palavras"]