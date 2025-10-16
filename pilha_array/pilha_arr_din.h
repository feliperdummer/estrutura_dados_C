#ifndef PILHA_ARR_DIN
#define PILHA_ARR_DIN

/*struct pilha:
*
*   int top -> Representa o indice do elemento que está no topo da lista;
*              Assume valor -1 quando a lista está vazia;
*
*   type *pa -> Representa o ponteiro para o array dinamicamente alocado;
*              O tipo (type) é relativo ao uso da lista, pode ser short, int, long, float, double, ou qualquer outro que se encaixe;
*
*   int tam -> Representa o tamanho atual da pilha;
*/
struct pilha {
    int top;
    int *pa;
    int tam;
};
typedef struct pilha Pilha;

// funcoes padrao
Pilha* cria(void);
_Bool taVazia(Pilha*);
_Bool taCheia(Pilha*);
int tamanho(Pilha*, const int);
void push(Pilha*, const int);
int pop(Pilha*);
int peek(Pilha*);
void sKill(Pilha*);

// funcoes utilitarias
void copiarPilha(Pilha*, Pilha*, int*);
void transferirElementos(Pilha*, Pilha*);

void inverter(Pilha*);
void insereFundo(Pilha*, const int);

int comparaPilhaRec(Pilha*, Pilha*);
int comparaPilhaItr(Pilha*, Pilha*);

#endif // PILHA_ARR_DIN

