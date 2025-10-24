#include <stdio.h>
#include <stdlib.h>

#include "lista_dup_encad.h"

/*criaLD(void):

    Retorna uma nova estrutura de lista duplamente encadeada;

    Lista_d* n =...: Cria um potenteiro para struct gerenciadora
                     e aloca uma struct gerenciadora;

    n->tam = 0: Inicializa o tamanho da struct em 0;

    n->head=NULL, n->tail=NULL: Inicializa os ponteiros head
                                e tail em NULL:

*/
Lista_d* criaLD(void) {
    Lista_d* n = (Lista_d*)malloc(sizeof(Lista_d));

    n->tam = 0;
    n->head = NULL;
    n->tail = NULL;
    return n;
}

/*insereILD(Lista_d* l, const int v):
*
*   Insere um no no inicio da lista;
*
*   if (n==NULL || l==NULL){...}: Testa se a alocacao deu certo e se a lista passada foi inicializada;
*
*   n->info = v, n->prox = l->head, n->ant = NULL: Inicializa o novo nó. n->prox sempre vai
*                                                  apontar para o antigo l->head, independente
*                                                  da lista estar vazia ou não, e n->ant sempre
*                                                  vai ser NULL, por ser o primeiro no da lista;
*
*   if (l->tam==0) l->tail = n: Aqui testa se a lista ta vazia, porque se for o caso, o novo no
*                               vai ser o l->tail tambem;
*
*                               else l->head->ant = n: Aqui só roda se a lista nao estiver vazia.
*                                                      Faz com que o novo no seja apontado pelo
*                                                      ponteiro ant do antigo head da lista;
*
*   l->head = n: Transforma n no novo head da lista;
*
*   l->tam++: incrementa o tamanho da lista;
*
*/
void insereILD(Lista_d* l, const int v) {
    Node_d* n = (Node_d*)malloc(sizeof(Node_d));

    if (n==NULL || l==NULL) return;
    n->info = v;
    n->prox = l->head;
    n->ant = NULL;
    if (l->tam==0) l->tail = n;
    else l->head->ant = n;
    l->head = n;
    l->tam++;
}

/*insereFLD(Lista_d* l, const int v):
*
*   Insere um no no fim da lista;
*
*   if (n==NULL || l==NULL){...}: Testa se a alocacao deu certo e se a lista passada foi inicializada;
*
*   n->info = v, n->prox = NULL, n->ant = l->tail: Inicializa o novo no. n->prox
*                                                  sempre vai ser NULL porque o
*                                                  novo no se torna o tail da lista.
*                                                  n->ant aponta para o antigo tail,
*                                                  mesmo se a lista estiver vazia;
*
*   if (l->tam==0) l->head = n: Aqui testa se a lista ta vazia, porque se for o caso,
*                               o novo no vai ser l->head tambem;
*
*                               else l->tail->prox = n: Aqui so roda se a lista nao
*                                                       estiver vazia. Faz com que o
*                                                       novo no seja apontado pelo prox
*                                                       do antigo tail da lista;
*
*   l->tail = n: Transforma n no novo tail da lista;
*
*   l->tam++: Incrementa o tamanho da lista;
*
*/
void insereFLD(Lista_d* l, const int v) {
    Node_d* n = (Node_d*)malloc(sizeof(Node_d));

    if (n==NULL || l==NULL) return;
    n->info = v;
    n->prox = NULL;
    n->ant = l->tail;
    if (l->tam==0) l->head = n;
    else l->tail->prox = n;
    l->tail = n;
    l->tam++;
}

