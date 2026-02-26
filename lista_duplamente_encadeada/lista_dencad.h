#ifndef LISTA_DUP_ENCAD_H
#define LISTA_DUP_ENCAD_H

#include <stddef.h>
#include <stdbool.h>

typedef enum {
    LD_SUCCESS = 0, // sucesso na operacao
    LD_MEM_ERR, // erro de memoria (alocacao, etc)
    LD_NULL_PTR, // ponteiro nulo
    LD_EMPTY, // lista vazia
    LD_INV_POS, // posicao invalida
    LD_VAL_NOT_FOUND // valor nao encontrado
} LD_Status;

/*
    a IA Gemini 3 Pro me foi bem util na hora de pensar na forma de escrever as linhas de código, ela traz 
    ideias estruturais muito úteis a cerca do design que eu nunca teria pensado sozinho;

    Nenhuma IA foi usada para gerar código.

    Fontes de ajuda: Stack Overflow, W3Schools, Geeks For Geeks;

*/

/* struct node_d:
 
    Definicao da struct dos nos da lista;
 
    _d no fim do nome significa que a struct foi
    feita para listas duplamente encadeadas;
 
    void* info: ponteiro void que armazena a informacao
                contida no nó atual da lista. O ponteiro
                void permite que a lista seja genérica a 
                respeito do tipo de dado armazenado;
 
    struct node_d* prox: ponteiro auto referenciado
                         que vai apontar para o proximo
                         no da lista;
 
    struct node_d* ant: ponteiro auto referenciado
                        que vai apontar para o no
                        anterior da lista;
 
*/
struct node_d {
    void* info;

    struct node_d* prox;
    struct node_d* ant;
};
typedef struct node_d Node_d;

/* struct lista_d:
 
    Definicao da struct gerenciadora da lista;
 
    _d no fim do nome significa que a struct foi feita
    para listas encadeadas;
 
    size_t tam: quantidade de nos da lista;

    size_t data_type: quantidade de bytes que o tipo de 
                      dado da lista ocupa na memoria;
 
    Node_d* head: ponteiro para o no inicial da lista;
 
    Node_d* tail: ponteiro para o no final da lista;
 
    Tipo assim, a vantagem de usar a struct gerenciadora
    que operacoes como inserir no inicio ou o final vao
    ser O(1) agora, e qualquer funcao que faca alteracao no
    corpo da lista nao vai precisar retornar alguma coisa mais,
    porque a alteracao vai ser na struct gerenciadora, e o
    ponteiro pra essa struct nao precisa saber disso;
 
*/
struct lista_d {
    size_t tam;
    size_t data_type;

    Node_d* head;
    Node_d* tail;
};
typedef struct lista_d Lista_d;

/* typedef int (*Comparador)(const void* a, const void* b):

    define Comparador como sendo um tipo de ponteiro para funcao que
    recebe dois ponteiros para void e retorna um int;

    isso aqui foi mais pra limpar a sintaxe dos headers das funcoes
    que fazem uso desse ponteiro para uma funcao de comparacao, ja 
    que a sintaxe de ponteiro pra funcao em C é podre;

*/
typedef int (*Comparador) (const void* a, const void* b);

/* Lista_d* criaLD(size_t data_size):

    Retorna uma nova estrutura de lista duplamente encadeada;

    Lista_d* lista =...: Cria um potenteiro para struct gerenciadora
                         e aloca uma struct gerenciadora;

    if (lista==NULL) {...}: testa se a alocacao deu certo;

    lista->data_type = data_size: guarda o valor em bytes do
                                  tipo de dado que a lista vai
                                  armazenar;

    nlista->tam = 0x0: inicializa o tamanho da lista em 0;

    lista->head=NULL, lista->tail=NULL: inicializa os ponteiros head
                                        e tail em NULL:

*/
Lista_d* criaLD(size_t);

