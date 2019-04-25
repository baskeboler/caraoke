#include "list.h"
#include <stdlib.h>

status_t list_push(list_t * ls, void* data) {
    list_t new_ls = (list_t) malloc(sizeof(struct list_node_t));
    new_ls->data = data;
    new_ls->next = *ls;
    *ls = new_ls;
    return STATUS_OK;
}

BOOL list_is_empty(list_t ls) {
    return ls == NULL;
}

list_t list_singleton(void *data) {
    list_t new_ls = (list_t) malloc(sizeof(struct list_node_t));
    new_ls->data = data;
    new_ls->next = NULL;
    return new_ls;
}
status_t list_pop(list_t *ls, void ** data_ptr) {
    if (*ls != NULL) {
        list_t aux = *ls;
        *data_ptr = aux->data;
        *ls = aux->next;
        return STATUS_OK;
    }
    return STATUS_ERROR_LIST_EMPTY;
}

list_t list_init() {
    return NULL;
}


status_t list_append(list_t * ls, void * data) {
    if (!list_is_empty(*ls)) {
        list_t aux = *ls;
        while (!list_is_empty(aux->next)) {
            aux = aux->next;
        }
        aux->next = list_singleton(data);
    } else {
        *ls = list_singleton(data);
    }
    return STATUS_OK;
}

status_t list_destroy(list_t * l) {
    if (*l == NULL) return STATUS_OK;
    list_t aux = *l;
    list_destroy(&(aux->next));
    *l = NULL;
    free(aux->data);
    free(aux);
    return STATUS_OK;
}