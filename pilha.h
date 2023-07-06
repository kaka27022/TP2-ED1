#ifndef LABIRINTO_H
#define LABIRINTO_H

typedef struct pilha Pilha;
typedef struct posicao Posicao;
typedef struct labirinto Labirinto;

struct labirinto {
    int lins;
    int cols;
    char **lab;
    int **visitado;
};

struct posicao {  
    int x;
    int y;
};

typedef struct celula {
    Posicao item;
    struct celula *prox;
} Celula;

struct pilha {
    int tamanho;
    Celula *topo;
    Celula *cabeca;
};




// [ALOCAÇÃO x INICIALIZAÇÃO]
int pilhaEhVazia(Pilha*);
void iniciaPilha(Pilha*);
Labirinto *alocarLab(int, int);
Posicao primeiraPosicao(Labirinto*);


// [OPERAÇÕES DO LABIRINTO]
void vitoria(Labirinto *);
void derrota(Labirinto *);
void printLab(Labirinto *);
void leLabirinto(Labirinto *);


// [OPERAÇÕES DA PILHA]
Posicao pilhaPop(Pilha*);
int contapassos(Labirinto*);
int acharSaidaPilha(Labirinto*);
void pilhaPush(Pilha*, Posicao);

// [OPERAÇÕES DA FILA]

// [DESALOCAÇÃO x FIM]
void desalocarPilha(Pilha*);
void desalocaVisitado(Labirinto*);
void desalocarLabirinto(Labirinto**);            

#endif // LABIRINTO_H