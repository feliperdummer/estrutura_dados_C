#include "pilha_lista.h"
#include <stdio.h>
#include <stdlib.h>

/*criaPl(void):
*
*   Cria uma nova estrutura de pilha;
*
*   Os dois testes sao apenas pra comprovar que
*   a alocacao de memoria deu certo;
*
*/
Pilha_l* criaPl(void) {
    Pilha_l* n = (Pilha_l*)malloc(sizeof(Pilha_l));
    if (n==NULL) return NULL;
    n->l = criaL();
    if (n->l==NULL) {
        free(n);
        return NULL;
    }
    return n;
}

/*taVaziaPl(Pilha_l* p):
*
*   Retorna o valor logico da expressao p->l->tam==0;
*
*           0 para falso;
*           !=0 para verdadeiro;
*
*/
_Bool taVaziaPl(Pilha_l* p) {
    return p->l->tam==0;
}

/*tamanhoPl(Pilha_l* p):
*
*   Retorna o tamanho atual da pilha;
*
*   if (p==NULL){...}: Aqui ele testa pra caso seja passado
*                      o endereco de uma pilha nao alocada,
*                      ai pra nao dar erro no funcionamento
*                      do programa, ele retorna 0;
*
*/
int tamanhoPl(Pilha_l* p) {
    if (p==NULL) return 0;
    return p->l->tam;
}

/*pushPl(Pilha_l* p, const int v):
*
*   Empurra um elemento para o topo da pilha;
*
*   O topo da pilha vai ser o head da lista porque
*   isso faz com que a funcao pop() tenha complexidade
*   O(1). Caso o tail da lista fosse o topo da pilha, a funcao pop()
*   teria que caminhar por toda a lista ate chegar no ultimo elemento;
*
*   if (p==NULL){...}: Testa se a pilha foi inicializada;
*
*/
void pushPl(Pilha_l* p, const int v) {
    if (p==NULL) return;
    insereIL(p->l, v);
}

/*popPl(Pilha_l* p, int* v):
*
*   Remove o valor do topo da pilha e o remove;
*
*   Fica de responsabilidade do usuario em
*   passar uma pilha inicializada e que nao
*   seja vazia, caso contrario o programa
*   pode (provavelmente vai) quebrar;
*
*/
int popPl(Pilha_l* p) {
    int v = p->l->head->info;
    rmPL(p->l, 0);
    return v;
}

/*int peekPl(Pilha_l* p):
*
*   Remove o valor do topo da pilha;
*
*   Fica de responsabilidade do usuario em
*   passar uma pilha inicializada e que nao
*   seja vazia, caso contrario o programa
*   pode (provavelmente vai) quebrar;
*
*/
int peekPl(Pilha_l* p) {
    return p->l->head->info;
}

/*killPl(Pilha_l* p):
*
*   Elimina a pilha;
*
*   if (p==NULL){...}: Caso a pilha ja nao exista;
*
*   killL(p->l): Libera a lista primeiro;
*
*   free(p): Libera a pilha;
*
*/
void killPl(Pilha_l* p) {
    if (p==NULL)
        return;
    killL(p->l);
    free(p);
}



