#ifndef LISTA_ENCAD_H
#define LISTA_ENCAD_H

#include <stddef.h>
#include <stdbool.h>

typedef enum {
    L_SUCCESS = 0, // sucesso na operacao
    L_MEM_ERR, // erro de memoria (alocacao, etc)
    L_NULL_PTR, // ponteiro nulo
    L_EMPTY, // lista vazia
    L_INV_POS, // posicao invalida
    L_VAL_NOT_FOUND // valor nao encontrado
} L_Status;

/*
    aqui tem a melhor explicacao que eu consegui pensar na hora de escrever essas funcoes,
    caso mesmo assim seja confuso, eu sinceramente nao sei o que dizer;

*/

/*
    a IA Gemini 3 Pro me foi bem util na hora de pensar na forma de escrever as linhas de código, ela traz 
    ideias estruturais muito úteis a cerca do design que eu nunca teria pensado sozinho;

    Nenhuma IA foi usada para gerar código, todo código gerado é uma mistura de 
    meu+geeksForGeeks+bufferOverFLow+w3Schools;

    pensa tipo uma distribuicao de 80-20, ai voce decide pra quem atribuir cada valor;
*/

/*struct node_e:
 
    Definicao da struct dos nos da lista;
 
    _e no fim do nome significa que a struct foi
    feita para listas encadeadas;
 
    void* info: informacao armazenada em cada no da lista,
               o (tipo) de cada info pode variar de acordo
               com o uso da lista, já que por ser um ponteiro
               para void, ele armazena endereco de qualquer coisa;
 
    struct node_e* prox: ponteiro auto referenciado
                         que vai apontar para o proximo
                         no da lista;
 
*/
struct node_e {
    void* info;
    struct node_e* prox;
};
typedef struct node_e Node_e;

/*struct lista_e:
 
    Definicao da struct gerenciadora da lista;
 
    _e no fim do nome significa que a struct foi feita
    para listas encadeadas;
 
    size_t tam: quantidade de nos da lista;
 
    size_t data_type: quantidade de bytes que o tipo de dado da lista ocupa

        **uso do size_t: no tam eu coloquei porque é bonito, no data_type eu
                         coloquei porque eu preciso armazenar a quantidade de
                         bytes que o tipo de dado da lista ocupa na memoria;
 
    Node_e* head: ponteiro para o no inicial da lista;
 
    Node_e* tail: ponteiro para o no final da lista;
 
    Tipo assim, a vantagem de usar a struct gerenciadora
    é que operacoes como inserir no inicio ou o final vao
    ser O(1) agora, e qualquer funcao que faca alteracao no
    corpo da lista nao vai precisar retornar alguma coisa mais,
    porque a alteracao vai ser na struct gerenciadora, e o
    ponteiro pra essa struct nao precisa saber disso;

*/
struct lista_e {
    size_t tam;
    size_t data_type;

    Node_e* head;
    Node_e* tail;
};
typedef struct lista_e Lista_e;

/*typedef int (*Comparador)(const void* a, const void* b):

    define Comparador como sendo um tipo de ponteiro para funcao que
    recebe dois ponteiros para void e retorna um int;

    isso aqui foi mais pra limpar a sintaxe dos headers das funcoes
    que fazem uso desse ponteiro para uma funcao de comparacao, ja 
    que a sintaxe de ponteiro pra funcao em C é podre;

*/
typedef int (*Comparador)(const void* a, const void* b);

/*Lista_e* criaL(size_t type):

    Cria uma struct gerenciadora para lista;

    Retorna a lista ou NULL para falha;

    Lista_e* n...: cria um ponteiro para struct gerenciadora e
                   aloca uma struct gerenciadora;

    if (lista==NULL){...}: testa o sucesso da alocacao;

    lista->data_type = data_size: armazena o valor em bytes do tipo de 
                                  dado que a lista vai armazenar; 

    lista->tam = 0x0: define o tamanho inicial da lista;

    lista->head = NULL: por nao ter elementos, o ponteiro head e null;

    lista->tail = NULL: mesma coisa do lista->head;

*/
Lista_e* criaL(size_t);

