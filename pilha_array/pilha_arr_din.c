#include "pilha_arr_din.h"
#include <stdio.h>
#include <stdlib.h>

/*
    autor: eu mesmo
*/

/*criaPa():
*
*   Pilha_a n = (Pilha_a*)malloc(sizeof(Pilha_a)): Declara um ponteiro para o tipo Pilha_a e o
*              inicializa com uma estrutura do tipo pilha dinamicamente alocada;
*
*   n->top = -1: Atribui o valor -1 a variavel top da estrutura criada, indicando que
*                a pilha ta inicialmente vazia;
*
*   n->p = malloc(1 * sizeof(int)): inicializa o ponteiro da estrutura com um vetor
*          de 1 posicao inicial dinamicamente alocado;
*
*   return n: retorna o endereço de memoria da estrutura Pilha_a criada;
*/
Pilha_a* criaPa(void) {
    Pilha_a* n = (Pilha_a*)malloc(sizeof(Pilha_a));
    n->pa = malloc(1 * sizeof(int));
    if (n->pa==NULL) {
        printf("erro: falha na alocacao de memoria\n");
        return NULL;
    }
    n->top = -1;
    n->tam = 1;
    return n;
}

/*taVaziaPa(Pilha_a* p):
*
*   return p->top==-1: retorna o valor logico da expressao:
*
*          0, quando a expressao e falsa;
*          !=0, quando a expressao e verdadeira;
*/
_Bool taVaziaPa(Pilha_a* p) {
    return p->top==-1;
}

/*taCheiaPa(Pilha_a* p):
*
*   return p->top==p->tam-1: retorna o valor logico da expressao:
*
*           0, quando a espressao e falsa;
*           !=0, quando a expressao e verdadeira;
*
*/
_Bool taCheiaPa(Pilha_a* p) {
    return tamanhoPa(p,'f')==tamanhoPa(p,'t');
}

