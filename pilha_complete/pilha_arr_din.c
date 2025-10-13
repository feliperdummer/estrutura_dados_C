#include "pilha_arr_din.h"
#include <stdio.h>
#include <stdlib.h>

/*cria():
*
*   Pilha* n = (Pilha*)malloc(sizeof(Pilha)): Declara um ponteiro para o tipo Pilha e o
*              inicializa com uma estrutura do tipo pilha dinamicamente alocada;
*
*   n->top = -1: Atribui o valor -1 a variavel top da estrutura criada, indicando que
*                a pilha ta inicialmente vazia;
*
*   n->p = (int*)malloc(10 * sizeof(int)): inicializa o ponteiro da estrutura com um vetor
*          de 10 posicoes iniciais dinamicamente alocado;
*
*   return n: retorna o endereço de memoria da estrutura Pilha criada;
*/
Pilha* cria(void) {
    Pilha* n = (Pilha*)malloc(sizeof(Pilha));
    n->pa = (int*)malloc(10*sizeof(int));
    if (n->pa==NULL) {
        printf("erro: falha na alocacao de memoria\n");
        return NULL;
    }
    n->top = -1;
    n->tam = 10;
    return n;
}

/*taVazia(Pilha* p):
*
*   return p->top==-1: retorna o valor logico da expressao:
*
*          0, quando a expressao e falsa;
*          !=0, quando a expressao e verdadeira;
*/
_Bool taVazia(Pilha* p) {
    return p->top==-1;
}

/*taCheia(Pilha* p):
*
*   return p->top==p->tam-1: retorna o valor logico da expressao:
*
*           0, quando a espressao e falsa;
*           !=0, quando a expressao e verdadeira;
*
*/
_Bool taCheia(Pilha* p) {
    return tamanho(p,'f')==tamanho(p,'t');
}

/*tamanho(Pilha* p):
*
*   Aceita duas flags como parametro:
*
*           f -> caso o desejo seja saber a quantidade de elementos da pilha ja preenchidos;
*           t -> caso o desejo seja saber o tamanho total da pilha;
*
*/
int tamanho(Pilha* p, const int opc) {
    switch(opc) {
        case 't':
            return p->tam;
        case 'f':
            return p->top + 1;
        default:
            printf("erro: flag invalida (t -> total | f -> preenchido)\n");
            return -1;
    }
}

/*push(Pilha* p, const int v):
*
*   if (taCheia(p)){...}: Testa caso a pilha tenha alcancado seu limite, caso sim,
*                         realoca mais 10 blocos de memoria;
*
*   p->pa[++p->top] = v: Incrementa a variavel t->top e atribui o valor ao elemento do topo;
*/
void push(Pilha* p, const int v) {
    if (p==NULL) {
        printf("erro: lista nao inicializada: funcao cria()\n");
        return;
    }
    if (taCheia(p)) {
        p->pa = (int*)realloc(p->pa, 10*sizeof(int));
        if (p->pa==NULL) {
            printf("erro: falha na realocacao de memoria\n");
            return;
        }
        p->tam += 10;
    }
    p->pa[++p->top] = v;
}

/*pop(Pilha* p):
*
*   if (p==NULL), if(taVazia(p)): Testa se a pilha nao foi inicializada ou ta vazia;
*
*   return p->pa[p->top--]: retorna o elemento que ta no topo da pilha,
*                           logo após decrementa a variavel p->top;
*
*/
int pop(Pilha* p) {
    if (p==NULL) {
        printf("erro: lista nao inicializada: funcao cria()\n");
        return -1;
    }
    if (taVazia(p)) {
        printf("erro: lista vazia\n");
        return -1;
    }
    return p->pa[p->top--];
}

/*peek(Pilha* p):

    if (p==NULL), if(taVazia(p)): Testa se a pilha nao foi inicializada ou ta vazia;

    return p->pa[p->top]: retorna o elemento do topo da pilha;
*/
int peek(Pilha* p) {
    if (p==NULL) {
        printf("erro: lista nao inicializada: funcao cria()\n");
        return -1;
    }
    if (taVazia(p)) {
        printf("erro: lista vazia\n");
        return -1;
    }
    return p->pa[p->top];
}

/*sKill(Pilha* p):

    free(p->pa): libera o vetor alocado dianamicamente quando a pilha foi criada;

    free(p): libera a pilha da memoria;

*/
void sKill(Pilha* p) {
    free(p->pa);
    free(p);
}