/*L_Status insereIL(Lista_e* lista, const void* valor):
    Insere um no no inicio da lista;

    Retorna:
        L_NULL_PTR -> ponteiro da lista nulo;
        L_MEM_ERR -> erro na alocacao de memoria;
        L_SUCCESS -> sucesso
 
    Node_e* node...: cria um ponteiro para um no
                     e aloca um no;

    if (node==NULL) {...}: testa o sucesso da alocacao;

    node->info = (lista->data_type*)malloc(sizeof(lista->data_type)):

            aloca um bloco de memoria do tamanho do dado que sera armazenado 
            na lista para que o ponteiro do no tenha sua propria copia do 
            valor passado pelo usuario;

    if (node->info==NULL) {...}: testa o sucesso da alocacao do ponteiro info;

    memcpy(node->info, valor, lista->data_type):

            copia os bytes do valor passado como argumento da funcao para o 
            ponteiro para a informacao que esta dentro do no. Isso faz com 
            que uma copia do valor passado pela funcao seja criada dentro da 
            lista. Assim, qualquer alteracao que o usuario fizer na variavel 
            fora desta funcao, nao tera efeito no valor do no criado agora.

            resumindo todo o processo: aloca um bloco de memoria para o ponteiro
                                       node->info e copia o valor que sera aqui
                                       armazenado da variavel (valor) passada 
                                       como argumento dessa funcao. Mesmo assim,
                                       na hora de imprimir (exemplo) o valor que
                                       esta armazenado no no, o usuario tera que usar
                                       um casting explicito para indicar qual tipo de 
                                       dado sera impresso, ja que o ponteiro para a
                                       informacao do no é um ponteiro para void;

    node->prox = lista->head: ja que o novo no inserido sera o head da lista, o antigo
                              head da lista sera apontado pelo ponteiro prox do novo no;

    lista->head = node: define o novo no como o head da lista;

    if (lista->tam==0x0){...}: caso a lista esteja vazia, o novo no sera o tail da lista;

    lista->tam = lista->tam + 0x1: incrementa o tamanho da lista em 1;
*/
L_Status insereIL(Lista_e*, const void*);

/*L_Status insereFL(Lista_e* lista, const void* valor):
 
    Insere um novo no fim da lista;

    Retorna:
        L_NULL_PTR -> ponteiro da lista nulo;
        L_MEM_ERR -> erro na alocacao de memoria;
        L_SUCCESS -> sucesso
 
    Node_e* node...: cria um ponteiro para um no e
                     aloca um no;

    if (node==NULL) {...}: testa o sucesso da alocacao;

    node->info = malloc(lista->data_type): mesma coisa que o insereIL();

    if (node->info==NULL) {...}: testa o sucesso da alocacao do ponteiro node->info;

    memcpy(node->info, valor, lista->data_type): mesma coisa que o insereIL();

    if (lista->tam==0x0) {...}: caso a lista for vazia, o novo no sera o head;

                                else{...}: caso nao, o novo no sera apontado pelo 
                                           antigo tail;

    lista->tam = lista->tam + 0x1: incrementa o tamanho da lista em 1;
*/
L_Status insereFL(Lista_e*, const void*);

