#include "pilha_arr_din.h"
#include <stdio.h>
#include <stdlib.h>

/*
    autor: eu mesmo
*/

/*cria():
*
*   Pilha* n = (Pilha*)malloc(sizeof(Pilha)): Declara um ponteiro para o tipo Pilha e o
*              inicializa com uma estrutura do tipo pilha dinamicamente alocada;
*
*   n->top = -1: Atribui o valor -1 a variavel top da estrutura criada, indicando que
*                a pilha ta inicialmente vazia;
*
*   n->p = malloc(1 * sizeof(int)): inicializa o ponteiro da estrutura com um vetor
*          de 1 posicao inicial dinamicamente alocado;
*
*   return n: retorna o endereço de memoria da estrutura Pilha criada;
*/
Pilha* cria(void) {
    Pilha* n = (Pilha*)malloc(sizeof(Pilha));
    n->pa = malloc(1 * sizeof(int));
    if (n->pa==NULL) {
        printf("erro: falha na alocacao de memoria\n");
        return NULL;
    }
    n->top = -1;
    n->tam = 1;
    return n;
}

/*taVazia(Pilha* p):
*
*   return p->top==-1: retorna o valor logico da expressao:
*
*          0, quando a expressao e falsa;
*          !=0, quando a expressao e verdadeira;
*/
_Bool taVazia(Pilha* p) {
    return p->top==-1;
}

/*taCheia(Pilha* p):
*
*   return p->top==p->tam-1: retorna o valor logico da expressao:
*
*           0, quando a espressao e falsa;
*           !=0, quando a expressao e verdadeira;
*
*/
_Bool taCheia(Pilha* p) {
    return tamanho(p,'f')==tamanho(p,'t');
}

/*tamanho(Pilha* p):
*
*   Aceita duas flags como parametro:
*
*           f -> caso o desejo seja saber a quantidade de elementos da pilha ja preenchidos;
*           t -> caso o desejo seja saber o tamanho total da pilha;
*
*/
int tamanho(Pilha* p, const int opc) {
    switch(opc) {
        case 't':
            return p->tam;
        case 'f':
            return p->top + 1;
        default:
            printf("erro: flag invalida (t -> total | f -> preenchido)\n");
            return -1;
    }
}

/*push(Pilha* p, const int v):
*
*
*
*   if (taCheia(p)) {...}: Aqui testa se o vetor da pilha chegou no limite, caso sim,
*                          ele sempre vai dobrar o tamanho de elementos do atual (análise amortizada),
*                          entao caso a quant atual seja 1, vai realocar pra 2, e assim por diante.
*                          Depois disso, na linha p->tam = (tamanho(p, 't')*2), ele
*                          atualiza o tamanho do vetor com o novo valor.
*
*   p->pa[++p->top] = v: Incrementa a variavel t->top e atribui o valor ao elemento do topo;
*/
void push(Pilha* p, const int v) {
    if (p==NULL) {
        printf("erro: lista nao inicializada: funcao cria()\n");
        return;
    }
    if (taCheia(p)) {
        p->pa = realloc(p->pa, (tamanho(p, 't')*2)*sizeof(int));
        if (p->pa==NULL) {
            printf("erro: falha na realocacao de memoria\n");
            return;
        }
        p->tam = (tamanho(p, 't')*2);
    }
    p->pa[++p->top] = v;
}

/*pop(Pilha* p):
*
*   if (p==NULL), if(taVazia(p)): Testa se a pilha nao foi inicializada ou ta vazia;
*
*   return p->pa[p->top--]: retorna o elemento que ta no topo da pilha,
*                           logo após decrementa a variavel p->top;
*
*/
int pop(Pilha* p) {
    if (p==NULL) {
        printf("erro: lista nao inicializada: funcao cria()\n");
        return -1;
    }
    if (taVazia(p)) {
        printf("erro: lista vazia\n");
        return -1;
    }
    return p->pa[p->top--];
}

/*peek(Pilha* p):

    if (p==NULL), if(taVazia(p)): Testa se a pilha nao foi inicializada ou ta vazia;

    return p->pa[p->top]: retorna o elemento do topo da pilha;
*/
int peek(Pilha* p) {
    if (p==NULL) {
        printf("erro: lista nao inicializada: funcao cria()\n");
        return -1;
    }
    if (taVazia(p)) {
        printf("erro: lista vazia\n");
        return -1;
    }
    return p->pa[p->top];
}

