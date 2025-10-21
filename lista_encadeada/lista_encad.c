#include "lista_encad.h"
#include <stdio.h>
#include <stdlib.h>

/*criaL(void):

    Cria uma struct gerenciadora para lista;

    Lista_e* n...: cria um ponteiro para struct gerenciadora e
                   aloca uma struct gerenciadora;

    n->tam = 0: Define o tamanho inicial da lista como 0;

    n->head = NULL: Por nao ter elementos, o ponteiro head e null;

    n->tail = NULL: Mesma coisa do head;

*/
Lista_e* criaL(void) {
    Lista_e* n = (Lista_e*)malloc(sizeof(Lista_e));
    n->tam = 0;
    n->head = NULL;
    n->tail = NULL;
    return n;
}

/*buildEA(int* arr, int tam):
*
*   Constroi uma lista a partir de um array;
*
*   Retorna a lista vazia caso o tamanho do array seja invalido (<=0)
*   e a lista preenchida caso seja sucesso;
*
*   if (tam<=0){...}: Testa se o tamanho do array e valido, caso nao,
*                     retorna a lista vazia;
*
*   while (tam-- > 0){...}: Preenche a lista com o valor que o ponteiro
*                           arr aponta a cada iteracao;
*
*/
Lista_e* buildEA(int* arr, int tam) {
    Lista_e* l = criaL();

    if (tam<=0)
        return l;
    while (tam-- > 0) {
        insereFL(l, *arr);
        arr++;
    }
    return l;
}

/*insereIL(Lista_e* l, const int v):
*
*   Insere um no no inicio da lista;
*
*   Node_e* n...: Cria um ponteiro para um no
*                 e aloca um no;
*
*   n->info = v: Atribui o valor ao no;
*
*   n->prox = l->head: Por ser inserido no inicio, agora ele aponta
*                      para o antigo primeiro elemento. Caso a lista
*                      esteja vazia, l->head vai ser NULL, o que faz
*                      com que essa linha funcione perfeitamente para
*                      qualquer situacao;
*
*   l->head: Passa o endereco do novo no para o ponteiro head da struct
*            gerenciadora, ja que ele e o head da lista agora;
*
*   if (l->tam==0){...}: Caso a lista esteja vazia, o novo no vai ser o
*                         ultimo no tambem;
*
*   l->tam++: incrementa o tamanho da lista;
*
*/
void insereIL(Lista_e* l, const int v) {
    Node_e* n = (Node_e*)malloc(sizeof(Node_e));

    if (n==NULL)
        return;
    n->info = v;
    n->prox = l->head;
    l->head = n;
    if (l->tam==0)
        l->tail = n;
    l->tam++;
}

/*insereFL(Lista_e* l, const int v):
*
*   Insere um novo no fim da lista;
*
*   Node_e* n...: Cria um ponteiro para um no e
*                 aloca um no;
*
*   n->info = v: Atribui o valor ao no;
*
*   n->prox = NULL: Faz com que o novo no aponte
*                   para NULL, ja que ele vai ser
*                   o novo ultimo no da lista;
*
*   if (l->tam==0){...}: Caso a lista esteja vazia,
*                      o novo no vai ser o tail
*                      e o head da lista ao mes-
*                      mo tempo;
*
*   l->tail = n: Agora o ponteiro para o ultimo
*                elemento da lista aponta para
*                o novo no;
*
*   l->tam++: Incrementa o valor da lista;
*
*/
void insereFL(Lista_e* l, const int v) {
    Node_e* n = (Node_e*)malloc(sizeof(Node_e));

    if (n==NULL)
        return;
    n->info = v;
    n->prox = NULL;
    if (l->tam==0)
        l->head = n;
    else
        l->tail->prox = n;
    l->tail = n;
    l->tam++;
}

