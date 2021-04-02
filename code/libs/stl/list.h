#ifndef __LIBS_LIST_H__
#define __LIBS_LIST_H__

#ifndef __ASSEMBLER__

#include <libs/ctype.h>

struct list_entry{
    struct list_entry *prev, *next;
};

typedef struct list_entry list_node;

static inline void list_init(list_node *elm) __attribute__((always_inline));
static inline void list_add(list_node* listelm, list_node *elm) __attribute__((always_inline));
static inline void list_add_before(list_node *listelm, list_node *elm) __attribute__((always_inline));
static inline void list_add_after(list_node *listelm, list_node *elm) __attribute__((always_inline));
static inline void list_del(list_node *listelm) __attribute__((always_inline));
static inline void list_del_init(list_node *listelm) __attribute__((always_inline));
static inline void list_empty(list_node *listelm) __attribute__((always_inline));
static inline list_node *list_next(list_node *listelm) __attribute__((always_inline));
static inline list_node *list_prev(list_node *listelm) __attribute__((always_inline));

static inline void __list_add(list_node *elm, list_node *prev, list_node *next) __attribute__((always_inline));
static inline void __list_del(list_node *prev, list_node *next) __attribute__((always_inline));


static inline void list_init(list_node *elm){
    elm->prev = elm->next = elm;
}

static inline void list_add(list_node *listelm, list_node *elm){
    list_add_after(listelm, elm);
}

static inline void list_add_before(list_node *listelm, list_node *elm) {
    __list_add(elm, listelm->prev, listelm);
}


static inline void list_add_after(list_node *listelm, list_node *elm) {
    __list_add(elm, listelm, listelm->next);
}

static inline void list_del(list_node *listelm) {
    __list_del(listelm->prev, listelm->next);
}

static inline void list_del_init(list_node *listelm) {
    list_del(listelm);
    list_init(listelm);
}

static inline bool list_empty(list_node *list) {
    return list->next == list;
}

static inline list_node * list_next(list_node *listelm) {
    return listelm->next;
}

static inline list_node * list_prev(list_node *listelm) {
    return listelm->prev;
}

static inline void __list_add(list_node *elm, list_node *prev, list_node *next) {
    prev->next = next->prev = elm;
    elm->next = next;
    elm->prev = prev;
}

static inline void __list_del(list_node *prev, list_node *next) {
    prev->next = next;
    next->prev = prev;
}

#endif 

#endif