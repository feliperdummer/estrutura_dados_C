#include "lista_encad.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>


Lista_e* criaL(size_t data_size) {
    Lista_e* lista = (Lista_e*)malloc(sizeof(Lista_e));
    if (lista==NULL) {
        return NULL;
    }

    lista->data_type = data_size;
    lista->tam = 0x0;
    lista->head = NULL;
    lista->tail = NULL;

    return lista;
}

void insereIL(Lista_e* lista, const void* valor) {
    Node_e* node = (Node_e*)malloc(sizeof(Node_e));
    if (node==NULL) {
        return;
    }

    node->info = malloc(lista->data_type);
    if (node->info==NULL) {
        free(node);
        return;
    }
    memcpy(node->info, valor, lista->data_type);

    node->prox = lista->head;
    lista->head = node;
    if (lista->tam==0x0) {
        lista->tail = node;
    }
    lista->tam = lista->tam + 0x1;
}

void insereFL(Lista_e* lista, const void* valor) {
    Node_e* node = (Node_e*)malloc(sizeof(Node_e));
    if (node==NULL) {
        return;
    }
    
    node->info = malloc(lista->data_type);
    if (node->info==NULL) {
        free(node);
        return;
    }
    memcpy(node->info, valor, lista->data_type);

    node->prox = NULL;
    if (lista->tam==0x0) {
        lista->head = node;
    }
    else {
        lista->tail->prox = node;
    }
    lista->tail = node;
    lista->tam = lista->tam + 0x1;
}

void insereOL(Lista_e* lista, const void* valor, Comparador cmp) {
    Node_e* node = (Node_e*)malloc(sizeof(Node_e));
    if (node==NULL) {
        return;
    }

    Node_e* curr = lista->head;
    Node_e* aux = NULL;

    node->info = malloc(lista->data_type);
    if (node->info==NULL) {
        free(node);
        return;
    }
    memcpy(node->info, valor, lista->data_type);

    while (curr!=NULL && cmp(node->info, curr->info) > 0) {
        aux = curr;
        curr = curr->prox;
    }
    if (aux==NULL) {
        lista->head = node;
    }
    else {
        aux->prox = node;
    }

    node->prox = curr;
    if (curr==NULL) {
        lista->tail = node;
    }
    lista->tam = lista->tam + 0x1;
}

void inserePL(Lista_e* lista, const void* valor, size_t p) {
    Node_e* node = (Node_e*)malloc(sizeof(Node_e));
    if (node==NULL) {
        return;
    }

    node->info = malloc(lista->data_type);
    if (node->info==NULL) {
        free(node);
        return;
    }
    memcpy(node->info, valor, lista->data_type);
    node->prox = NULL;

    if (lista->tam==0x0) {
        lista->head = node;
        lista->tail = node;
    }
    else if (p==0x0) {
        node->prox = lista->head;
        lista->head = node;
    }
    else if (p>=(lista->tam)) {
        lista->tail->prox = node;
        lista->tail = node;
    }
    else {
        Node_e* curr = lista->head;
        while (--p > 0) {
            curr = curr->prox;
        }
        node->prox = curr->prox;
        curr->prox = node;
    }

    lista->tam = lista->tam + 0x1;
}

int rmIL(Lista_e* lista) {
    if (lista->tam==0x0) {
        return -1;
    }

    Node_e* aux = lista->head;

    lista->head = lista->head->prox;

    if (lista->head==NULL) {
        lista->tail = NULL;
    }

    free(aux->info);
    free(aux);
    
    lista->tam = lista->tam - 0x1;

    return 1;
}

int rmUL(Lista_e* lista) {
    if (lista->tam==0x0) {
        return -1;
    }

    if (lista->head==lista->tail) {
        free(lista->head->info);
        free(lista->head);

        lista->head = NULL;
        lista->tail = NULL;
    }
    else {
        Node_e* curr = lista->head;

        while (curr->prox!=lista->tail) {
            curr = curr->prox;
        }

        free(lista->tail->info);
        free(lista->tail);

        lista->tail = curr;
        lista->tail->prox = NULL;
    }

    lista->tam = lista->tam - 0x1;

    return 1;
}

int rmPL(Lista_e* lista, const size_t p) {
    Node_e* aux = NULL;
    Node_e* curr = lista->head;

    if (lista->tam==0x0) {
        return -1;
    } 
    if (p>=lista->tam) {
        return -2;
    }

    for (size_t i = 0; i < p; i++) {
        aux = curr;
        curr = curr->prox;
    }

    if (aux==NULL) {
        lista->head = curr->prox;
        if (curr->prox==NULL) {
            lista->tail = NULL;
        }
    }
    else {
        aux->prox = curr->prox;
        if (curr->prox==NULL) {
            lista->tail = aux;
        }
    }

    free(curr->info);
    free(curr);
    lista->tam = lista->tam - 0x1;

    return 1;
}

size_t rmVL(Lista_e* lista, const void* valor, Comparador cmp) {
    size_t count = 0;

    if (lista->tam==0) {
        return count;
    }

    Node_e* aux = NULL;
    Node_e* curr = NULL;

    while (lista->head!=NULL && cmp(lista->head->info, valor)==0) {
        aux = lista->head;
        lista->head = lista->head->prox;

        free(aux->info);
        free(aux);

        ++count;
    }

    if (lista->head==NULL) {
        lista->tail = NULL;
    }
    else {
        aux = lista->head;
        curr = lista->head->prox;
    }

    while (curr) {
        if (cmp(curr->info, valor)==0) {
            if (curr==lista->tail) {
                lista->tail = aux;
            }
            aux->prox = curr->prox;

            free(curr->info);
            free(curr);

            curr = aux->prox;
            ++count;
        }
        else {
            aux = curr;
            curr = curr->prox;
        }
    }
    lista->tam = lista->tam - count;
    return count;
}

ssize_t rmFL(Lista_e* lista, const void* valor, Comparador cmp) {
    if (lista->tam==0x0) {
        return -1;
    }

    Node_e* aux = NULL;
    Node_e* curr = NULL;
    ssize_t p = 0x0;

    if (cmp(lista->head->info, valor)==0x0) {
        aux = lista->head;
        lista->head = lista->head->prox;
        
        free(aux->info);
        free(aux);
        
        if (lista->head==NULL) {
            lista->tail = NULL;
        }
        lista->tam = lista->tam - 0x1;
        return p;
    }

    aux = lista->head;
    curr = lista->head->prox;
    p++;

    while (curr) {
        if (cmp(curr->info, valor)==0x0) {
            aux->prox = curr->prox;
            if (curr==lista->tail) {
                lista->tail = aux;
            }

            free(curr->info);
            free(curr);

            lista->tam = lista->tam - 0x1;
            return p;
        }
        else {
            aux = curr;
            curr = curr->prox;
            p++;
        }
    }

    return -1;
}

ssize_t searchL(Lista_e* lista, const void* valor, Comparador cmp) {
    if (lista->tam==0x0) {
        return -1;
    }

    if (cmp(lista->tail->info, valor)==0x0) {
        return lista->tam-1;
    }

    Node_e* curr = lista->head;
    ssize_t p = 0x0;

    while (curr->prox) {
        if (cmp(curr->info, valor)==0x0) {
            return p;
        }
        else {
            curr = curr->prox;
            p++;
        }
    }

    return -1;
}

void killL(Lista_e* lista) {
    if (lista==NULL) {
        return;
    }

    Node_e* curr = lista->head;
    Node_e* aux = NULL;

    while (curr) {
        aux = curr;
        curr = curr->prox;
        free(aux->info);
        free(aux);
    }
    free(lista);
}