/*insereOL(Lista_e* l, const int v):
*
*   Insere um no de forma ordenada na lista;
*
*   A funcao espera que a lista esteja ordenada,
*   senao, o comportamento sera indefinido;
*
*   if (n==NULL){...}: Testa se a alocacao de memoria deu certo;
*
*   n->info = v: Atribui o valor ao novo no;
*
*   while (prim!=NULL && n->info > prim->info){...}: Caminha pela lista até que ache o local
*                                                    exato para colocar o novo no;
*
*   if (aux==NULL){...}: Caso aux seja NULL, quer dizer que o loop nao caminhou nenhuma vez,
*                        entao ou o valor a ser inserido é o menor, ou a lista ta vazia. Nas
*                        duas possibilidades, o novo no vai ser o novo head da lista;
*
*                        else: Aqui significa que entrou no loop, entao tem um elemento da lista
*                              que vem antes do valor novo;
*
*   if (prim==NULL){...}: Caso prim seja NULL, quer dizer que ou o loop nao caminhou nenhuma vez,
*                         ou ele caminhou ate chegar no fim da lista. Na primeira opcao, a lista
*                         ta vazia, na segunda opcao, o valor a ser inserido e o maior. Nas duas
*                         possibilidades, o novo no vai ser o novo tail da lista;
*
*   l->tam++: Incrementa o tamanho da lista;
*
*/
void insereOL(Lista_e* l, const int v) {
    Node_e* n = (Node_e*)malloc(sizeof(Node_e));
    Node_e* prim = l->head;
    Node_e* aux = NULL;

    if (n==NULL)
        return;
    n->info = v;
    while (prim!=NULL && n->info > prim->info) {
        aux = prim;
        prim = prim->prox;
    }
    if (aux==NULL)
        l->head = n;
    else
        aux->prox = n;
    n->prox = prim;
    if (prim==NULL)
        l->tail = n;
    l->tam++;
}

/*inserePL(Lista_e* l, const int v, const int p):
*
*   Insere um novo no de forma ordenada;
*
*   Espera que a lista ja esteja ordenada;
*
*   if (n==NULL){...}: Caso a alocacao de memoria falhe;
*
*   if (p < 0){...}: Caso a posicao seja invalida;
*
*   if (l->tam==0){...}: Caso a lista esteja vazia, o novo
*                        no inserido vai ser tanto o tail
*                        quanto o head da lista;
*
*   else if (p==0) {...}: Caso o novo no for inserido na
*                         primeira posicao, ele vai ser o
*                         novo head da lista;
*
*   else if (p>=(l->tam)){...}: Caso a posicao do novo no
*                               seja maior ou igual ao tamanho
*                               da lista, quer dizer que o novo
*                               no vai ser o tail da lista, ou seja,
*                               o ultimo no;
*
*   else{...}: Aqui significa que o novo no vai ser inserido no meio da
*              lista, para isso, um loop while caminha ate achar o no anterior
*              ao da posicao do novo no;
*
*   l->tam++: Incrementa o tamanho da lista;
*
*/
void inserePL(Lista_e* l, const int v, int p) {
    Node_e* n = (Node_e*)malloc(sizeof(Node_e));
    Node_e* prim = NULL;

    if (n==NULL)
        return;
    if (p < 0) {
        printf("erro: posicao invalida\n");
        free(n);
        return;
    }
    n->info = v;
    n->prox = NULL;
    if (l->tam==0) {
        l->head = n;
        l->tail = n;
    }
    else if (p==0) {
        n->prox = l->head;
        l->head = n;
    }
    else if (p>=(l->tam)) {
        l->tail->prox = n;
        l->tail = n;
    }
    else {
        prim = l->head;
        while (--p > 0)
            prim = prim->prox;
        n->prox = prim->prox;
        prim->prox = n;
    }
    l->tam++;
}