/*L_Status insereOL(Lista_e* lista, const void* valor, Comparador cmp):

    Insere um no de forma ordenada na lista;

    Retorna:
        L_NULL_PTR -> ponteiro da lista nulo;
        L_MEM_ERR -> erro na alocacao de memoria;
        L_SUCCESS -> sucesso
 
    A funcao espera que a lista esteja ordenada,
    senao, o comportamento sera indefinido;

    cmp:

        (*Comparador)(const void* a, const void* b);

        cmp nada mais é que um ponteiro para um funcao de comparacao, 
        de escolha do usuario. Pesquise sobre a funcao qsort() da stdlib
        caso queira saber um pouco sobre como isso funciona com uma funcao
        de um lib padrao.

    Node_e* node...: aloca um novo no;

    if (node==NULL){...}: testa o sucesso da alocacao de memoria;

    agora é a parte que é a mesma coisa que nas outras funcoes de insercao;

    while (curr!=NULL && cmp(node->info, curr->info) > 0){...}: Caminha pela lista até que ache o local
                                                                exato para colocar o novo no;
 
    if (aux==NULL){...}: Caso aux seja NULL, quer dizer que o loop nao caminhou nenhuma vez,
                         entao ou o valor a ser inserido é o menor, ou a lista ta vazia. Nas
                         duas possibilidades, o novo no vai ser o novo head da lista;
 
                         else: Aqui significa que entrou no loop, entao tem um elemento da lista
                               que vem antes do valor novo;
 
    node->prox = curr: conecta o novo no inserido ao proximo no da lista, ou seja, o no que armazena
                       um valor maior que o novo no;

    if (curr==NULL){...}: Caso curr seja NULL, quer dizer que ou o loop nao caminhou nenhuma vez,
                          ou ele caminhou ate chegar no fim da lista. Na primeira opcao, a lista
                          ta vazia, na segunda opcao, o valor a ser inserido e o maior. Nas duas
                          possibilidades, o novo no vai ser o novo tail da lista;
 
    lista->tam = lista->tam + 0x1: incrementa o tamanho da lista em 1;
 
*/
L_Status insereOL(Lista_e*, const void*, Comparador);

/*L_Status inserePL(Lista_e* lista, const void* valor, size_t p):
 
    Insere um novo numa posicao personalizada;

    Retorna:
        L_NULL_PTR -> ponteiro da lista nulo;
        L_MEM_ERR -> erro na alocacao de memoria;
        L_SUCCESS -> sucesso

    Node_e* node...: aloca um novo no na memoria;
 
    if (node==NULL){...}: testa o sucesso da alocacao de memoria;
 
    if (lista->tam==0){...}: caso a lista esteja vazia, o novo
                             no inserido vai ser tanto o tail
                             quanto o head da lista;
 
    else if (p==0) {...}: caso o novo no for inserido na
                          primeira posicao, ele vai ser o
                          novo head da lista;
 
    else if (p>=(lista->tam)){...}: caso a posicao do novo no
                                    seja maior ou igual ao tamanho
                                    da lista, quer dizer que o novo
                                    no vai ser o tail da lista, ou seja,
                                    o ultimo no;
 
    else{...}: aqui significa que o novo no vai ser inserido no meio da
               lista, para isso, um loop while caminha ate achar o no anterior
               ao da posicao do novo no;
 
    lista->tam = lista->tam + 0x1: incrementa o tamanho da lista em 1;
 
*/
L_Status inserePL(Lista_e*, const void*, size_t);

/*L_Status rmIL(Lista_e* lista):

    Remove o primeiro no de uma lista;

    Retorna:
        L_NULL_PTR -> ponteiro da lista nulo;
        L_EMPTY -> lista vazia;
        L_SUCCESS -> sucesso;

    if (list->tam==0x0) {...}: testa se a lista ta vazia;

    lista->head = lista->head->prox: avanca o head da lista para o proximo elemento;
                                     caso a lista tenha apenas um no, o head ficara
                                     NULL;

    if (lista->head==NULL): se o head virar NULL, quer dizer que o unico elemento da lista
                            sera excluido, o que significa que o tail tem que virar NULL tambem;

    free(aux->info): libera a memoria do ponteiro info;

    free(aux): libera a memoria do no;

    lista->tam = lista->tam - 0x1: decrementa o tamanho da lista em 1;

*/
L_Status rmIL(Lista_e*);

