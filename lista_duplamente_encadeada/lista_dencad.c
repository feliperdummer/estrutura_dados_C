#include "lista_dencad.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

Lista_d* criaLD(size_t data_size) {
    Lista_d* lista = (Lista_d*)malloc(sizeof(Lista_d));
    if (lista==NULL) {
        return NULL;
    }

    lista->data_type = data_size;
    lista->tam = 0x0;
    lista->head = NULL;
    lista->tail = NULL;
    
    return lista;
}

LD_Status inserePLD(Lista_d* lista, const void* valor, size_t p) {
    if (lista==NULL || valor==NULL) {
        return LD_NULL_PTR;
    }
    if (p > lista->tam) {
        return LD_INV_POS;
    }

    Node_d* node = (Node_d*)malloc(sizeof(Node_d));
    if (node==NULL) {
        return LD_MEM_ERR;
    }

    node->info = malloc(lista->data_type);
    if (node->info==NULL) {
        free(node);
        return LD_MEM_ERR;
    }
    memcpy(node->info, valor, lista->data_type);

    node->prox = NULL;
    node->ant = NULL;
    
    if (lista->tam==0x0) { // lista vazia;
        lista->head = node;
        lista->tail = node;
    }
    else if (p==0) { // insercao na primeira posicao
        node->prox = lista->head;
        lista->head->ant = node;
        lista->head = node;
    }
    else if (p==lista->tam) { // insercao na ultima posicao
        lista->tail->prox = node;
        node->ant = lista->tail;
        lista->tail = node;
    }
    else { // insercao no meio
        Node_d* curr = lista->head;
        while (curr!=NULL && --p > 0) {
            curr = curr->prox;
        }
        node->prox = curr->prox;
        curr->prox->ant = node;
        curr->prox = node;
        node->ant = curr;
    }

    lista->tam++;

    return LD_SUCCESS;
}

LD_Status insereILD(Lista_d* lista, const void* valor) {

    return inserePLD(lista, valor, 0);
}

LD_Status insereFLD(Lista_d* lista, const void* valor) {

    return inserePLD(lista, valor, lista->tam);
}

LD_Status insereOLD(Lista_d* lista, const void* valor, Comparador cmp) {
    if (lista==NULL || valor==NULL) {
        return LD_NULL_PTR;
    }

    Node_d* node = (Node_d*)malloc(sizeof(Node_d));
    if (node==NULL) {
        return LD_MEM_ERR;
    }

    node->info = malloc(lista->data_type);
    if (node->info==NULL) {
        free(node);
        return LD_MEM_ERR;
    }
    memcpy(node->info, valor, lista->data_type);

    node->prox = NULL;
    node->ant = NULL;

    if (lista->tam==0x0) { // lista vazia
        return inserePLD(lista, valor, 0);
    }
    else if (cmp(node->info, lista->head->info) < 0) { //caso o valor seja menor que o head
        return inserePLD(lista, valor, 0);
    }
    else if (cmp(node->info, lista->tail->info) >= 0) { // caso o valor seja maior ou igual ao tail
        return inserePLD(lista, valor, lista->tam);
    }
    else { // insercao no meio
        Node_d* curr = lista->head;
        while (curr!=NULL && cmp(node->info, curr->info) >= 0) {
            curr = curr->prox;
        }
        node->prox = curr;
        node->ant = curr->ant;
        curr->ant->prox = node;
        curr->ant = node;
    }

    lista->tam++;

    return LD_SUCCESS;
}

LD_Status rmPLD(Lista_d* lista, size_t p) {
    if (lista==NULL) {
        return LD_NULL_PTR;
    }
    if (p >= lista->tam) {
        return LD_INV_POS;
    }
    if (lista->tam==0x0) {
        return LD_EMPTY;
    }

    Node_d* rm = NULL;

    if (p==0x0) {
        rm = lista->head;
        lista->head = lista->head->prox;
        if (lista->head!=NULL) { // cuida do ant do novo head
            lista->head->ant = NULL;
        }
    }
    else if (p==lista->tam-1) {
        rm = lista->tail;
        lista->tail = lista->tail->ant;
        if (lista->tail!=NULL) { // cuida do prox do novo tail
            lista->tail->prox = NULL;
        }
    }
    else {
        rm = lista->head;
        while (rm!=NULL && p-- > 0) {
            rm = rm->prox;
        }
        rm->ant->prox = rm->prox;
        rm->prox->ant = rm->ant;
    }

    free(rm->info);
    free(rm);

    if (lista->head==NULL) { // caso a lista esteja vazia depois da remocao
        lista->tail = NULL;
    }

    lista->tam--;

    return LD_SUCCESS;
}

size_t rmVLD(Lista_d* lista, const void* valor, Comparador cmp, LD_Status* flag) {
    if (lista==NULL || valor==NULL) {
        if (flag!=NULL) {
            *flag = LD_NULL_PTR;
        }
        return 0;
    }
    if (lista->tam==0x0) {
        if (flag!=NULL) {
            *flag = LD_EMPTY;
        }
        return 0;
    }

    Node_d* rm = NULL;
    Node_d* aux = NULL;
    size_t q = 0;

    while (lista->head!=NULL && cmp(lista->head->info, valor)==0) {
        aux = lista->head;
        lista->head = lista->head->prox;
        free(aux->info);
        free(aux);
        q++;
    }

    if (lista->head==NULL) {
        lista->tail = NULL;
    }
    else {
        lista->head->ant = NULL;
        aux = lista->head;
        rm = lista->head->prox;
    }

    while (rm) {
        if (cmp(rm->info, valor)==0) {
            if (rm==lista->tail) {
                lista->tail = aux;
            }
            else { 
                rm->prox->ant = aux;
            }
            aux->prox = rm->prox;
            free(rm->info);
            free(rm);
            rm = aux->prox;
            q++;
        }
        else {
            aux = rm;
            rm = rm->prox;
        }
    }

    lista->tam -= q;

    if (flag!=NULL) {
        *flag = LD_SUCCESS;
    }
    return q;
}

