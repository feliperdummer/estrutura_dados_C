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
*   n->p = malloc(1 * sizeof(int)): inicializa o ponteiro da estrutura com um vetor
*          de 1 posicao inicial dinamicamente alocado;
*
*   return n: retorna o endereço de memoria da estrutura Pilha criada;
*/
Pilha* cria(void) {
    Pilha* n = (Pilha*)malloc(sizeof(Pilha));
    n->pa = malloc(1 * sizeof(int));
    if (n->pa==NULL) {
        printf("erro: falha na alocacao de memoria\n");
        return NULL;
    }
    n->top = -1;
    n->tam = 1;
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
*   if (taCheia(p)) {...}: Aqui testa se o vetor da pilha chegou no limite, caso sim,
*                          ele sempre vai dobrar o tamanho de elementos do atual, entao
*                          caso a quant atual seja 1, vai realocar pra 2, e assim por diante.
*                          Depois disso, na linha p->tam = (tamanho(p, 't')*2), ele
*                          atualiza o tamanho do vetor com o novo valor.
*
*   p->pa[++p->top] = v: Incrementa a variavel t->top e atribui o valor ao elemento do topo;
*/
void push(Pilha* p, const int v) {
    if (p==NULL) {
        printf("erro: lista nao inicializada: funcao cria()\n");
        return;
    }
    if (taCheia(p)) {
        p->pa = realloc(p->pa, (tamanho(p, 't')*2)*sizeof(int));
        if (p->pa==NULL) {
            printf("erro: falha na realocacao de memoria\n");
            return;
        }
        p->tam = (tamanho(p, 't')*2);
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