/*insereOLD(Lista_d* l, const int v):
*
*   Insere um novo no de forma ordenada;
*
*   Ja espera que a lista passada esteja ordenada;
*
*   if (n==NULL || l==NULL){...}: Testa se a alocacao deu certo e se a lista passada foi inicializada;
*
*   n->info = v, n->prox = NULL, n->ant = NULL: Inicializa o novo no;
*
*   if (l->tam==0){...}: Testa se a lista ta vazia, se sim, o novo no vira head e tail;
*
*   else if (v >= l->tail->info) {...}: Testa se o novo no e maior ou igual ao tail, caso sim,
*                                       ele se torna o novo tail. Essa operacao ta fora do loop
*                                       porque ele se torna O(1) em questao de tempo caso a insercao
*                                       for feita na ultima posicao, nao sendo necessario percorrer
*                                       o a lista toda pra chegar la;
*
*   else{...}: Aqui e pra caso a insercao for feita na primeira posicao ou no meio da lista. "Ah mas
*              por que nao tem um teste pra insercao na primeira posicao igual foi feito com o tail ?"
*              Porque a insercao na primeira posicao e uma operacao O(1) independente de ser feita dentro
*              ou fora do loop.
*
*              while (prim!=NULL && v >= prim->info){...}: Caminha pela lista ate que o novo no seja menor que
*                                                          prim. O teste de (prim!=NULL) é mais uma programacao
*                                                          defensiva do que uma possibilidade, porque o teste
*                                                          (v >= l->tail->info) antes do loop impede que isso
*                                                          aconteca;
*
*              if (prim==l->head){...}: Aqui testa se o novo no vai ser inserido na primeira posicao
*                                              e vai virar o novo head.
*
*              else {...}: Se nao cair no if de cima, significa que o novo no vai ser inserido no meio
*                          da lista. Ai ele conecta o novo no com o no que vem antes dele;
*
*              n->prox = prim, prim->ant = n: Aqui conecta o novo no com o no que vem depois dele (prim);
*
*   l->tam++: Incrementa o tamanho da lista;
*
*/
void insereOLD(Lista_d* l, const int v) {
    Node_d* n = (Node_d*)malloc(sizeof(Node_d));
    Node_d* prim = NULL;

    if (l==NULL || n==NULL) return;
    n->info = v;
    n->prox = NULL;
    n->ant = NULL;
    if (l->tam==0) {
        l->head = n;
        l->tail = n;
    }
    else if (v >= l->tail->info) {
        n->ant = l->tail;
        l->tail->prox = n;
        l->tail = n;
    }
    else {
        prim = l->head;
        while (prim!=NULL && v >= prim->info)
            prim = prim->prox;
        if (prim==l->head) l->head = n;
        else {
            n->ant = prim->ant;
            prim->ant->prox = n;
        }
        n->prox = prim;
        prim->ant = n;
    }
    l->tam++;
}

/*inserePLD(Lista_d* l, const int v, int p):
*
*   Insere um no em uma posicao personalizada;
*
*   if (n==NULL || l==NULL || p < 0 || p > l->tam): Testa se a alocacao deu certo, se a lista foi inicializada,
*                                                   e se a posicao escolhida e valida;
*
*   n->info = v, n->prox = NULL, n->ant = NULL: Inicializa o novo no;
*
*   if (l->tam==0){...}: Caso a lista for vazia, o novo no vira head e tail;
*
*   else if (p == l->tam){...}: Caso a posicao escolhida seja a ultima, ele faz a operacao fora do loop while,
*                               pelo mesmo motivo que foi dado na funcao de cima;
*
*
*   else{...}: Se cair aqui significa que a insercao vai ser no inicio ou no meio;
*
*              while (prim!=NULL && p-- > 0): Caminha pela lista ate que prim
*                                             aponte para o no que ocupa a posicao
*                                             passada como argumento;
*
*              if (prim==l->head){...}: Caso prim seja igual a l->head, quer dizer que
*                                       o loop nao andou nenhuma vez, ou seja, o novo
*                                       no vai ser o l->head da lista;
*
*              else {...}: Se cair aqui significa que a insercao vai ser no meio da lista,
*                          entao ele conecta o novo no ao anterior;
*
*              n->prox = prim, prim->ant = n: Conecta o novo no a prim;
*
*   l->tam++: Incrementa o tamanho da lista;
*
*/
void inserePLD(Lista_d* l, const int v, int p) {
    Node_d* n = (Node_d*)malloc(sizeof(Node_d));
    Node_d* prim = NULL;

    if (n==NULL || l==NULL || p < 0 || p > l->tam) return;
    n->info = v;
    n->prox = NULL;
    n->ant = NULL;
    if (l->tam==0) {
        l->head = n;
        l->tail = n;
    }
    else if (p == l->tam) {
        l->tail->prox = n;
        n->ant = l->tail;
        l->tail = n;
    }
    else {
        prim = l->head;
        while (prim!=NULL && p-- > 0)
            prim = prim->prox;
        if (prim==l->head) l->head = n;
        else {
            n->ant = prim->ant;
            prim->ant->prox = n;
        }
        n->prox = prim;
        prim->ant = n;
    }
    l->tam++;
}