/*sKill(Pilha* p):

    free(p->pa): libera o vetor alocado dianamicamente quando a pilha foi criada;

    free(p): libera a pilha da memoria;

*/
void sKill(Pilha* p) {
    free(p->pa);
    free(p);
}

/*copiarPilha(Pilha* src, Pilha* dst, int* flagErro):
*
*   Essa funcao foi feita pra gerenciar a funcao transferirElementos;
*   que copia os elementos de uma pilha para a outra;
*
*   if (src==NULL || dst==NULL): testa se alguma das pilhas nao foi inicializada;
*/
void copiarPilha(Pilha* src, Pilha* dst, int* flagErro) {
    if (src==NULL || dst==NULL) {
        *flagErro = 1;
        return;
    }
    transferirElementos(src, dst);
    *flagErro = 0;
}

/*transferirElementos(Pilha* p1, Pilha* p2):
*
*   if (taVazia(p1)): Caso base pra parar a recursa;
*
*   se chama recursivamente até que a lista p1 (source) esteja vazia,
*   a partir dai, ela "recoloca" os elementos na p1, mas ao mesmo
*   tempo os compartilhando com p2;
*
*/
void transferirElementos(Pilha* p1, Pilha* p2) {
    if(taVazia(p1))
        return;
    int aux = pop(p1);
    transferirElementos(p1, p2);
    push(p1, aux);
    push(p2, aux);
}

/*inverter(Pilha* p):
*
*   Essa funcao serve pra desmontar a pilha, elemento por elemento, fazendo
*   isso recursivamente;
*
*   Usa uma outra funcao auxiliar, insereFundo(), pra reposicionar o elemento
*   que acabou de ser retirado na primeira posicao da pilha, a invertendo;
*
*   if (p->top==0 || taVazia(p)): Casos base pra parar a recursividade, porque
*                                 se a pilha tem apenas um elemento (p->top==0),
*                                 quer dizerque automaticamente ela ja ta invertida.
*                                 taVazia(p) é um teste pra ver se a lista passada
*                                 como argumento ta vazia;
*
*
*/
void inverter(Pilha* p) {
    if (p->top==0 || taVazia(p))
        return;
    else {
        int aux = pop(p);
        inverter(p);
        insereFundo(p, aux);
    }
}

/*insereFundo(Pilha* p, const int v):
*
*   Insere o valor passado como argumento no fundo da pilha,
*   de forma recursiva;
*
*   if (taVazia(p)): Caso de base pra parar a recursao, ai insere
*                    o valor passado como argumento recursivamente
*                    na primeira posicao da pilha;
*
*   As duas funcoes sao necessarias porque uma serve como um loop externo
*   que passa por toda a pilha (inverter()), a outra serve como um loop
*   interno que mexe com os elementos (insereFundo()). Pense nisso como
*   uma inversao de vetor, mas um pouco mais chata.
*
*/
void insereFundo(Pilha* p, const int v) {
    if (taVazia(p)) {
        push(p, v);
    }
    else {
        int aux = pop(p);
        insereFundo(p, v);
        push(p, aux);
    }
}

/*comparaPilhaRec(Pilha* p1, Pilha* p2):
*
*   retorna 1 pra sucesso e 0 pro oposto do sucesso;
*
*   Essa funcao usa recursividade só pra brincar, porque
*   a versao iterativa é bem melhor em geral;
*
*   if (taVazia(p1) && taVazia(p2)): Aqui é um teste que só é verdade se as duas pilhas estiverem vazias
*                                    ao mesmo tempo, o que indica que sao do mesmo tamanho, informacao
*                                    essencial pro resto da funcao;
*
*   if (taVazia(p1 || taVazia(p2)): Esse teste aqui é pra quando o primeiro de cima dá falso, o que abre
*                                   a possibilidade das pilhas terem tamanhos diferentes, o que seria
*                                   indicado caso uma estivesse vazia e outra nao, que é justamente o que
*                                   esse teste comprova. Outra informacao crucial pro resto da funcao;
*
*   int aux1 = pop(p1), aux2 = pop(p2): Salva o elemento do topo das duas funcoes;
*
*
*   int compTam = comparaPilhaRec(p1, p2): Chama a funcao recursivamente e armazena
*   o valor de retorno em uma variavel compTam, é basicamente o que decide se as duas
*   pilhas tem o mesmo tamanho.
*
*   if (compTam) {...}: Esse teste é feito porque mesmo se as duas funcoes tiverem o mesmo
*                       tamanho, nao significa que seus elementos sejam iguais. Isso e testado
*                       logo abaixo;
*
*/
int comparaPilhaRec(Pilha* p1, Pilha* p2) {
    if (taVazia(p1) && taVazia(p2))
        return 1;
    if (taVazia(p1) || taVazia(p2))
        return 0;
    int aux1 = pop(p1), aux2 = pop(p2);
    int compTam = comparaPilhaRec(p1, p2);
    push(p1, aux1);
    push(p2, aux2);
    if (compTam) {
        if (aux1==aux2)
            return 1;
        else
            return 0;
    }
    return 0;
}