/*rmPL(Lista_e*, int):
*
*   Remove um no na posicao especificada;
*
*   Retorna 1 pra sucesso, -1 pra lista vazia e -2 pra posicao invalida;
*
*   if (l->tam==0){...}: Testa se a lista ta vazia;
*
*   if (p>=l->tam || p < 0){...}: Testa se a posicao passada e invalida;
*
*   for (i = 0; i < p; i++){...}: Caminha pela lista ate que o ponteiro
*                                 auxiliar aponte para o no anterior ao
*                                 que vai ser excluido e prim aponte para
*                                 o no que vai ser excluido;
*
*   if (aux==NULL){...}: Caso aux seja NULL, quer dizer que o loop nao foi
*                        ativado nenhuma vez, entao a posicao a ser excluida
*                        e a primeira, entao o atual segundo no da lista vira
*                        o head, isso serve tambem pra caso a lista tenha apenas
*                        um no, porque prim->prox vai ser NULL nesse caso.
*
*                        if (prim->prox==NULL){...}: Aqui ele continua o teste se
*                                                    a lista tem apenas um elemento,
*                                                    caso sim, ele aponta l->tail para
*                                                    NULL;
*
*   else{...}: Aqui cobre o caso do no a ser exlcluido estar no meio da lista, ou na ultima
*              posicao.
*
*              if (prim->prox==NULL){...}: Caso o no a ser excluido seja o ultimo, ele aponta
*                                          l->tail para aux, que como ja foi dito, vai ser o no
*                                          anterior ao que sera excluido;
*
*   free(prim): Libera memoria do no excluido;
*
*   l->tam--: Decrementa o tamanho da lista;
*
*/
int rmPL(Lista_e* l, const int p) {
    Node_e* aux = NULL;
    Node_e* prim = l->head;
    int i;

    if (l->tam==0)
        return -1;
    if (p>=l->tam || p < 0)
        return -2;
    for (i = 0; i < p; i++) {
        aux = prim;
        prim = prim->prox;
    }
    if (aux==NULL) {
        l->head = prim->prox;
        if (prim->prox==NULL)
            l->tail = NULL;
    }
    else {
        aux->prox = prim->prox;
        if (prim->prox==NULL)
            l->tail = aux;
    }
    free(prim);
    l->tam--;
    return 1;
}


/*rmVL(Lista_e* l, const int v):
*
*   Remove um todos os nos do valor passado como argumento;
*
*   Retorna a quantidade de nos retirados para sucesso, e 0 para erro;
*
*   if (l->tam==0){...}: Testa se a lista ta vazia;
*
*   while (l->head!=NULL && l->head->info==v){...}: Esse while caminha na lista enquanto o primeiro elemento
*                                                   for igual ao valor que sera retirado e enquanto a lista
*                                                   tiver elementos. Isso ajuda demais porque agora nao e
*                                                   necessario tratar de todos os casos em que o no a ser
*                                                   retirado e o primeiro. Quando esse loop acabar, ou a lista
*                                                   vai estar vazia, ou o primeiro elemento nao vai ter que ser
*                                                   retirado;
*
*   if (l->head==NULL){...}: Testa caso a lista termine o primeiro loop vazia. Se isso for o caso, o ponteiro
*                            tail da lista precisa se atualizado pra NULL tambem;
*
*                            else {...}: Faz com que aux aponte para o primeiro elemento, e prim aponte para o
*                                        elemento apos o l->head. Isso funciona porque a gente ja sabe que se a
*                                        lista nao ta vazia depois do primeiro loop, isso quer dizer que o atual
*                                        head da lista nao tem o valor que a gente quer remover, entao e seguro
*                                        pular pro segundo. Mesmo num cenario de uma lista com um elemento so,
*                                        prim apontaria pra NULL, e nao chegaria nem a entrar no segundo loop;
*
*   while (prim){...}: Loop que caminha pela lista a busca de elementos que contenham o valor a ser removido;
*
*                      if (prim->info==v){...}: Testa caso o elemento atual contenha o valor a ser removido;
*
*                                               if (prim==l->tail): Se o elemento atual for o ultimo elemento
*                                                                   da lista (tail), isso quer dizer que o no
*                                                                   anterior, atualmente sendo apontado por aux,
*                                                                   tem que ser o novo tail;
*
*                                               aux->prox = prim->prox: o no apontado por aux agora foi ligado
*                                                                       ao no posterior a prim, reconectando a
*                                                                       lista para que prim possa ser removido;
*
*                                               free(prim): libera o no prim;
*
*                                               prim = aux->prox: Re-atribui um valor a prim, porque atualmente
*                                               ele nao aponta pra nenhum no, ja que foi liberado. Nesse caso,
*                                               ele tem que apontar para o elemento apos aux, porque aux sempre
*                                               aponta para um no que ja foi testado;
*
*                                               ++q: incrementa a quantidade de elementos removidos;
*
*                       else {...}: avanca para o proximo elemento, salvando o atual em aux;
*
*   l->tam -= q: Decrementa a quantidade total de elementos da lista;
*
*/
int rmVL(Lista_e* l, const int v) {
    Node_e* aux = NULL;
    Node_e* prim = NULL;
    int q = 0;

    if (l->tam==0)
        return q;
    while (l->head!=NULL && l->head->info==v) {
        aux = l->head;
        l->head = l->head->prox;
        free(aux);
        ++q;
    }
    if (l->head==NULL)
        l->tail = NULL;
    else {
        aux = l->head;
        prim = l->head->prox;
    }
    while (prim) {
        if (prim->info==v) {
            if (prim==l->tail)
                l->tail = aux;
            aux->prox = prim->prox;
            free(prim);
            prim = aux->prox;
            ++q;
        }
        else {
            aux = prim;
            prim = prim->prox;
        }
    }
    l->tam -= q;
    return q;
}

