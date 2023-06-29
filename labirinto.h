#ifndef LABIRINTO_H
#define LABIRINTO_H

typedef struct labirinto Labirinto;
typedef struct posicao Posicao;
typedef struct percurso Percurso;

//Funcoes para alocar as TADS
Labirinto* alocarLabirinto(int, int);
Posicao* designaPosicao(int, int);      
Percurso* alocarPercurso(Labirinto*, int, int); 

//Funcao que le o labirinto digitado   
void leLabirinto(Labirinto*);

//Funcoes para resolucao do labirinto
void primeiraPosicao(Labirinto*, int*, int*); 
int acharSaida(Labirinto*, Posicao*);   
void passosAteSaida(Percurso*);       
void designaCoordenadas(Labirinto*, Percurso*, Posicao*);  
int contador(Labirinto*);

//Funcoes para printar resultados
void printCoordenadas(Percurso*);  
void printLabirinto(Labirinto*, Posicao*);     

//Funcoes para desalocar as TADs
void desalocarLabirinto(Labirinto**);    
void desalocarPosicao(Posicao**);        
void desalocarPercurso(Percurso**);      


#endif // LABIRINTO_H