/*comparaPilhaItr(Pilha* p1, Pilha* p2):
*
*   retorna 1 pra sucesso e 0 pro oposto do sucesso;
*
*   Aqui e a versao realmente util da funcao acima;
*
*   int* t_p1 = malloc(sizeof(int)): Aqui ele aloca um bloco de memoria pro vetor temporario
*                                    que vai servir como uma pilha auxiliar pra pilha p1.
*                                    A mesma coisa e feita com p2;
*
*   int t_tam = 1: Esse aqui vai ser o tamanho atual dos dois vetores, ele serve pros dois
*                  porque nao importa se as pilhas tem tamanho diferente, elas vao ser
*                  descascadas no mesmo tempo;
*
*   if (tam1!=tam2) {...}: testa se as duas PILHAS tem o mesmo tamanho. Lembrando, nao se trata
*                          do tamanho dos dois vetores, mas sim das duas pilhas;
*
*   while (!taVazia(p1) && !taVazia(p2)) {...}: Aqui e onde basicamente tudo acontece. Ele inicia
*                                               testando se uma das duas pilhas ta vazia.
*
*                                               if (i==t_tam) {...}: pra quando o indice que percorre
*                                               os vetores atingir o tamanho do vetor, o que indica que
*                                               ele precisa ter o tamanho incrementado, a tecnica usada pra
*                                               esse aumento foi sempre dobrar o tamanho do vetor, um bagulho
*                                               chamado análise amortizada, que pondera o custo de memória pelo
*                                               custo de tempo, e como o realloc normalmente e uma funcao que gasta
*                                               um tempinho pra ser concluida, usar o menos possivel e a melhor opcao;
*
*
*                                               if (peek(p1)!=peek(p2)) {...}: Testa se os topos atuais das listas sao
*                                               diferentes, caso sim, ele atribui 0 ao valor de retono da funcao, e quebra o loop;
*
*                                               t_p1[i] = pop(p1); t_p2[i] = pop(p2); i++: Aqui ele so retira o valor do topo
*                                               das duas pilhas depois de todos os testes e os armazena no vetor que funciona
*                                               como uma pilha auxiliar;
*
*   while (--i >= 0) {...}: Esse loop aqui so serve pra colocar os elementos
*                           retirados de cada pilha de volta nos seus lugares.
*                           Nao importa se o teste dos elementos dentro do loop
*                           while falhou e ele quebrou o loop, os elementos vao
*                           voltar de forma normal;
*
*
*/
int comparaPilhaItr(Pilha* p1, Pilha* p2) {
    int tam1 = tamanho(p1, 'f'), tam2 = tamanho(p2, 'f');
    int* t_p1 = malloc(sizeof(int));
    int* t_p2 = malloc(sizeof(int));
    int t_tam = 1;
    int i = 0, r = 1;

    if (tam1!=tam2)
        return 0;
    while (!taVazia(p1) && !taVazia(p2)) {
        if (i==t_tam) {
            t_p1 = realloc(t_p1, (t_tam*2)*sizeof(int));
            t_p2 = realloc(t_p2, (t_tam*2)*sizeof(int));
            t_tam *= 2;
        }
        if (peek(p1)!=peek(p2)) {
            r = 0;
            break;
        }
        t_p1[i] = pop(p1);
        t_p2[i] = pop(p2);
        i++;
    }
    while (--i >= 0) {
        push(p1, t_p1[i]);
        push(p2, t_p2[i]);
    }
    free(t_p1);
    free(t_p2);
    return r;
}
