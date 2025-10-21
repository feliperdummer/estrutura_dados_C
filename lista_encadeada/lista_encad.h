#ifndef LISTA_ENCAD_H
#define LISTA_ENCAD_H

/*struct node_e:
*
*   Definicao da struct dos nos da lista;
*
*   _e no fim do nome significa que a struct foi
*   feita para listas encadeadas;
*
*   type info: informacao armazenada em cada no da lista,
*              o (type) de cada info pode variar de acordo
*              com o uso da lista, aqui foi usado int;
*
*   struct node_e* prox: ponteiro auto referenciado
*                        que vai apontar para o proximo
*                        no da lista;
*
*/
struct node_e {
    int info;
    struct node_e* prox;
};
typedef struct node_e Node_e;

/*struct lista_e:
*
*   Definicao da struct gerenciadora da lista;
*
*   _e no fim do nome significa que a struct foi feita
*   para listas encadeadas;
*
*   int tam: tamanho da lista;
*
*   Node_e* head: ponteiro para o no inicial da lista;
*
*   Node_e* tail: ponteiro para o no final da lista;
*
*   Tipo assim, a vantagem de usar a struct gerenciadora
*   é que operacoes como inserir no inicio ou o final vao
*   ser O(1) agora, e qualquer funcao que faca alteracao no
*   corpo da lista nao vai precisar retornar alguma coisa mais,
*   porque a alteracao vai ser na struct gerenciadora, e o
*   ponteiro pra essa struct nao precisa saber disso;
*
*/
struct lista_e {
    int tam;
    Node_e* head;
    Node_e* tail;
};
typedef struct lista_e Lista_e;

Lista_e* criaL(void);
Lista_e* buildEA(int*, const int);
void insereIL(Lista_e*, const int);
void insereFL(Lista_e*, const int);
void insereOL(Lista_e*, const int);
void inserePL(Lista_e*, const int, int);
int rmPL(Lista_e*, const int);
int rmVL(Lista_e*, const int);
int rmFL(Lista_e*, const int);
int searchL(Lista_e*, const int);
void killL(Lista_e*);

#endif // LISTA_ENCAD_H


