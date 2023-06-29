#include "fila.h"
#include "labirinto.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*TAD que armazena o labirinto e suas caracteristicas*/
struct labirinto{

  char **lab;
  int lins;
  int cols;
};

bool coordenadaEhValida(int row, int col, int lins, int cols){
    return (row >= 0 && row < lins && col >= 0 && col < cols);
}

// Verifica se uma coordenada representa a saida do labirinto
bool ehSaida(int row, int col, int lins, int cols) {
    return (row == 0 || row == lins - 1 || col == 0 || col == cols - 1);
}

bool caminhoVazio(char** lab, int row, int col){
    return (lab[row][col] == ' ');
}

// Inicializa a fila vazia (Padrao)
void inicializaFila(Fila* fila){
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
}

// Verifica se a fila esta vazia atravez do seu tamanho
bool filaVazia(Fila* fila){
    return (fila->tamanho == 0);
}

// Insere um elemento na fila
void inserirFila(Fila* fila, Coordenadas coordenada){
    Celula* novaCelula = (Celula*)malloc(sizeof(Celula));
    novaCelula->coordenada = coordenada;
    novaCelula->prox = NULL;

    if(fila->inicio == NULL) {
        fila->inicio = novaCelula;
        fila->fim = novaCelula;
    } else {
        fila->fim->prox = novaCelula;
        fila->fim = novaCelula;
    }

    fila->tamanho++;
}

// Remove um elemento da fila
Coordenadas removerFila(Fila* fila) {
    if(filaVazia(fila)) {
        Coordenadas coordenadaVazia = {-1, -1};
        return coordenadaVazia;
    }

    Celula* celulaRemovida = fila->inicio;
    Coordenadas coordenadaRemovida = celulaRemovida->coordenada;

    fila->inicio = fila->inicio->prox;
    free(celulaRemovida);
    fila->tamanho--;

    return coordenadaRemovida;
}

// Marca caminho percorrido no labirinto com pontilhado
void marcarCaminho(Labirinto* labirinto, Coordenadas* caminho, int tamanhoCaminho){

    char** lab = labirinto->lab;

    for(int i = 0; i < tamanhoCaminho; i++){
        int row = caminho[i].x;
        int col = caminho[i].y;
        lab[row][col] = 'o';
    }
}

// Executa a busca em largura para encontrar a saida do labirinto
bool acharSaida_f(Labirinto* labirinto, Fila fila) {
    char** lab = labirinto->lab;
    int lins = labirinto->lins;
    int cols = labirinto->cols;

    bool visitado[lins][cols];
    for(int i = 0; i < lins; i++){
        for(int j = 0;j < cols; j++){
            visitado[i][j] = false;
        }
    }

    inicializaFila(&fila);

    // Encontrar posicao inicial 'M' no labirinto
    Coordenadas start;
    start.x = -1;
    start.y = -1;

    for(int i = 0; i < lins; i++){
        for(int j = 0; j < cols; j++){
            if(lab[i][j] == 'M'){
                start.x = i;
                start.y = j;
                break;
            }
        }
    }

    inserirFila(&fila, start);
    visitado[start.x][start.y] = true;

    Coordenadas caminho[lins * cols];
    int tamanhoCaminho = 0;

    while (!filaVazia(&fila)){
        Coordenadas atual = removerFila(&fila);
        int row = atual.x;
        int col = atual.y;

        if(ehSaida(row, col, lins, cols)){
            marcarCaminho(labirinto, caminho, tamanhoCaminho);
            return true;
        }

        Coordenadas vizinhos[4] = {
            {row, col + 1},   // Direita
            {row - 1, col},   // Cima
            {row, col - 1},   // Esquerda
            {row + 1, col}    // Baixo
          
        };

        for(int i = 0; i < 4; i++){
            int novaLinha = vizinhos[i].x;
            int novaColuna = vizinhos[i].y;

            if(coordenadaEhValida(novaLinha, novaColuna, lins, cols) && !visitado[novaLinha][novaColuna] && caminhoVazio(lab, novaLinha, novaColuna)){
                visitado[novaLinha][novaColuna] = true;
                Coordenadas novaCoordenada = {novaLinha, novaColuna};
                inserirFila(&fila, novaCoordenada);
                caminho[tamanhoCaminho++] = novaCoordenada;
            }
        }
    }

    printf("EPIC FAIL!!\n");
    return false;

}

// Funcao que imprime pontilhados ate o final do lab;
void printLabirinto_f(Labirinto *labirinto) {
  for (int i = 0; i < labirinto->lins; i++) {
    for (int j = 0; j < labirinto->cols; j++) {
      printf("%c", labirinto->lab[i][j]);
    }
    printf("\n");
  }
}


