#include "lista_encad.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

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

L_Status insereIL(Lista_e* lista, const void* valor) {
    if (lista==NULL || valor==NULL) {
        return L_NULL_PTR;
    }

    Node_e* node = (Node_e*)malloc(sizeof(Node_e));
    if (node==NULL) {
        return L_MEM_ERR;
    }

    node->info = malloc(lista->data_type);
    if (node->info==NULL) {
        free(node);
        return L_MEM_ERR;
    }
    memcpy(node->info, valor, lista->data_type);

    node->prox = lista->head;
    lista->head = node;
    if (lista->tam==0x0) {
        lista->tail = node;
    }
    lista->tam = lista->tam + 0x1;

    return L_SUCCESS;
}

L_Status insereFL(Lista_e* lista, const void* valor) {
    if (lista==NULL || valor==NULL) {
        return L_NULL_PTR;
    }

    Node_e* node = (Node_e*)malloc(sizeof(Node_e));
    if (node==NULL) {
        return L_MEM_ERR;
    }
    
    node->info = malloc(lista->data_type);
    if (node->info==NULL) {
        free(node);
        return L_MEM_ERR;
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

    return L_SUCCESS;
}

L_Status insereOL(Lista_e* lista, const void* valor, Comparador cmp) {
    if (lista==NULL || valor==NULL) {
        return L_NULL_PTR;
    }

    Node_e* node = (Node_e*)malloc(sizeof(Node_e));
    if (node==NULL) {
        return L_MEM_ERR;
    }

    Node_e* curr = lista->head;
    Node_e* aux = NULL;

    node->info = malloc(lista->data_type);
    if (node->info==NULL) {
        free(node);
        return L_MEM_ERR;
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

    return L_SUCCESS;
}

L_Status inserePL(Lista_e* lista, const void* valor, size_t p) {
    if (lista==NULL || valor==NULL) {
        return L_NULL_PTR;
    }

    Node_e* node = (Node_e*)malloc(sizeof(Node_e));
    if (node==NULL) {
        return L_MEM_ERR;
    }

    node->info = malloc(lista->data_type);
    if (node->info==NULL) {
        free(node);
        return L_MEM_ERR;
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

    return L_SUCCESS;
}

L_Status rmIL(Lista_e* lista) {
    if (lista==NULL) {
        return L_NULL_PTR;
    }
    if (lista->tam==0x0) {
        return L_EMPTY;
    }

    Node_e* aux = lista->head;

    lista->head = lista->head->prox;

    if (lista->head==NULL) {
        lista->tail = NULL;
    }

    free(aux->info);
    free(aux);
    
    lista->tam = lista->tam - 0x1;

    return L_SUCCESS;
}

L_Status rmUL(Lista_e* lista) {
    if (lista==NULL) {
        return L_NULL_PTR;
    }
    if (lista->tam==0x0) {
        return L_EMPTY;
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

    return L_SUCCESS;
}

L_Status rmPL(Lista_e* lista, const size_t p) {
    if (lista==NULL) {
        return L_NULL_PTR;
    }
    if (lista->tam==0x0) {
        return L_EMPTY;
    } 
    if (p>=lista->tam) {
        return L_INV_POS;
    }

    Node_e* aux = NULL;
    Node_e* curr = lista->head;

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

    return L_SUCCESS;
}

size_t rmVL(Lista_e* lista, const void* valor, Comparador cmp, L_Status* flag) {
    if (lista==NULL || valor==NULL) {
        if (flag!=NULL) *flag = L_NULL_PTR;
        return 0;
    }
    
    size_t count = 0;

    if (lista->tam==0x0) {
        if (flag!=NULL) *flag = L_EMPTY;
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

    if (flag!=NULL) *flag = L_SUCCESS;
    return count;
}

// por favor usa a flag aqui porque nao deu pra retornar valor negativo
size_t rmFL(Lista_e* lista, const void* valor, Comparador cmp, L_Status* flag) {
    if (lista==NULL || valor==NULL) {
        if (flag!=NULL) *flag = L_NULL_PTR;
        return 0;
    }
    if (lista->tam==0x0) {
        if (flag!=NULL) *flag = L_EMPTY;
        return 0;
    }

    Node_e* aux = NULL;
    Node_e* curr = NULL;
    size_t p = 0x0;

    if (cmp(lista->head->info, valor)==0x0) {
        aux = lista->head;
        lista->head = lista->head->prox;
        
        free(aux->info);
        free(aux);
        
        if (lista->head==NULL) {
            lista->tail = NULL;
        }
        lista->tam = lista->tam - 0x1;

        if (flag!=NULL) *flag = L_SUCCESS;
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

            if (flag!=NULL) *flag = L_SUCCESS;
            return p;
        }
        else {
            aux = curr;
            curr = curr->prox;
            p++;
        }
    }

    if (flag!=NULL) *flag = L_VAL_NOT_FOUND;
    return 0;
}

// usa flag aqui tambem, pelo amor do seu codigo 
size_t searchL(const Lista_e* lista, const void* valor, Comparador cmp, L_Status* flag) {
    size_t p = 0x0;

    if (lista==NULL || valor==NULL) {
        if (flag!=NULL) *flag = L_NULL_PTR;
        return p;
    }
    if (lista->tam==0x0) {
        if (flag!=NULL) *flag = L_EMPTY;
        return p;
    }

    if (cmp(lista->tail->info, valor)==0x0) {
        if (flag!=NULL) *flag = L_SUCCESS;
        return lista->tam-1;
    }

    Node_e* curr = lista->head;

    while (curr->prox) {
        if (cmp(curr->info, valor)==0x0) {
            if (flag!=NULL) *flag = L_SUCCESS;
            return p;
        }
        else {
            curr = curr->prox;
            p++;
        }
    }

    if (flag!=NULL) *flag = L_VAL_NOT_FOUND;
    return 0;
}

void* getNodeValL(const Lista_e* lista, const size_t p, L_Status* flag) {
    if (lista==NULL) {
        if (flag!=NULL) *flag = L_NULL_PTR;
        return NULL;
    }
    if (p>=lista->tam) {
        if (flag!=NULL) *flag = L_INV_POS;
        return NULL;
    }

    if (p==lista->tam-1) {
        if (flag!=NULL) *flag = L_SUCCESS;
        return lista->tail->info;
    }

    Node_e* curr = lista->head;

    for (size_t i = 0; i < p; i++) {
        curr = curr->prox;
    }

    if (flag!=NULL) *flag = L_SUCCESS;
    return curr->info;
}

// outra funcao que é recomendado usar a flag
size_t sizeL(const Lista_e* lista, L_Status* flag) {
    if (lista==NULL) {
        if (flag!=NULL) *flag = L_NULL_PTR;
        return 0;
    }

    if (flag!=NULL) *flag = L_SUCCESS;
    return lista->tam;
}

// cuidado ao usar essa funcao sem passar uma flag como parametro
bool taVaziaL(const Lista_e* lista, L_Status* flag) {
    if (lista==NULL) {
        if (flag!=NULL) *flag = L_NULL_PTR;
        return true;
    }

    if (flag!=NULL) *flag = L_SUCCESS;
    return (lista->tam==0x0) ? true : false;
}

L_Status limpaL(Lista_e* lista) {
    if (lista==NULL) {
        return L_NULL_PTR;
    }
    if (lista->tam==0x0) {
        return L_EMPTY;
    }

    Node_e* curr = lista->head;
    Node_e* aux = NULL;

    while (curr) {
        aux = curr;
        curr = curr->prox;
        free(aux->info);
        free(aux);
    }

    lista->head = NULL;
    lista->tail = NULL;

    return L_SUCCESS;
}

L_Status killL(Lista_e* lista) {
    if (lista==NULL) {
        return L_NULL_PTR;
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

    return L_SUCCESS;
}