/*L_Status rmUL(Lista_e* lista):

    Remove o ultimo no de uma lista;

    Retorna:
        L_NULL_PTR -> ponteiro da lista nulo;
        L_EMPTY -> lista vazia;
        L_SUCCESS -> sucesso;

    if (lista->tam==0x0) {...}: testa se a lista ta vazia;

    if (lista->head==lista->tail) {...}: caso a lista tenha apenas um elemento;

    else {...}: caso a lista tenha 2+ elementos (nos), é necessario que um ponteiro
                auxiliar caminhe até o penultimo elemento da lista, este que sera
                transformado no tail, depois que o atual tail da lista for liberado;

    lista->tam = lista->tam - 0x1: decrementa o tamanho da lista em 1;

*/
L_Status rmUL(Lista_e*);

/*L_Status rmPL(Lista_e* lista, const size_t p):
 
    Remove um no na posicao especificada;
 
    Retorna:
        L_NULL_PTR -> ponteiro da lista nulo;
        L_EMPTY -> lista vazia;
        L_INV_POS -> posicao invalida;
        L_SUCCESS -> sucesso;
 
    if (lista->tam==0x0){...}: testa se a lista ta vazia;
 
    if (p>=lista->tam){...}: testa se a posicao passada e invalida, nao é necessario
                             testar para posicao negativa por causa do tipo de dado
                             (size_t);

    for (int i = 0; i < p; i++){...}: caminha pela lista ate que o ponteiro
                                      aux aponte para o no anterior ao que vai
                                      ser excluido e curr aponte para
                                      o no que vai ser excluido;
 
    if (aux==NULL){...}: caso aux seja NULL, quer dizer que o loop nao foi
                         ativado nenhuma vez, entao a posicao a ser excluida
                         e a primeira, entao o atual segundo no da lista vira
                         o head, isso serve tambem pra caso a lista tenha apenas
                         um no, porque curr->prox vai ser NULL nesse caso.
 
                         if (curr->prox==NULL){...}: aqui ele continua o teste se
                                                     a lista tem apenas um elemento,
                                                     caso sim, ele aponta lista->tail para
                                                     NULL;
 
    else{...}: aqui cobre o caso do no a ser excluido estar no meio da lista, ou na ultima
               posicao.
 
               if (curr->prox==NULL){...}: caso o no a ser excluido seja o ultimo, ele aponta
                                           lista->tail para aux, que como ja foi dito, vai ser
                                           o no anterior ao que sera excluido;

    free(curr->info): libera a memoria do ponteiro info do no a ser excluido;
 
    free(curr): libera memoria do no excluido;
 
    lista->tam = lista->tam - 0x1: decrementa o tamanho da lista em 1;
 
*/
L_Status rmPL(Lista_e*, const size_t);

