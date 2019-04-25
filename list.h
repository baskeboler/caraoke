#if !defined(LIST_H)
#define LIST_H
#include "common.h"

typedef struct list_node_t {
    void* data;
    struct list_node_t* next;
} * list_t;

#define list_foreach(d, ls, type) \
   for(d = ls ? (type) ls->data : NULL; ls != NULL; ls = ls->next)


extern list_t list_singleton(void *data);
extern status_t list_push(list_t * ls, void* data);
extern status_t list_append(list_t * ls, void * data);
extern BOOL list_is_empty(list_t ls);
extern status_t list_pop(list_t *ls, void ** data_ptr);
extern list_t list_init();
extern status_t list_destroy(list_t * l);

#endif // LIST_H
