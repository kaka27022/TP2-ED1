#include "labirinto.h"

#include <stdio.h>
#include <stdlib.h>

// ================================================================================= -[INIT]- ==============================================================================================

Posicao primeiraPosicao(Labirinto *labirinto) {
    Posicao firstpos;
    for (int i = 0; i < labirinto->lins; i++) {
        for(int j = 0; j < labirinto->cols; j++) {
            if (labirinto->lab[i][j] == 'M') {
                firstpos.x = i;
                firstpos.y = j;
            }
        }
    }

    return firstpos;
}

void leLabirinto(Labirinto *labirinto) {

  for (int i = 0; i < labirinto->lins; i++) {
    for (int j = 0; j < labirinto->cols; j++) {
      scanf("%c", &labirinto->lab[i][j]);
    }
    // Getchar para ler os espacos no labirinto 
    getchar();
  }
}

Labirinto *alocarLab(int lins, int cols) {
    Labirinto *labirinto = malloc(sizeof(Labirinto));
    labirinto->lins = lins; labirinto->cols = cols;
    labirinto->lab = malloc(lins * sizeof(char*));
    for (int i = 0; i < lins; i++) 
        labirinto->lab[i] = malloc(cols * sizeof(char)); 
    
    return labirinto;
}

// ================================================================================ [ OPERAÇÕES: PILHA ] ===================================================================================
//                                                                                                                                                                    BUSCA EM PROFUNDIDADE 

int caminhoValido(Labirinto *labirinto, int lins, int cols) {
    return (labirinto->lab[lins][cols] == ' ');
}

int acharSaidaPilha(Pilha *pilha, Labirinto *labirinto) {
    int flag = 0;
    Posicao pos = primeiraPosicao(labirinto);
    int visitado[labirinto->lins][labirinto->cols];
    
    pilhaPush(pilha, pos);

    // marcando tudo como nao visitado
    for (int i = 0; i < labirinto->lins; i++)
        for (int j = 0; j < labirinto->cols; j++)
            visitado[i][j] = 0;

    while(!pilhaEhVazia) {
        int backt = 0;
        pos = pilha->topo->item;
        visitado[pos.x][pos.y] = 1;

        // [WIN CONDITION]
        if(pos.x == labirinto->lins - 1 && pos.y == labirinto->cols) {
            vitoria(labirinto);
            return 1;
        }
        
        // [DIREITA]
        if (!visitado[pos.x][pos.y + 1] && caminhoValido(labirinto, pos.x, pos.y + 1)) {
            pos.y++; backt++;
            pilhaPush(pilha, pos);
        }
        // [BAIXO]
        if (!visitado[pos.x + 1][pos.y] && caminhoValido(labirinto, pos.x + 1, pos.y)) {
            pos.x++; backt++;
            pilhaPush(pilha, pos);
        }
        // [ESQUERDA]
        if (!visitado[pos.x][pos.y - 1] && caminhoValido(labirinto, pos.x, pos.y - 1)) {
            pos.y--; backt++;
            pilhaPush(pilha, pos);
        }
        // [CIMA]
        if (!visitado[pos.x - 1][pos.y] && caminhoValido(labirinto, pos.x - 1, pos.y)) {
            pos.x--; backt++;
            pilhaPush(pilha, pos);
        }

        if (backt == 0)
            pilhaPop(pilha);

    }
    
    derrota(labirinto);
    printf("\nEPIC FAIL!!\n\n");
    return 0;
}

void iniciaPilha(Pilha *pilha) {
    pilha->cabeca = NULL;
    pilha->topo = NULL;
    pilha->tamanho = 0;
}

int pilhaEhVazia(Pilha *pilha) {
    return (pilha->tamanho == 0);
}

// [ADICIONA UM ELEMENTO AO TOPO] -- NOTA: "topo" não faz parte da lista, é como um clone;
void pilhaPush(Pilha *pilha, Posicao pos) {
    Celula *new = malloc(sizeof(Celula));
    if (new == NULL)
        printf("\nmemória insuficiente!!\n");

    new->item = pos;
    new->prox = NULL;
    pilha->tamanho++;
    if (pilha->cabeca == NULL) {
        pilha->topo = new;
        pilha->cabeca = new;
    } else {
        pilha->topo->prox = new;
        pilha->topo = new;
    }
}

// [RETIRA O ELEMENTO DO TOPO]
int pilhaPop(Pilha *pilha) {
    if (pilhaEhVazia(pilha))
        return 0;
    Celula *aux = pilha->cabeca;
    while (aux->prox->prox != NULL) // para qdo estver uma posição anterior ao topo
        aux = aux->prox;
    // libero o topo e o atualizo
    pilha->tamanho--;
    free(pilha->topo);
    pilha->topo = aux;
    aux->prox = NULL;

    return 1;
}

int contapassos(Labirinto *labirinto) {
    int cont = 0;
    for (int i = 0; i < labirinto->lins; i++)
        for (int j = 0; j < labirinto->cols; j++)
            if(labirinto->lab[i][j] == '1')
                cont++;

    return cont;
}

void printLab(Labirinto *labirinto) {
    for (int i = 0; i < labirinto->lins; i++) {
        for (int j = 0; j < labirinto->cols; j++) {
            printf("%c", labirinto->lab[i][j]);
        }
        printf("\n");
    }
}

void vitoria(Labirinto *labirinto) {
    printf("\nnúmero de passos: %d\n", contapassos(labirinto));
    printf("\nCaminho de Saída:\n");
    printLab(labirinto);
}

void derrota(Labirinto *labirinto) {
    printf("\nnúmero de passos: %d\n", contapassos(labirinto));
    printLab(labirinto);
    printf("\nEPIC FAIL!");
}

// =======================================================================
// [DESALOCAÇÃO DE MEMÓRIA] ==============================================
// =======================================================================

void desalocarPilha(Pilha *pilha) {
    Celula *aux = pilha->cabeca;
    while(aux != NULL) {
        free(aux);
        aux = aux->prox;
    }

    free(pilha);
}

void desalocarLabirinto(Labirinto **labirinto) {
    for(int i = 0; i < (*labirinto)->lins; i++)
        free((*labirinto)->lab[i]);

    free((*labirinto)->lab);
    free(*labirinto);
}