/* inserePLD(Lista_d* l, const int v, int p):
 
    Insere um no em uma posicao personalizada;

    retorna o status da operacao;

    Possiveis flags de retorno:
        LD_NULL_PTR -> ponteiro nulo;
        LD_MEM_ERR -> erro de alocacao;
        LD_INV_POS -> posicao invalida;
        LD_SUCCESS -> sucesso;
 
    if (lista==NULL || valor==NULL) {...}: testa se o ponteiro lista ou valor é NULL;

    if (p > lista->tam) {...}: testa se p é uma posicao valida;

    if (node==NULL) {...}: testa se a alocacao do novo nó deu certo;

    if (node->info==NULL) {...}: testa se a alocacao do ponteiro info deu certo;

    memcpy(node->info, valor, lista->data_type): olhe insereILD();

    node->prox = NULL, node->ant = NULL: inicializa os ponteiros do novo nó 
                                         em NULL por seguranca;

    if (lista->tam==0x0) {...}: caso a lista esteja vazia;

    else if (p==0) {...}: caso o novo nó seja o novo head;

    else if (p == lista->tam) {...}: caso o novo nó seja o novo tail;

    else {...}: insercao no meio da lista;

    lista->tam++: incrementa o tamanho da lista em 1;
 
*/
LD_Status inserePLD(Lista_d*, const void*, size_t);

/* LD_Status insereILD(Lista_d* lista, const void* valor):
 
    insere um no no inicio da lista;

    retorna a flag que indica o status da operacao

    Possiveis flags:
        LD_NULL_PTR -> ponteiro nulo
        LD_MEM_ERR -> erro de alocacao
        LD_SUCCESS -> sucesso
 
    if (lista==NULL){...}: testa se o ponteiro da lista é nulo;

    if (node==NULL){...}: testa se  a alocacao do novo nó deu certo

    if (node->info==NULL){...}: testa se a alocacao de memoria do ponteiro 
                                de info do nó deu certo;
                                
    memcpy(node->info, valor, lista->type): copia a quantidade especifica de bytes
                                            (lista->data_type) do ponteiro passado 
                                            como argumento (que contém o valor que 
                                            vai ser armazenado no nó) para o ponteiro
                                            da lista. Isso cria um cópia do valor que
                                            apenas a lista tem acesso, assim, qualquer 
                                            alteracao feita no ponteiro *valor fora da 
                                            funcao nao vai ter efeito no valor que esta
                                            dentro do no da lista;

    node->prox = lista->head: faz com que o novo no aponte para o atual head da lista;

    node->ant = NULL: faz com que o ponteiro ant do novo nó aponte para NULL, pelo fato
                      dele ser o primeiro no da lista;

    if (lista->tam==0) {...}: caso a lista esteja vazia, o novo no vai ser tanto head
                              quanto tail;

                              else {...}: caso contrario, o ponteiro ant do atual head
                                          da lista aponta para o novo nó;

    lista->head = node: transforma o novo nó no head da lista;

    lista->tam++: incrementa o tamanho da lista em 1;

*/
LD_Status insereILD(Lista_d*, const void*);

/* LD_Status insereFLD(Lista_d*, const void*):
 
    Insere um no no fim da lista;

    retorna o status da operacao;

    Possiveis flags de retorno: 
        LD_NULL_PTR -> ponteiro da lista ou valor nulos;
        LD_MEM_ERR -> erro de alocacao;
        LD_SUCCESS -> sucesso;
 
    if (lista==NULL || valor==NULL) {...}: testa se algum ponteiro é NULL;
 
    if (node==NULL) {...}: testa se a alocacao do novo nó deu certo;

    if (node->info==NULL) {...}: testa se a alocacao do ponteiro info deu certo;

    memcpy(node->info, valor, lista->data_type): mesma coisa do insereILD();

    node->prox = NULL, node->ant = lista->tail: por ser o ultimo nó da lista, seu ponteiro
                                                prox vai apontar pra NULL e seu ponteiro 
                                                ant vai apontar pro atual tail. Caso a lista
                                                esteja vazia (lista->tail==NULL), dá certo 
                                                do mesmo jeito;

    if (lista->tail==NULL) {...}: testa se a lista ta vazia, caso sim, o novo nó será o head;

                                  else {...}: caso contrario, o ponteiro prox do atual tail agora
                                              apontará para o novo nó que será o tail;

    lista->tail = node: transforma o novo nó no tail da lista;

    lista->tam++: incrementa o tamanho da lista em 1;
 
*/
LD_Status insereFLD(Lista_d*, const void*);