/*rmFL(Lista_e* l, const int v):
*
*   Remove o primeiro no que contenha o valor passado como argumento;
*
*   Retorna a posicao que foi removida em caso de sucesso, e 0 para falha;
*
*   if (l->tam==0){...}: Testa se a lista ta vazia;
*
*   if (l->head->info==v){...}: Testa se o elemento procurado e o head da lista.
*
*                               if (l->head==NULL){...}: Testa se a lista tem apenas
*                                                        o elemento que vai ser retirado,
*                                                        caso sim, faz com que tail aponte
*                                                        para NULL;
*
*   aux = l->head, prim = l->head->prox: Faz com que aux aponte para o atual head, que
*                                        ja sabemos que nao e o elemento procurado, tambem
*                                        faz com que prim aponte para o segundo elemento da
*                                        lista;
*
*   p++: incrementa a posicao que vai ser retornada;
*
*   while (prim){...}: Loop que caminha pela lista procurando pelo valor que sera retirado.
*                      Se o valor for encontrado, conecta o elemento antecessor do atual ao
*                      sucessor do atual, assim se torna possivel liberar o no desejado.
*                      Testa se o no encontrado e o ultimo, caso sim, faz com que l->tail
*                      aponte para aux, o antecessor do atual. Libera o no com o valor desejado
*                      e decrementa o valor da lista, depois disso, retorna a posicao encontrada;
*
*   obs: eu nao especifiquei muito a explicacao desse funcao porque ela e muito parecida com
*        a anterior (rmVL);
*
*
*/
int rmFL(Lista_e* l, const int v) {
    Node_e* aux = NULL;
    Node_e* prim = NULL;
    int p = 0;

    if (l->tam==0)
        return -1;
    if (l->head->info==v) {
        aux = l->head;
        l->head = l->head->prox;
        free(aux);
        if (l->head==NULL)
            l->tail = NULL;
        l->tam--;
        return p;
    }
    aux = l->head;
    prim = l->head->prox;
    p++;
    while (prim) {
        if (prim->info==v) {
            aux->prox = prim->prox;
            if (prim==l->tail)
                l->tail = aux;
            free(prim);
            l->tam--;
            return p;
        }
        else {
            aux = prim;
            prim = prim->prox;
            p++;
        }
    }
    return -1;
}

/*searchL(Lista_e* l, const int v):
*
*   Busca por um valor na lista;
*
*   Retorna a posicao do no para sucesso e -1 para falha;
*
*   if (l->tam==0){...}: Testa se a lista ta vazia;
*
*   if (l->tail->info==v){...}: Testa se o valor procurado
*                               ta na ultima posicao, isso
*                               salva um bom tempo quando
*                               esse teste da verdadeiro;
*
*   while (prim->prox){...}: Caminha pela lista ate que
*                            que chegue no ultimo elemento,
*                            quando acha o elemento, retorna
*                            a posicao. Esse loop nao vai ate
*                            que prim seja NULL porque nao e
*                            necessario testar a ultima posicao
*                            de novo, uma vez que ela foi testada
*                            antes do loop;
*
*   if (prim->info==v){...}: Testa se a ultima posicao contem o
*                            valor procurado;
*
*/
int searchL(Lista_e* l, const int v) {
    Node_e* prim = NULL;
    int p = 0;

    if (l->tam==0)
        return -1;
    if (l->tail->info==v)
        return l->tam-1;
    prim = l->head;
    while (prim->prox) {
        if (prim->info==v)
            return p;
        else {
            prim = prim->prox;
            p++;
        }
    }
    if (prim->info==v)
        return p;
    return -1;
}

/*killL(Lista_e* l):
*
*   ELimina a lista;
*
*/
void killL(Lista_e* l) {
    Node_e* prim = l->head;
    Node_e* aux = NULL;

    if (l==NULL)
        return;
    while (prim) {
        aux = prim;
        prim = prim->prox;
        free(aux);
    }
    free(l);
}





