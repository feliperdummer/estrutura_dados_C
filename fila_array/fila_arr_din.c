#include <stdio.h>
#include <stdlib.h>

#include "fila_arr_din.h"


/*criaFa(void):
*
*   Aloca, iniciliza e retorna uma nova estrutura do tipo Fila_a;
*
*   _a no fim significa que a fila utiliza array dinamico na implementacao
*
*   Fila_a* f = malloc(sizeof(Fila_a)): Primeiro aloca uma nova estrutura do tipo Fila_a;
*
*   f->pa = malloc(sizeof(int)): Agora aloca um array de tamanho dentro da estrutura;
*
*   f->tam = 1: Inicializa o tamanho do array em 1;
*
*   f->ini = 0: O primeiro elemento da fila, quando vazia, fica no indice 0;
*
*   f->fim = 0: O ultimo elemento segue a mesma regra do primeiro quando a fila ta vazia;
*
*   f->pre = 0: Inicializa a quantidade de elementos preenchidos em 0;
*
*/
Fila_a* criaFa(void) {
    Fila_a* f = malloc(sizeof(Fila_a));
    if (f==NULL) return NULL;
    f->pa = malloc(sizeof(int));
    if (f->pa==NULL) return NULL;
    f->tam = 1;
    f->ini = 0;
    f->fim = 0;
    f->pre = 0;
    return f;
}

/*taVaziaFa(Fila_a* f):
*
*   A funcao espera que a fila ja esteja inicilizada, caso contrario,
*   o comportamento e inesperado;
*
*   Retorna se a fila ta vazia;
*
*/
_Bool taVaziaFa(Fila_a* f) {
    return f->pre==0;
}

/*taCheiaFa(Fila_a* f):
*
*   A funcao espera que a fila ja esteja inicilizada, caso contrario,
*   o comportamento e inesperado;
*
*   Retorna se a fila ta cheia;
*
*/
_Bool taCheiaFa(Fila_a* f) {
    return f->pre==f->tam;
}

/*tamanhoFa(Fila_a* f, const int flag):
*
*   Retorna o tamanho da fila, com duas opcoes;
*
*   'f': Retorna a quantidade de elementos do array que ja foram preenchidos;
*
*   't': Retorna o tamanho total do vetor de elementos;
*
*/
int tamanhoFa(Fila_a* f, const int flag) {
    switch (flag) {
        case 'f':
            return f->pre;
        case 't':
            return f->tam;
        default:
            printf("erro: flag invalida (t -> total | f -> preenchido)\n");
            return -1;
    }
}

/*enqueueFa(Fila_a* f, const int v):
*
*   Insere um novo valor no fim da fila;
*
*   if (taCheiaFa(f)){...}: Caso a fila esteja cheia, chama a funcao
*                           alinhaFilaFa(), que exerce o trabalho de
*                           alocar um novo bloco de memoria com o dobro
*                           do tamanho, alinha os elementos de volta na
*                           fila, atualiza o indice de inicio e o de fim,
*                           atualiza o tamanho da fila, descarta o array
*                           antigo e por ultimo, aponta o novo array para
*                           o ponteiro da fila;
*
*   f->pa[f->fim] = v: Insere o novo elemento no proximo elemento disponivel da fila;
*
*   f->fim = (f->fim+1) % f->tam: Calcula qual sera o proximo elemento disponivel para
*                                 insercao da fila. Isso garante o funcionamento circular
*                                 da fila;
*
*   f->pre++: Incrementa a variavel que armazena a quantidade de elemento preenchidos do vetor;
*
*/
void enqueueFa(Fila_a* f, const int v) {
    if (taCheiaFa(f)) alinhaFilaFa(f);
    f->pa[f->fim] = v;
    f->fim = (f->fim+1) % f->tam;
    f->pre++;
}