/*tamanhoPa(Pilha_a* p):
*
*   Aceita duas flags como parametro:
*
*           f -> caso o desejo seja saber a quantidade de elementos da pilha ja preenchidos;
*           t -> caso o desejo seja saber o tamanho total da pilha;
*
*/
int tamanhoPa(Pilha_a* p, const int opc) {
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

/*pushPa(Pilha_a* p, const int v):
*
*
*
*   if (taCheiaPa(p)) {...}: Aqui testa se o vetor da pilha chegou no limite, caso sim,
*                            ele sempre vai dobrar o tamanho de elementos do atual (análise amortizada),
*                            entao caso a quant atual seja 1, vai realocar pra 2, e assim por diante.
*                            Depois disso, na linha p->tam = (tamanhoPa(p, 't')*2), ele
*                            atualiza o tamanho do vetor com o novo valor.
*
*   p->pa[++p->top] = v: Incrementa a variavel t->top e atribui o valor ao elemento do topo;
*/
void pushPa(Pilha_a* p, const int v) {
    if (p==NULL) {
        printf("erro: lista nao inicializada: funcao cria()\n");
        return;
    }
    if (taCheiaPa(p)) {
        p->pa = realloc(p->pa, (tamanhoPa(p, 't')*2)*sizeof(int));
        if (p->pa==NULL) {
            printf("erro: falha na realocacao de memoria\n");
            return;
        }
        p->tam = (tamanhoPa(p, 't')*2);
    }
    p->pa[++p->top] = v;
}

/*popPa(Pilha_a* p):
*
*   Fica de responsabilidade do usuario de passar uma pilha
*   que foi inicializada e que nao ta vazia. O programa pode
*   quebrar ou ter comportamento indefinido caso contrario;
*
*   return p->pa[p->top--]: retorna o elemento que ta no topo da pilha,
*                           logo após decrementa a variavel p->top;
*
*/
int popPa(Pilha_a* p) {
    return p->pa[p->top--];
}

/*peekPa(Pilha_a* p):
*
*   Fica de responsabilidade do usuario de passar uma pilha
*   que foi inicializada e que nao ta vazia. O programa pode
*   quebrar ou ter comportamento indefinido caso contrario;
*
*   return p->pa[p->top]: retorna o elemento do topo da pilha;
*/
int peekPa(Pilha_a* p) {
    return p->pa[p->top];
}

/*KillPa(Pilha_a* p):
*
*   free(p->pa): libera o vetor alocado dianamicamente quando a pilha foi criada;
*
*   free(p): libera a pilha da memoria;
*
*/
void KillPa(Pilha_a* p) {
    free(p->pa);
    free(p);
}

/*copiarPilhaPa(Pilha_a* src, Pilha_a* dst, int* flagErro):
*
*   Essa funcao foi feita pra gerenciar a funcao transferirElementos;
*   que copia os elementos de uma pilha para a outra;
*
*   if (src==NULL || dst==NULL): testa se alguma das pilhas nao foi inicializada;
*/
void copiarPilhaPa(Pilha_a* src, Pilha_a* dst, int* flagErro) {
    if (src==NULL || dst==NULL) {
        *flagErro = 1;
        return;
    }
    transferirElementosPa(src, dst);
    *flagErro = 0;
}

/*transferirElementosPa(Pilha_a* p1, Pilha_a* p2):
*
*   if (taVaziaPa(p1)): Caso base pra parar a recursa;
*
*   se chama recursivamente até que a lista p1 (source) esteja vazia,
*   a partir dai, ela "recoloca" os elementos na p1, mas ao mesmo
*   tempo os compartilhando com p2;
*
*/
void transferirElementosPa(Pilha_a* p1, Pilha_a* p2) {
    if(taVaziaPa(p1))
        return;
    int aux = popPa(p1);
    transferirElementosPa(p1, p2);
    pushPa(p1, aux);
    pushPa(p2, aux);
}

/*inverterPa(Pilha_a* p):
*
*   Essa funcao serve pra desmontar a pilha, elemento por elemento, fazendo
*   isso recursivamente;
*
*   Usa uma outra funcao auxiliar, insereFundo(), pra reposicionar o elemento
*   que acabou de ser retirado na primeira posicao da pilha, a invertendo;
*
*   if (p->top==0 || taVaziaPa(p)): Casos base pra parar a recursividade, porque
*                                 se a pilha tem apenas um elemento (p->top==0),
*                                 quer dizerque automaticamente ela ja ta invertida.
*                                 taVaziaPa(p) é um teste pra ver se a lista passada
*                                 como argumento ta vazia;
*
*
*/
void inverterPa(Pilha_a* p) {
    if (p->top==0 || taVaziaPa(p))
        return;
    else {
        int aux = popPa(p);
        inverterPa(p);
        insereFundoPa(p, aux);
    }
}

/*insereFundoPa(Pilha_a* p, const int v):
*
*   Insere o valor passado como argumento no fundo da pilha,
*   de forma recursiva;
*
*   if (taVaziaPa(p)): Caso de base pra parar a recursao, ai insere
*                      o valor passado como argumento recursivamente
*                      na primeira posicao da pilha;
*
*   As duas funcoes sao necessarias porque uma serve como um loop externo
*   que passa por toda a pilha (inverterPa()), a outra serve como um loop
*   interno que mexe com os elementos (insereFundoPa()). Pense nisso como
*   uma inversao de vetor, mas um pouco mais chata.
*
*/
void insereFundoPa(Pilha_a* p, const int v) {
    if (taVaziaPa(p)) {
        pushPa(p, v);
    }
    else {
        int aux = popPa(p);
        insereFundoPa(p, v);
        pushPa(p, aux);
    }
}

/*comparaPilhaRecPa(Pilha_a* p1, Pilha_a* p2):
*
*   retorna 1 pra sucesso e 0 pro oposto do sucesso;
*
*   Essa funcao usa recursividade só pra brincar, porque
*   a versao iterativa é bem melhor em geral;
*
*   if (taVaziaPa(p1) && taVaziaPa(p2)): Aqui é um teste que só é verdade se as duas pilhas estiverem vazias
*                                        ao mesmo tempo, o que indica que sao do mesmo tamanho, informacao
*                                        essencial pro resto da funcao;
*
*   if (taVaziaPa(p1) || taVaziaPa(p2)): Esse teste aqui é pra quando o primeiro de cima dá falso, o que abre
*                                        a possibilidade das pilhas terem tamanhos diferentes, o que seria
*                                        indicado caso uma estivesse vazia e outra nao, que é justamente o que
*                                        esse teste comprova. Outra informacao crucial pro resto da funcao;
*
*   int aux1 = popPa(p1), aux2 = popPa(p2): Salva o elemento do topo das duas funcoes;
*
*
*   int compTam = comparaPilhaRecPa(p1, p2): Chama a funcao recursivamente e armazena
*   o valor de retorno em uma variavel compTam, é basicamente o que decide se as duas
*   pilhas tem o mesmo tamanho.
*
*   if (compTam) {...}: Esse teste é feito porque mesmo se as duas funcoes tiverem o mesmo
*                       tamanho, nao significa que seus elementos sejam iguais. Isso e testado
*                       logo abaixo;
*
*/
int comparaPilhaRecPa(Pilha_a* p1, Pilha_a* p2) {
    if (taVaziaPa(p1) && taVaziaPa(p2))
        return 1;
    if (taVaziaPa(p1) || taVaziaPa(p2))
        return 0;
    int aux1 = popPa(p1), aux2 = popPa(p2);
    int compTam = comparaPilhaRecPa(p1, p2);
    pushPa(p1, aux1);
    pushPa(p2, aux2);
    if (compTam) {
        if (aux1==aux2)
            return 1;
        else
            return 0;
    }
    return 0;
}

/*comparaPilhaItrPa(Pilha_a* p1, Pilha_a* p2):
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
*   while (!taVaziaPa(p1) && !taVaziaPa(p2)) {...}: Aqui e onde basicamente tudo acontece. Ele inicia
*                                                   testando se uma das duas pilhas ta vazia.
*
*                                                   if (i==t_tam) {...}: pra quando o indice que percorre
*                                                   os vetores atingir o tamanho do vetor, o que indica que
*                                                   ele precisa ter o tamanho incrementado, a tecnica usada pra
*                                                   esse aumento foi sempre dobrar o tamanho do vetor, um bagulho
*                                                   chamado análise amortizada, que pondera o custo de memória pelo
*                                                   custo de tempo, e como o realloc normalmente e uma funcao que gasta
*                                                   um tempinho pra ser concluida, usar o menos possivel e a melhor opcao;
*
*
*                                                   if (peekPa(p1)!=peekPa(p2)) {...}: Testa se os topos atuais das listas sao
*                                                   diferentes, caso sim, ele atribui 0 ao valor de retono da funcao, e quebra o loop;
*
*                                                   t_p1[i] = popPa(p1); t_p2[i] = popPa(p2); i++: Aqui ele so retira o valor do topo
*                                                   das duas pilhas depois de todos os testes e os armazena no vetor que funciona
*                                                   como uma pilha auxiliar;
*
*   while (--i >= 0) {...}: Esse loop aqui so serve pra colocar os elementos
*                           retirados de cada pilha de volta nos seus lugares.
*                           Nao importa se o teste dos elementos dentro do loop
*                           while falhou e ele quebrou o loop, os elementos vao
*                           voltar de forma normal;
*
*
*/
int comparaPilhaItrPa(Pilha_a* p1, Pilha_a* p2) {
    int tam1 = tamanhoPa(p1, 'f'), tam2 = tamanhoPa(p2, 'f');
    int* t_p1 = malloc(sizeof(int));
    int* t_p2 = malloc(sizeof(int));
    int t_tam = 1;
    int i = 0, r = 1;

    if (tam1!=tam2)
        return 0;
    while (!taVaziaPa(p1) && !taVaziaPa(p2)) {
        if (i==t_tam) {
            t_p1 = realloc(t_p1, (t_tam*2)*sizeof(int));
            t_p2 = realloc(t_p2, (t_tam*2)*sizeof(int));
            t_tam *= 2;
        }
        if (peekPa(p1)!=peekPa(p2)) {
            r = 0;
            break;
        }
        t_p1[i] = popPa(p1);
        t_p2[i] = popPa(p2);
        i++;
    }
    while (--i >= 0) {
        pushPa(p1, t_p1[i]);
        pushPa(p2, t_p2[i]);
    }
    free(t_p1);
    free(t_p2);
    return r;
}
