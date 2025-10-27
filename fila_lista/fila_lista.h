#ifndef FILA_LISTA_H
#define FILA_LISTA_H

#include "lista_encad.h"


/*struct pilha_l:
*
*   Definicao da struct para a filha;
*
*   o _l no nome significa que a fila vai usar lista na sua implementacao;
*
*   Lista_e* l: Ponteiro pra lista que vai ser usada na implementacao da fila;
*
*/
struct fila_l { Lista_e* l; };
typedef struct fila_l Fila_l;

Fila_l* criaFl(void);
void enqueueFl(Fila_l*, const int);
int dequeueFl(Fila_l*, int*);
_Bool taVaziaFl(Fila_l*);
int tamanhoFl(Fila_l*);
void killFl(Fila_l*);

#endif // FILA_LISTA_H
