#ifndef FILA_H
#define FILA_H

#include <stdbool.h>

typedef struct labirinto Labirinto;

typedef struct{
    int x;
    int y;
} Coordenadas;

typedef struct celula{
    Coordenadas coordenada;
    struct celula *prox;
} Celula;

typedef struct {
    Celula *inicio;
    Celula *fim;
    int tamanho;
} Fila;

bool acharSaida_f(Labirinto* , Fila);
void printLabirinto_f(Labirinto*);

#endif //FILA_H