/*rmPLD(Lista_d* l, int p):
*
*   Remove um no numa posicao especifica;
*
*   Retorna 1 pra sucesso, 0 pra problema com a lista, -1 pra problema com a posicao;
*
*   if (l==NULL || l->tam==0){...}: Testa pra lista vazia ou nao inicializada;
*
*   if (p < 0 || p >= l->tam){...}: Testa pra posicao invalida;
*
*   if (p==l->tam-1){...}: Cai aqui se o no que vai ser removido estiver na ultima posicao.
*                          Faz com que o ponteiro auxiliar (rm) aponte para o tail da lista
*                          e faz com que o no anterior ao atual tail vire o novo tail;
*
*                          if (l->tail==NULL){...}: Aqui testa pra caso a lista tenha apenas o
*                                                   no que vai ser removido, porque na linha de
*                                                   cima, l->tail viraria NULL caso a lista tenha
*                                                   apenas um elemento, ja que o anterior dele
*                                                   seria NULL. Caso seja verdadeiro, faz com que
*                                                   head vire NULL tambem, caso nao, faz com que
*                                                   o prox do novo tail aponte para NULL;
*
*   else {...}: Aqui vai cair se o no a ser removido estiver na primeira posicao ou no meio da lista.
*
*               while (rm!=NULL && p-- > 0){...}: Caminha pela lista ate que rm aponte para o no
*                                                 que vai ser removido;
*
*               if (rm==l->head){...}: So cai aqui se o loop nao andar nenhuma vez, o que significa que
*                                      que o no a ser removido ta na primeira posicao. Nesse caso aqui,
*                                      diferente do teste pra ultima posicao, ele nao precisa testar se
*                                      o no que vai ser removido e o unico da lista, ja que o teste pra
*                                      ultima posicao [if (l->tail==NULL)] ja garante que que nenhuma
*                                      lista de elemento unico passe pra esse bloco do codigo;
*
*               else{...}: Aqui so cai se o no a ser removido estiver no meio da lista, ai ele conecta
*                          o no que vem antes de rm com o no que vem depois de rm;
*
*   free(prim): Libera a memoria do no removido;
*
*   l->tam--: Decrementa o tamanho da lista;
*
*/
int rmPLD(Lista_d* l, int p) {
    Node_d* rm = NULL;

    if (l==NULL || l->tam==0) return 0;
    if (p < 0 || p >= l->tam) return -1;
    if (p==l->tam-1) {
        rm = l->tail;
        l->tail = l->tail->ant;
        if (l->tail==NULL)
            l->head = NULL;
        else
            l->tail->prox = NULL;
    }
    else {
        rm = l->head;
        while (rm!=NULL && p-- > 0)
            rm = rm->prox;
        if (rm==l->head) {
            l->head = rm->prox;
            l->head->ant = NULL;
        }
        else {
            rm->ant->prox = rm->prox;
            rm->prox->ant = rm->ant;
        }
    }
    free(rm);
    l->tam--;
    return 1;
}