/* LD_Status insereOLD(Lista_d*, const void*, Comparador):
 
    Insere um novo no de forma ordenada;
 
    espera que a lista passada esteja ordenada;

    retorna o status da operacao;

    Possiveis flags de retorno:
        LD_NULL_PTR -> ponteiro nulo;
        LD_MEM_ERR -> erro de alocacao;
        LD_SUCCESS -> sucesso;
 
    if (lista==NULL || valor==NULL) {...}: testa se o ponteiro lista ou valor é NULL;

    if (node==NULL) {...}: testa se a alocacao do novo nó deu certo;

    if (node->info==NULL) {...}: testa se a alocacao do ponteiro info deu certo;

    memcpy(node->info, valor, lista->data_type): olhar insereILD();

    node->prox==NULL, node->ant==NULL: inicializa os ponteiros do novo nó em NULL,
                                       por uma questao de seguranca;

    if (lista->tam==0x0) {...}: caso a lista esteja vazia, o novo nó sera tanto head quanto tail;

    else if (cmp(node->info, lista->head->info) < 0): caso o valor armazenado no novo nó seja menor
                                                      que o valor do head, este será o novo head;

    else if (cmp(node->info, lista->tail->info) >= 0): caso o valor armazenado no novo nó seja maior
                                                       ou igual ao valor do tail, este será o novo tail;

    else {...}: caso a insercao seja no meio da lista;

    lista->tam++: incrementa o tamnho da lista em 1;
 
*/
LD_Status insereOLD(Lista_d*, const void*, Comparador);

/* LD_Status rmPLD(Lista_d*, size_t):
 
    Remove um no numa posicao especifica;
 
    Retorna o status da operacao;

    Possiveis flags de retorno:
        LD_NULL_PTR -> ponteiro nulo;
        LD_INV_POS -> posicao invalida;
        LD_EMPTY -> lista vazia;
        LD_SUCCESS -> sucesso

    if (lista==NULL) {...}: testa se o ponteiro lista e nulo;

    if (p >= lista->tam) {...}: testa se a posicao passada como argumento é valida.
                                Nao é necessario testar para valor negativo porque
                                o tipo da variavel p é size_t;

    if (lista->tam==0x0) {...}: testa se a lista ta vazia;

    if (p==0x0) {...}: caso a remocao seja do primeiro elemento da lista (head);

    else if (p==lista->tam-1) {...}: caso a remocao seja do ultimo elemento da lista (tail);

    else {...}: caso a remocao seja no meio da lista;

    free(rm->info), free(rm): libera o ponteiro info do nó a ser removido e depois 
                              o proprio no a ser removido;

    if (lista->head==NULL) {...}: caso depois da liberacao a lista esteja vazia, é necessario
                                 apontar o tail para NULL tambem;

    lista->tam--: decrementa o tamanho da lista em 1;
 
*/
LD_Status rmPLD(Lista_d*, size_t);