LD_Status rmILD(Lista_d* lista) {
    return rmPLD(lista, 0);
}

LD_Status rmULD(Lista_d* lista) {
    return rmPLD(lista, lista->tam-1);
}

// usa a flag aqui por favor;
size_t rmFLD(Lista_d* lista, const void* valor, Comparador cmp, LD_Status* flag) {
    if (lista==NULL || valor==NULL) {
        if (flag!=NULL) {
            *flag = LD_NULL_PTR;
        }
        return 0;
    }
    if (lista->tam==0x0) {
        if (flag!=NULL) {
            *flag = LD_EMPTY;
        }
        return 0;
    }

    if (cmp(lista->head->info, valor)==0) { // caso o valor esteja no head
        rmPLD(lista, 0);
        return 0;
    }
    if (cmp(lista->tail ->info, valor)==0) { // caso o valor esteja no tail
        rmPLD(lista, lista->tam-1);
        return lista->tam-1;
    }

    size_t p = 1;
    Node_d* rm = lista->head->prox;
    
    while (rm) {
        if (cmp(rm->info, valor)==0) {
            rm->ant->prox = rm->prox;
            rm->prox->ant = rm->ant;

            free(rm->info);
            free(rm);

            lista->tam--;

            if (flag!=NULL) {
                *flag = LD_SUCCESS;
            }
            return p;
        }
        else {
            rm = rm->prox;
            p++;
        }
    }

    if (flag!=NULL) {
        *flag = LD_VAL_NOT_FOUND;
    }
    return 0;
}

// nao é recomendado passar o argumento da flag como NULL, por causa do valor de retorno
size_t searchLD(const Lista_d* lista, const void* valor, Comparador cmp, LD_Status* flag) {
    if (lista==NULL || valor==NULL) {
        if (flag!=NULL) {
            *flag = LD_NULL_PTR;
            return 0;
        }
    }
    if (lista->tam==0x0) {
        if (flag!=NULL) {
            *flag = LD_EMPTY;
            return 0;
        }
    }

    Node_d* search = NULL;
    size_t p = 0;

    if (cmp(lista->head->info, valor)==0) { // valor encontrado na primeira posicao
        p = 0;
    }
    else if (cmp(lista->tail->info, valor)==0) { // valor encontrado na ultima posicao
        p = lista->tam-1;
    }
    else {
        search = lista->head->prox;
        p = 1;
        while (search!=NULL && cmp(search->info, valor)!=0) {
            search = search->prox;
            p++;
        }

        if (search==NULL) {
            if (flag!=NULL) {
                *flag = LD_VAL_NOT_FOUND;
            }
            return 0;
        }
    }

    if (flag!=NULL) {
        *flag = LD_SUCCESS;
    }
    return p; 
}

void* getNodeValLD(const Lista_d* lista, size_t p, LD_Status* flag) {
    if (lista==NULL) {
        if (flag!=NULL) {
            *flag = LD_NULL_PTR;
        }
        return NULL;
    }
    if (p >= lista->tam) {
        if (flag!=NULL) {
            *flag = LD_INV_POS;
        }
        return NULL;
    }

    if (p==0x0) { // primeiro no da lista;
        if (flag!=NULL) {
            *flag = LD_SUCCESS;
        }
        return lista->head->info;
    }
    if (p==lista->tam-1) { // ultimo no da lista;
        if (flag!=NULL) {
            *flag = LD_SUCCESS;
        }
        return lista->tail->info;
    }

    Node_d* search = lista->head;
    
    while (search!=NULL && p-- > 0) {
        search = search->prox;
    }

    if (search==NULL) {
        if (flag!=NULL) {
            *flag = LD_INV_POS;
        }
        return NULL;
    }

    if (flag!=NULL) {
        *flag = LD_SUCCESS;
    }
    return search->info;
}

// eu usaria a flag aqui, hehe;
size_t sizeLD(const Lista_d* lista, LD_Status* flag) {
    if (lista==NULL) {
        if (flag!=NULL) {
            *flag = LD_NULL_PTR;
        }
        return 0;
    }

    if (flag!=NULL) {
        *flag = LD_SUCCESS;
    }
    return lista->tam;
}

// cuidado ao usar essa funcao sem passar uma flag como parametro
bool taVaziaLD(const Lista_d* lista, LD_Status* flag) {
    if (lista==NULL) {
        if (flag!=NULL) {
            *flag = LD_NULL_PTR;
        }
        return true;
    }

    if (flag!=NULL) {
        *flag = LD_SUCCESS;
    }
    return (lista->tam==0x0) ? true : false;
}

LD_Status limpaLD(Lista_d* lista) {
    if (lista==NULL) {
        return LD_NULL_PTR;
    }
    if (lista->tam==0x0) {
        return LD_EMPTY;
    }

    Node_d* rm = lista->head;
    Node_d* aux = NULL;

    while (rm) {
        aux = rm;
        rm = rm->prox;

        free(aux->info);
        free(aux);
    }

    lista->head = NULL;
    lista->tail = NULL;

    return LD_SUCCESS;
}

LD_Status killLD(Lista_d* lista) {
    if (lista==NULL) {
        return LD_NULL_PTR;
    }
    if (lista->tam==0x0) {
        return LD_EMPTY;
    }

    Node_d* rm = lista->head;
    Node_d* aux = NULL;

    while (rm) {
        aux = rm;
        rm = rm->prox;

        free(aux->info);
        free(aux);
    }
    free(lista);

    return LD_SUCCESS;
}