/*rmVLD(Lista_d* l, const int v):
*
*   Remove todos os nos de um determinado valor (v);
*
*   Retorna a quantidade de nos removidos pra sucesso, 0 pra erro;
*
*   if (l==NULL || l->tam==0){...}: Testa se a lista foi inicializada ou ta vazia;
*
*   while (l->head!=NULL && l->head->info==v){...}: Esse while serve pra retirar o primeiro no
*                                                   da lista caso ele tenha o valor procurado. A razao
*                                                   pra usar essa tecnica e que depois desse loop ou a
*                                                   lista vai estar vazia ou o primeiro elemento nao vai
*                                                   ter o valor que a gente procura, o que significa que a
*                                                   funcao nao vai ter mais que tratar remocao no head da
*                                                   lista enquanto tambem trata remocao no meio e no fim;
*
*   if (l->head==NULL){...}: Testa se a lista ta vazia depois do loop, caso sim, faz com que tail aponte
*                            para NULL tambem, indicando uma lista vazia;
*
*   else{...}: Cai aqui caso a lista nao esteja vazia. Faz com que l->head->ant aponte para NULL, por ser o
*              primeiro no da lista. Faz com que aux aponte para o atual head da lista, que nao contem o
*              valor procurado. Faz com que rm aponte para o proximo no depois de head, que talvez
*              contenha o valor procurado, ou caso a lista sobre apenas com um elemento ele vai ser NULL
*              e a funcao nunca vai entrar no segundo loop;
*
*   while (rm){...}: Caminha pela lista ate que chegue no fim.
*
*                    if (rm->info==v){...}: Caso rm contenha o valor procurado;
*
*                                           if (rm==l->tail){...}: Se rm apontar para o tail da lista, entao
*                                                                  e necessario transformar o elemento anterior
*                                                                  no atual tail;
*
*                                           else{...}: Caso rm nao aponte para o tail da lista, entao e necessario
*                                                      fazer a ponte entre o no depois dele e o no que vem antes dele;
*
*                                           aux->prox = rm->prox: Conclui a ponte entre o no anterior a rm e o posterior;
*
*                                           free(rm): Libera a memoria do no que rm aponta;
*
*                                           rm = aux->prox: Como rm foi liberado, ele nao aponta pra nada, entao e necessario
*                                                           fazer com que ele aponte para o proximo no nao testado da lista;
*
*                    else{...}: Caso o no apontado por rm atualmente nao tenha o valor procurado, apenas salva rm atual em aux
*                              e avanca rm;
*
*   l->tam -= q: Atualiza o tamanho da lista;
*
*/
int rmVLD(Lista_d* l, const int v) {
    Node_d* rm = NULL;
    Node_d* aux = NULL;
    int q = 0;

    if (l==NULL || l->tam==0) return 0;
    while (l->head!=NULL && l->head->info==v) {
        aux = l->head;
        l->head = l->head->prox;
        free(aux);
        q++;
    }
    if (l->head==NULL) l->tail = NULL;
    else {
        l->head->ant = NULL;
        aux = l->head;
        rm = l->head->prox;
    }
    while (rm) {
        if (rm->info==v) {
            if (rm==l->tail) l->tail = aux;
            else rm->prox->ant = aux;
            aux->prox = rm->prox;
            free(rm);
            rm = aux->prox;
            q++;
        }
        else {
            aux = rm;
            rm = rm->prox;
        }
    }
    l->tam -= q;
    return q;
}

