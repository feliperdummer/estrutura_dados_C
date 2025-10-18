#ifndef PILHA_ARR_DIN
#define PILHA_ARR_DIN

/*struct pilha_a:
*
*   o _a significa que a struct foi feita para pilhas que usam vetores;
*
*   int top -> Representa o indice do elemento que está no topo da lista;
*              Assume valor -1 quando a lista está vazia;
*
*   type *pa -> Representa o ponteiro para o array dinamicamente alocado;
*              O tipo (type) é relativo ao uso da lista, pode ser short, int, long, float, double, ou qualquer outro que se encaixe;
*
*   int tam -> Representa o tamanho atual da pilha;
*/
struct pilha_a {
    int top;
    int *pa;
    int tam;
};
typedef struct pilha_a Pilha_a;

// funcoes padrao
Pilha_a* criaPa(void);
_Bool taVaziaPa(Pilha_a*);
_Bool taCheiaPa(Pilha_a*);
int tamanhoPa(Pilha_a*, const int);
void pushPa(Pilha_a*, const int);
int popPa(Pilha_a*);
int peekPa(Pilha_a*);
void KillPa(Pilha_a*);

// funcoes utilitarias
void copiarPilhaPa(Pilha_a*, Pilha_a*, int*);
void transferirElementosPa(Pilha_a*, Pilha_a*);

void inverterPa(Pilha_a*);
void insereFundoPa(Pilha_a*, const int);

int comparaPilhaRecPa(Pilha_a*, Pilha_a*);
int comparaPilhaItrPa(Pilha_a*, Pilha_a*);

#endif // PILHA_ARR_DIN

