#include "labirinto.h"
#include "fila.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int main(void) {

    //Variaveis pra contagem de tempo
    double tempo_exec;
    clock_t inicio, fim;

    inicio = clock();

    srand(time(NULL));

    // Declaracao de variaveis;
    Labirinto *labirinto;
    Posicao *posicao;
    Percurso *percurso;
    Fila fila;
    int x, y;  //Coordenadas iniciais
    int lins, cols;
    char opcao;

    scanf("%d %d", &lins, &cols);
    labirinto = alocarLabirinto(lins, cols);   // Alocacao do labirinto
    getchar();
    scanf("%c", &opcao);
    getchar();

    switch (opcao)
    {   
        // Imprime o labirinto com os pontilhados;
        case 'r':
          leLabirinto(labirinto);
          primeiraPosicao(labirinto, &x, &y);
          posicao = designaPosicao(x, y);
          acharSaida(labirinto, posicao);
          percurso = alocarPercurso(labirinto, x, y);
          passosAteSaida(percurso);
          //int aux = contador(labirinto);
          //if(aux > 0){
            printf("\n");
            printLabirinto(labirinto, posicao);
          //}
        break;

        // Imprime as coordenadas ate o destinho;
        //case 'c':
          //leLabirinto(labirinto);
          //primeiraPosicao(labirinto, &x, &y);
          //posicao = designaPosicao(x, y);
          //acharSaida(labirinto, posicao);
          //percurso = alocarPercurso(labirinto, x, y);
          //passosAteSaida(percurso);
          //designaCoordenadas(labirinto, percurso, posicao);
          //printCoordenadas(percurso);
          
        //break;

        case 'f':
          leLabirinto(labirinto);
          acharSaida_f(labirinto, fila);
          int cont = contador_f(labirinto);
          if(cont > 0){
            printf("\n%d\n", cont);
            printLabirinto_f(labirinto);
          }
        break;
    }
  
  //Desaloca TADs
  desalocarLabirinto(&labirinto);
  //Percurso e Posicao sao usados apenas na opcao r
  if(opcao == 'r'){
    desalocarPercurso(&percurso);
    desalocarPosicao(&posicao);
  }

  //Imprime tempo 
  fim = clock();
  tempo_exec = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
  printf("\nTempo de execucao: %fs\n", tempo_exec);

  return 0;

}