/*rmVLD(Lista_d* l, const int v):
 
    Remove todos os nos de um determinado valor (v);
 
    Retorna a quantidade de nos removidos pra sucesso;

    Possiveis flags de retorno:
        LD_NULL_PTR -> ponteiro nulo;
        LD_EMPTY -> lista vazia;
        LD_SUCCESS -> sucesso;
 
    while (lista->head!=NULL && cmp(lista->head->info, valor)==0){...}: Esse while serve pra retirar o primeiro no
                                                    da lista caso ele tenha o valor procurado. A razao
                                                    pra usar essa tecnica e que depois desse loop ou a
                                                    lista vai estar vazia ou o primeiro elemento nao vai
                                                    ter o valor que a gente procura, o que significa que a
                                                    funcao nao vai ter mais que tratar remocao no head da
                                                    lista enquanto tambem trata remocao no meio e no fim;
 
    if (lista->head==NULL){...}: Testa se a lista ta vazia depois do loop, caso sim, faz com que tail aponte
                                 para NULL tambem, indicando uma lista vazia;
 
    else{...}: Cai aqui caso a lista nao esteja vazia. Faz com que l->head->ant aponte para NULL, por ser o
               primeiro no da lista. Faz com que aux aponte para o atual head da lista, que nao contem o
               valor procurado. Faz com que rm aponte para o proximo no depois de head, que talvez
               contenha o valor procurado, ou caso a lista sobre apenas com um elemento ele vai ser NULL
               e a funcao nunca vai entrar no segundo loop;
 
    while (rm){...}: Caminha pela lista ate que chegue no fim.
 
                     if (cmp(rm->info, valor)==0){...}: Caso rm contenha o valor procurado;
 
                                            if (rm==lista->tail){...}: Se rm apontar para o tail da lista, entao
                                                                   e necessario transformar o elemento anterior
                                                                   no atual tail;
 
                                            else{...}: Caso rm nao aponte para o tail da lista, entao e necessario
                                                       fazer a ponte entre o no depois dele e o no que vem antes dele;
 
                                            aux->prox = rm->prox: Conclui a ponte entre o no anterior a rm e o posterior;
 
                                            free(rm->info): libera o ponteiro info de rm;
                                            free(rm): Libera a memoria do no que rm aponta;
 
                                            rm = aux->prox: Como rm foi liberado, ele nao aponta pra nada, entao e necessario
                                                           fazer com que ele aponte para o proximo no nao testado da lista;

                     else{...}: Caso o no apontado por rm atualmente nao tenha o valor procurado, apenas salva rm atual em aux
                                e avanca rm;
 
    lista->tam -= q: Atualiza o tamanho da lista;
 
*/
size_t rmVLD(Lista_d*, const void*, Comparador, LD_Status*);

/* LD_Status rmILD(LIsta_d*):

    Usa a funcao rmPLD() pra remover na primeira posicao;

*/
LD_Status rmILD(Lista_d*);

/* LD_Status rmULD(LIsta_d*):

    Usa a funcao rmPLD() pra remover na ultima posicao;

*/
LD_Status rmULD(Lista_d*);

/*rmFLD(Lista_d* l, const int v):

    Remove o primeiro no que contenha o valor passado como argumento;

    Retorna a posicao do no removido pra sucesso, 0 para falha;

    Possiveis flags de retorno:
        LD_NULL_PTR -> ponteiro nulo;
        LD_EMPTY -> lista vazia;
        LD_VAL_NOT_FOUND -> valor nao encontrado;
        LD_SUCCESS -> sucesso;

    if (lista==NULL || valor==NULL) {...}: testa se os ponteiros estao inicializados;

    if (lista->tam==0x0) {...}: testa se a lista ta vazia;

    if (cmp(lista->head->info, valor)==0){...}: remocao no head;

    if (cmp(lista->tail->info, valor)==0) {...}: remocao no tail;

    rm = lista->head->prox: rm armazena o valor do segundo no da lista, que vai ser onde o
                            loop vai comecar procurando pelo valor desejado;

    while (rm){...}: Caminha pela lista ate chegar no final, procurando pelo valor passado como argumento;

                     if (cmp(rm->info, valor)==0) {...}: valor no meio da lista

                     else{...}: Caso nao seja o valor procurado, avanca a lista e incrementa o valor de p;

*/
size_t rmFLD(Lista_d*, const void*, Comparador, LD_Status*);