/*alinhaFilaFa(Fila_a* f):
*
*   Aloca um novo vetor para a fila, assim como o alinha;
*
*   Alinhar o novo vetor alocado e necessario porque
*   a fila pode estar fragmentada, ou seja, o primeiro
*   elemento da fila nao necessariamente ocupa o primeiro
*   indice do array, e o ultimo elemento da fila nao
*   necessariamente ocupa o ultimo indice da array;
*
*   Essa funcao tem a unica especialidade de organizar um
*   novo vetor pra fila caso o antigo seja preenchido por
*   completo, e como essa implementacao de fila usa um
*   array dinamicamente alocado, toda vez que a fila chega
*   no seu limite, o tamanho do array e dobrado;
*
*   Resumindo, ela aloca um novo array com o dobro do tamanho
*   do antigo, e organiza os elementos da fila de forma que
*   estes fiquem alinhados no novo array, mantendo assim a
*   forma circular da fila;
*
*   int lim = f->pre: Recebe o numero de elementos que ja
*                     foram preenchidos do vetor da fila.
*                     Vai ser o ponto de parada pra copiar
*                     os elementos pro novo vetor;
*
*   int* n = malloc(f->tam*2 * sizeof(int)): Aloca um novo vetor com o dobro do tamanho do atual.
*                                            Lembrando que o tamanho da fila em si ainda nao foi
*                                            atualizado;
*
*   for (i = 0; i < lim; i++){...}: Anda pelo novo vetor, a partir do primeiro elemento, copiando
*                                   os elementos que estao no vetor antigo a partir do elemento
*                                   que esta em primeiro na fila (f->ini). Essa abordagem funciona
*                                   mesmo se a fila estiver fragmentada antes da realocacao, porque
*                                   o calculo do indice ini ((f->ini+1) % f->tam) garante que os
*                                   elementos sao copiados de forma continua, sem nenhum "furar a fila";
*
*   f->ini = 0: Agora que os elementos ja foram devidamente alocados no novo vetor, o novo indice do primeiro
*               elemento volta a ser 0;
*
*   f->fim: O novo valor de f->fim vai ser i, porque no fim do loop, a variavel i avanca uma casa depois do
*           ultimo elemento preenchido, o que nos da de bandeja o indice do proximo elemento disponivel para
*           insercao na fila;
*
*   free(f->pa): Libera a memoria do vetor antigo;
*
*   f->pa = n: O ponteiro do vetor da fila agora aponta para o vetor novo;
*
*   f->tam *= 2: Agora sim atualiza o tamanho do vetor da fila, que passa a ser o dobro do que era;
*
*/
void alinhaFilaFa(Fila_a* f) {
    int i = 0;
    int lim = f->pre;
    int* n = malloc(f->tam*2 * sizeof(int));

    if (n==NULL) return;
    for (i = 0; i < lim; i++) {
        n[i] = f->pa[f->ini];
        f->ini = (f->ini+1) % f->tam;
    }
    f->ini = 0;
    f->fim = i;
    free(f->pa);
    f->pa = n;
    f->tam *= 2;
}

/*dequeueFa(Fila_a* f, int* flag):
*
*   Retorna o elemento que ocupa o inicio da fila;
*
*   A flag so serve pra sinalizar se alguma coisa deu errado,
*   ja que qualquer valor retornado ai pode ser um valor que
*   existe dentro da fila;
*
*   if(taVaziaFa(f)){...}: Testa se a fila ta vazia;
*
*   else{...}:
*
*               r = f->pa[f->ini]: Salva o primeiro elemento da fila na variavel r;
*
*               f->ini = (f->ini+1) % f->tam: Calcula qual sera o indice do primeiro
*                                             elemento da fila de forma que a circularidade
*                                             da fila se mantenha;
*
*               f->pre--: Decrementa a variavel que armazena a quantidade de elementos que
*                         foram preenchidos no vetor da fila;
*
*               *flag = 0: Sinaliza a flag com 0, pra indicar sucesso;
*
*/
int dequeueFa(Fila_a* f, int* flag) {
    int r = 0;
    if(taVaziaFa(f)) *flag = -1;
    else {
        r = f->pa[f->ini];
        f->ini = (f->ini+1) % f->tam;
        f->pre--;
        *flag = 0;
    }
    return r;
}

