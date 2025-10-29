#include <stdio.h>
#include <stdlib.h>

#include "fila_lista.h"

/*criaFl(void):
*
*   Cria uma nova estrutura de fila;
*
*   f->l = criaL(): Quando a estrutura da fila e alocada,
*                   e necessario inicializar a lista que
*                   gerencia a fila;
*
*   Os dois if testam se as alocacoes deram certo;
*
*/
Fila_l* criaFl(void) {
    Fila_l* f = malloc(sizeof(Fila_l));
    if (f==NULL) return NULL;
    f->l = criaL();
    if (f->l==NULL) {
        free(f);
        return NULL;
    }
    return f;
}

/*enqueueFl(Fila_l* f, const int v):
*
*   Insere um elemento no fim da fila;
*
*   if (f==NULL){...}: Testa se a fila foi inicializada;
*
*   insereFL(f->l, v): Insere o valor no fim da fila, utilizando
*                      a funcao de inserir no fim da lista que foi
*                      usada para implementacao;
*
*/
void enqueueFl(Fila_l* f, const int v) {
    if (f==NULL) return;
    insereFL(f->l, v);
}

/*dequeueFl(Fila_l* f, int *flag):
*
*   Retira o elemento que ta no comeco da fila;
*
*   Retorna 0 e -1 na flag em caso de falha. Em caso
*   de sucesso, retorna o valor retirado e 0 na flag;
*
*   if (f==NULL || f->l->tam==0){...}: Testa se a fila foi inicializada
*                                      e tem elementos;
*
*   else{...}: Caso a lista tenha elementos, armazena o elemento retirado
*              na variavel r e atribui 0 na flag;
*
*/
int dequeueFl(Fila_l* f, int *flag) {
    int r = 0;
    if (f==NULL || f->l->tam==0) *flag = -1;
    else {
        r = f->l->head->info;
        rmPL(f->l, 0);
        *flag = 0;
    }
    return r;
}

/*taVaziaFl(Fila_l* f):
*
*   A funcao leva em consideracao que a fila
*   foi inicializada, caso contrario, pode
*   (provavelmente vai) dar crash no programa;
*
*   Determina se a fila ta vazia ou nao;
*
*   Retorna o valor da expressao f->l->tam==0:
*
*           0: caso a fila tenha elementos;
*
*           !0: Caso a fila esteja vazia;
*
*/
_Bool taVaziaFl(Fila_l* f) {
    return f->l->tam==0;
}

/*tamanhoFl(Fila_l* f):
*
*   A funcao leva em consideracao que a fila
*   foi inicializada, caso contrario, pode
*   (provavelmente vai) dar crash no programa;
*
*   Retorna o tamanho atual da fila;
*
*   if (f==NULL){...}: Caso a fila nao esteja inicializada, retorna 0;
*
*/
int tamanhoFl(Fila_l* f) {
    return f->l->tam;
}

/*killFl(Fila_l* f):
*
*   Elimina a fila;
*
*   if (f==NULL): Testa se a fila "existe";
*
*   killL(f->l): Elimina a lista que foi usada
*                pra implementar a fila;
*
*   free(f): Elimina a fila;
*
*/
void killFl(Fila_l* f) {
    if (f==NULL) return;
    killL(f->l);
    free(f);
}