/*size_t rmVL(Lista_e* lista, const void* valor, Comparador cmp, L_Status* flag):
 
    Remove todos os nos do valor passado como argumento;
 
    Retorna a quantidade de nos retirados.
    Caso a flag nao seja NULL, o status da operacao sera informado;

    Possiveis flags:
        L_NULL_PTR -> ponteiro nulo;
        L_EMPTY -> lista vazia;
        L_SUCCESS -> sucesso;
 
    if (lista->tam==0){...}: testa se a lista ta vazia;
 
    while (lista->head!=NULL && cmp(lista->head->info, valor)==0){...}: esse while caminha na lista enquanto o primeiro elemento
                                                                        for igual ao valor que sera retirado e enquanto a lista
                                                                        tiver elementos. Isso ajuda demais porque agora nao e
                                                                        necessario tratar de todos os casos em que o no a ser
                                                                        retirado e o primeiro. Quando esse loop acabar, ou a lista
                                                                        vai estar vazia, ou o primeiro elemento nao vai ter que ser
                                                                        retirado;
 
    if (lista->head==NULL){...}: testa caso a lista termine o primeiro loop vazia. Se isso for o caso, o ponteiro
                                 tail da lista precisa se atualizado pra NULL tambem;
 
                             else {...}: Faz com que aux aponte para o primeiro elemento, e curr aponte para o
                                         elemento apos o lista->head. Isso funciona porque a gente ja sabe que se a
                                         lista nao ta vazia depois do primeiro loop, isso quer dizer que o atual
                                         head da lista nao tem o valor que a gente quer remover, entao e seguro
                                         pular pro segundo. Mesmo num cenario de uma lista com um elemento so,
                                         curr apontaria pra NULL, e nao chegaria nem a entrar no segundo loop;
 
    while (curr){...}: loop que caminha pela lista em busca de elementos que contenham o valor a ser removido;
 
                       if (cmp(curr->info, valor)==0){...}: Testa caso o elemento atual contenha o valor a ser 
                                                            removido;
 
                                                if (curr==lista->tail): Se o elemento atual for o ultimo elemento
                                                                        da lista (tail), isso quer dizer que o no
                                                                        anterior, atualmente sendo apontado por aux,
                                                                        tem que ser o novo tail;
 
                                                aux->prox = curr->prox: o no apontado por aux agora foi ligado
                                                                        ao no posterior a curr, reconectando a
                                                                        lista para que curr possa ser removido;
 
                                                free(curr->info): libera a memoria do ponteiro info;

                                                free(curr): libera o no curr;
 
                                                curr = aux->prox: Reatribui um valor a curr, porque atualmente
                                                ele nao aponta pra nenhum no, ja que foi liberado. Nesse caso,
                                                ele tem que apontar para o elemento apos aux, porque aux sempre
                                                aponta para um no que ja foi testado;
 
                                                ++count: incrementa a quantidade de elementos removidos;
 
                        else {...}: avanca para o proximo elemento, salvando o atual em aux;
 
    lista->tam = lista->tam - count: decrementa a quantidade total de elementos da lista;
*/
size_t rmVL(Lista_e*, const void*, Comparador, L_Status*);

/*size_t rmFL(Lista_e* lista, const void* valor, Comparador cmp, L_Status* flag):
 
    Remove o primeiro no que contenha o valor passado como argumento;
 
    Retorna a posicao que foi removida em caso de sucesso, e 0 para falha;
    É Recomendado usar a flag aqui nessa funcao, porque o 0 como falha pode confundir,
    ja que ele é uma posicao valida da lista;

    Possiveis flags:
        L_NULL_PTR -> ponteiro nulo;
        L_EMPTY -> lista vazia;
        L_VAL_NOT_FOUND -> valor nao encontrado;
        L_SUCCESS -> sucesso;
 
    if (lista->tam==0x0){...}: testa se a lista ta vazia;
 
    if (cmp(lista->head->info, valor)==0x0){...}: testa se o elemento procurado e o head da lista.
 
                                if (lista->head==NULL){...}: Testa se a lista tem apenas
                                                             o elemento que vai ser retirado,
                                                             caso sim, faz com que tail aponte
                                                             para NULL;
 
    aux = lista->head, curr = lista->head->prox: Faz com que aux aponte para o atual head, que
                                                 ja sabemos que nao e o elemento procurado, tambem
                                                 faz com que curr aponte para o segundo elemento da
                                                 lista;
 
    p++: incrementa a posicao que vai ser retornada;
 
    while (curr){...}: Loop que caminha pela lista procurando pelo valor que sera retirado.
                       Se o valor for encontrado, conecta o elemento antecessor do atual ao
                       sucessor do atual, assim se torna possivel liberar o no desejado.
                       Testa se o no encontrado e o ultimo, caso sim, faz com que lista->tail
                       aponte para aux, o antecessor do atual. Libera o no com o valor desejado
                       e decrementa o valor da lista, depois disso, retorna a posicao encontrada;
 
    obs: eu nao especifiquei muito a explicacao desse funcao porque ela e muito parecida com
         a anterior (rmVL) que foi escrita uma constituicao inteira so pra explicar aquela coisa;
*/
size_t rmFL(Lista_e*, const void*, Comparador, L_Status*);

