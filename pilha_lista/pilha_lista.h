#ifndef PILHA_LISTA_H
#define PILHA_LISTA_H

#include "lista_encad.h"

/*struct pilha_l:

    Definicao da struct para a pilha;

    o _l no nome significa que a pilha vai usar lista na sua implementacao;

    Lista_e* l: Estrutura da lista que vai ser usada na pilha;

*/
struct pilha_l { Lista_e* l; };
typedef struct pilha_l Pilha_l;

Pilha_l* criaPl(void);
_Bool taVaziaPl(Pilha_l*);
int tamanhoPl(Pilha_l*);
void pushPl(Pilha_l*, const int);
int popPl(Pilha_l*);
int peekPl(Pilha_l*);
void killPl(Pilha_l*);

#endif // PILHA_LISTA_H
