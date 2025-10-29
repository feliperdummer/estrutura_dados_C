#ifndef FILA_ARR_DIN_H
#define FILA_ARR_DIN_H

/*struct fila_a:
*
*   Definicao da struct para a fila com array dinamico;
*
*   o _a no nome signfica que a fila vai usar array na implementacao;
*
*   int ini: Posicao do proximo elemento a ser retirado da fila;
*
*   int fim: Posicao que sera inserido o proximo elemento da fila;
*
*   int *pa: Ponteiro para o array dinamico;
*
*   int tam: Tamanho do array alocado;
*
*   int pre: Numero de elementos totais preenchidos;
*
*/
struct fila_a {
    int ini;
    int fim;
    int *pa;
    int tam;
    int pre;
};
typedef struct fila_a Fila_a;

Fila_a* criaFa(void);
void enqueueFa(Fila_a*, const int);
void alinhaFilaFa(Fila_a*);
int dequeueFa(Fila_a*, int*);
_Bool taVaziaFa(Fila_a*);
_Bool taCheiaFa(Fila_a*);
int tamanhoFa(Fila_a*, const int);
void killFa(Fila_a*);

#endif // FILA_ARR_DIN_H