/*rmFLD(Lista_d* l, const int v):

    Remove o primeiro no que contenha o valor passado como argumento;

    Retorna a posicao do no removido pra sucesso, -1 para falha;

    if (l==NULL || l->tam==0){...}: Testa se a lista foi inicializada ou ta vazia;

    if (l->head->info==v){...}: Testa se o valor procurado ta na primeira posicao da lista,
                                caso sim, altera o ponteiro l->head e libera a memoria da
                                do antigo l->head. Assim como testa se a funcao tem apenas
                                um elemento (o que sera removido), caso sim, atualiza o
                                ponteiro l->tail para NULL, indicando que a lista ta vazia.
                                Decrementa o tamanho da lista e retorna a posicao removida;

    p = l->tam-1: Ajusta o valor de p para que armazene o valor da ultima posicao, para
                  complementar o teste a seguir;

    f (l->tail->info==v){...}: Testa se o valor procurado ta na ultima posicao da lista, esse
                               teste e util porque evita que a operacao tenha complexidade de
                               tempo O(n) caso o valor encontrado esteja na ultima posicao. Com
                               esse teste, esse operacao se torna O(1). Caso seja verdadeiro,
                               atualiza o tail da lista para a posicao anterior, faz com que o
                               ponteiro prox do novo tail aponte para NULL e libera a memoria
                               ocupada pelo no que vai ser removido. Decrementa o tamanho da lista
                               e retorna a posicao removida;

    p = 1: Atualiza o valor de p para que armazene a posicao do no atual;

    aux = l->head: aux agora armazena o valor do head, que nao contem o valor procurado;

    rm = l->head->prox: rm armazena o valor do segundo no da lista, que vai ser onde o
                        loop vai comecar procurando pelo valor desejado;

    while (rm){...}: Caminha pela lista ate chegar no final, procurando pelo valor passado como argumento;

                     if (rm->info==v){...}: Caso ache o valor, que nesse caso vai obrigatoriamente estar
                                            no meio da lista, faz a ponte entre o elemento anterior e o
                                            proximo. Libera a memoria ocupada pelo no a ser removido,
                                            atualiza o tamanho da lista e retorna a posicao removida;

                     else{...}: Caso nao seja o valor procurado, avanca a lista e incrementa o valor de p;

*/
int rmFLD(Lista_d* l, const int v) {
    Node_d* aux = NULL;
    Node_d* rm = NULL;
    int p = 0;

    if (l==NULL || l->tam==0) return -1;
    if (l->head->info==v) {
        aux = l->head;
        l->head = l->head->prox;
        free(aux);
        if (l->head==NULL) l->tail=NULL;
        else l->head->ant = NULL;
        l->tam--;
        return p;
    }
    p = l->tam-1;
    if (l->tail->info==v) {
        aux = l->tail;
        l->tail = l->tail->ant;
        l->tail->prox = NULL;
        free(aux);
        l->tam--;
        return p;
    }
    p = 1;
    aux = l->head;
    rm = l->head->prox;
    while (rm) {
        if (rm->info==v) {
            aux->prox = rm->prox;
            aux->prox->ant = rm->ant;
            free(rm);
            l->tam--;
            return p;
        }
        else {
            aux = rm;
            rm = rm->prox;
            p++;
        }
    }
    return -1;
}

/*searchLD(Lista_d* l, const int v):
*
*   Procura pelo primeiro no que contenha o valor procurado;
*
*   Retorna a posicao do no pra sucesso, -1 pra falha;
*
*   if (l==NULL || l->tam==0){...}: Testa se a lista foi inicializada ou ta vazia;
*
*   if (l->head->info==v){...}: Testa se o valor ta no primeiro no;
*
*   p = l->tam-1: Atualiza o valor de p pra complementar o teste a seguir;
*
*   if (l->tail->info==v){...}: Testa se o valor ta no ultimo no;
*
*   p = 1: Atualiza o valor de p de novo, mas agora avancando um no;
*
*   search = l->head->prox: Faz com que o ponteiro auxiliar aponte pro segundo no da lista;
*
*   while (search->prox){...}: Caminha pela lista a partir do segundo no ate o penultimo no;
*
*/
int searchLD(Lista_d* l, const int v) {
    Node_d* search = NULL;
    int p = 0;

    if (l==NULL || l->tam==0) return -1;
    if (l->head->info==v) return p;
    p = l->tam-1;
    if (l->tail->info==v) return p;
    p = 1;
    search = l->head->prox;
    while (search->prox) {
        if (search->info==v) return p;
        else {
            search = search->prox;
            p++;
        }
    }
    return -1;
}

/*killLD(Lista_d* l):
*
*   Elimina a lista duplamente encadeada;
*
*   while (kill){...}: Primeiro elimina a estrutura propria da lista;
*
*   free(l): Agora elimina a estrutura da struct gerenciadora;
*
*/
void killLD(Lista_d* l) {
    Node_d* aux = NULL;
    Node_d* kill = NULL;

    if (l==NULL) return;
    kill = l->head;
    while (kill) {
        aux = kill;
        kill = kill->prox;
        free(aux);
    }
    free(l);
}