/*size_t searchL(const Lista_e* lista, const void* valor, Comparador cmp, L_Status* flag):
 
    Busca por um valor na lista;
 
    Retorna a posicao do no na lista ou 0 para falha;
    cuidado ao usar sem flag, por causa do 0 como falha pode confundir;
    
    Possiveis flags:
        L_NULL_PTR -> ponteiro nulo;
        L_EMPTY -> lista vazia;
        L_VAL_NOT_FOUND -> valor nao encontrado;
        L_SUCCESS -> sucesso;
 
    if (lista->tam==0){...}: testa se a lista ta vazia;
 
    if (cmp(lista->tail->info, valor)==0x0){...}: testa se o valor procurado
                                                  ta na ultima posicao, isso
                                                  salva um bom tempo quando
                                                  a lista é muito grande;
 
    while (curr->prox){...}: Caminha pela lista ate que
                             que chegue no ultimo elemento,
                             quando acha o elemento, retorna
                             a posicao. Esse loop nao vai ate
                             que curr seja NULL porque nao e
                             necessario testar a ultima posicao
                             de novo, uma vez que ela foi testada
                             antes do loop;

*/
size_t searchL(const Lista_e*, const void*, Comparador, L_Status*);

/*void* getNodeValL(Lista_e* lista, const size_t p, L_Status* flag):

    Retorna o endereco de memoria do valor armazenado no nó que
    se encontra na posicao passada como argumento, ou NULL em 
    caso de algum erro / valor nao encontrado;

    Possiveis flags: 
        L_NULL_PTR -> ponteiro nulo;
        L_INV_POS -> posicao invalida;
        L_SUCCESS -> sucesso;

    if (lista==NULL) {...}: testa se o ponteiro da lista é nulo;

    if (p>=lista->tam) {...}: testa se a posicao passada como argumento é valida,
                              esse teste tambem cobre caso a posicao seja negativa,
                              ja que o tipo de dado é size_t, significando que no
                              caso de uma posicao negativa, o valor seria automaticamente
                              transformado no maior valor possivel de um size_t, o que 
                              implicaria no teste verdadeiro;

    if (p==lista->tam-1) {...}: caso a posicao seja a ultima da lista;

    for (size_t i = 0; i < p; i++) {...}: caminha pela lista até parar no nó da posicao desejada;

*/
void* getNodeValL(const Lista_e*, const size_t, L_Status*);

/*size_t sizeL(const Lista_e*, L_Status* flag):

    retorna o número de nós da lista atualmente;

    Possiveis flags:
        L_NULL_PTR -> ponteiro nulo;
        L_SUCCESS -> sucesso;

*/
size_t sizeL(const Lista_e*, L_Status*);

/*bool taVaziaL(const Lista_e*, L_Status* flag):

    retorna true para lista vazia ou ponteiro nulo(!!!!) e false para o contrario;

    outra funcao que é bom usar a flag, ja que é unica maneira de saber diferenciar
    se a lista ta vazia mas existe ou se ela nem foi alocada ainda;

    Possiveis flags:
        L_NULL_PTR -> ponteiro nulo;
        L_SUCCESS -> sucesso;

*/
bool taVaziaL(const Lista_e*, L_Status*);

/*L_Status limpaL(Lista_e*):

    remove todos os nós da lista, mas a mantém na memória;

    Possiveis flags de retorno:
        L_NULL_PTR -> ponteiro nulo;
        L_EMPTY -> lista vazia;
        L_SUCCESS -> sucesso;

*/
L_Status limpaL(Lista_e*);

/*L_Status killL(Lista_e* l):
 
    elimina a lista;

    Possiveis flags de retorno:
        L_NULL_PTR -> ponteiro nulo;
        L_SUCCESS -> sucesso;
 
*/
L_Status killL(Lista_e*);

#endif // LISTA_ENCAD_H