/* size_t searchLD(const Lista_d*, const void*, Comparador, LD_Status*):
 
    Procura pelo primeiro no que contenha o valor procurado;
 
    Retorna a posicao do no pra sucesso, 0 para falha (!!!!!)

    Possiveis flags de retorno:
        LD_NULL_PTR -> ponteiro nulo;
        LD_EMPTY -> lista vazia;
        LD_VAL_NOT_FOUND -> valor nao encontrado;
        LD_SUCCESS -> sucesso;

    if (lista==NULL || valor==NULL) {...}: testa se os ponteiros estao inicializados;

    if (lista->tam==0x0) {...}: testa se a lista ta vazia;

    if (cmp(lista->head->info, valor)==0) {...}: caso o valor esteja no head da lista;

    else if (cmp(lista->tail->info, valor)==0) {...}: caso o valor esteja no tail;

    else {...}: caso o valor esteja no meio da lista ou nao exista um nó que armazene
                o valor passado como argumento;
 
*/
size_t searchLD(const Lista_d*, const void*, Comparador, LD_Status*);

/* void* getNodeValLD(const Lista_d* lista, size_t p, LD_Status* flag):

    Procura pelo nó na posicao passada como argumento

    Retorna o endereco de memoria do ponteiro info do nó na posicao p;

    Possiveis flags de retorno:
        LD_NULL_PTR -> ponteiro nulo;
        LD_INV_POS -> posicao invalida;
        LD_SUCCESS -> sucesso;

    if (lista==NULL) {...}: testa se o ponteiro foi inicializado;

    if (p >= lista->tam) {...}: testa se a posicao é valida;

    if (p==0x0) {...}: caso seja o primeiro no da lista;

    if (p == lista->tam-1) {...}: caso seja o ultimo no da lista;

    while (search!=NULL && p-- > 0) {...}: anda até o nó procurado;

    if (search==NULL) {...}: verificacao de seguranca, mas quase nunca
                             vai ser usada;

*/
void* getNodeValLD(const Lista_d*, size_t, LD_Status*);

/* size_t sizeLD(const Lista_d*, LD_Status*):

    Retorna a quantidade de nos da lista;

    Possiveis flags de retorno:
        LD_NULL_PTR -> ponteiro nulo;
        LD_SUCCESS -> sucesso;

    if (lista==NULL) {...}: testa se o ponteiro foi inicializado;

*/
size_t sizeLD(const Lista_d*, LD_Status*);

/* bool taVaziaLD(const Lista_d*, LD_Status*):

    Retorna se a lista ta vazia ou nao;

    Possiveis flags de retorno:
        LD_NULL_PTR -> ponteiro nulo;
        LD_SUCCESS -> sucesso;

    if (lista==NULL) {...}: testa se o ponteiro foi inicializado;

*/
bool taVaziaLD(const Lista_d*, LD_Status*);

/* LD_Status limpaLD(Lista_d* lista):

    Limpa a lista por completo

    Retorna o status da operacao

    Possiveis flags de retorno:
        LD_NULL_PTR -> ponteiro nulo;
        LD_EMPTY -> lista vazia;
        LD_SUCCESS -> sucesso;

    while (rm) {...}: varre tudo;

    lista->head = NULL, lista->tail = NULL: arruma os dois ponteiros da lista;

*/
LD_Status limpaLD(Lista_d*);

/* LD_Status killLD(Lista_d* lista):
 
    Elimina a lista duplamente encadeada;
 
    tipo assim, só olha a funcao de cima e descobre as tres linhas diferentes,
    eu te desafio;
 
*/
LD_Status killLD(Lista_d*);

#endif // LISTA_DUP_ENCAD_H

