#ifndef LISTA_DUP_ENCAD_H
#define LISTA_DUP_ENCAD_H

/*struct node_e:
*
*   Definicao da struct dos nos da lista;
*
*   _d no fim do nome significa que a struct foi
*   feita para listas duplamente encadeadas;
*
*   type info: informacao armazenada em cada no da lista,
*              o (type) de cada info pode variar de acordo
*              com o uso da lista, aqui foi usado int;
*
*   struct node_d* prox: ponteiro auto referenciado
*                        que vai apontar para o proximo
*                        no da lista;
*
*   struct node_d* ant: ponteiro auto referenciado
*                       que vai apontar para o proximo
*                       no da lista;
*
*/
struct node_d {
    int info;
    struct node_d* prox;
    struct node_d* ant;
};
typedef struct node_d Node_d;

/*struct lista_d:
*
*   Definicao da struct gerenciadora da lista;
*
*   _d no fim do nome significa que a struct foi feita
*   para listas encadeadas;
*
*   int tam: tamanho da lista;
*
*   Node_d* head: ponteiro para o no inicial da lista;
*
*   Node_d* tail: ponteiro para o no final da lista;
*
*   Tipo assim, a vantagem de usar a struct gerenciadora
*   é que operacoes como inserir no inicio ou o final vao
*   ser O(1) agora, e qualquer funcao que faca alteracao no
*   corpo da lista nao vai precisar retornar alguma coisa mais,
*   porque a alteracao vai ser na struct gerenciadora, e o
*   ponteiro pra essa struct nao precisa saber disso;
*
*/
struct lista_d {
    int tam;
    Node_d* head;
    Node_d* tail;
};
typedef struct lista_d Lista_d;

Lista_d* criaLD(void);
void insereILD(Lista_d*, const int);
void insereFLD(Lista_d*, const int);
void insereOLD(Lista_d*, const int);
void inserePLD(Lista_d*, const int, int);
int rmPLD(Lista_d*, int);
int rmVLD(Lista_d*, const int);
int rmFLD(Lista_d*, const int);
int searchLD(Lista_d*, const int);
void killLD(Lista_d*);

#endif // LISTA_DUP_ENCAD_H
