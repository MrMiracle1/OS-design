#ifndef __LIS_STL_SKEW_HEAP_H__
#define __LIS_STL_SKEW_HEAP_H__

struct skew_heap_entry
{
    struct skew_heap_entry *p, *left, *right;    
};

typedef struct skew_heap_entry skew_heap_entry_t;

typedef int(*compare_fn)(void *a, void *b);

static inline void skew_heap_init(skew_heap_entry_t *a) __attribute__((always_inline));
static inline skew_heap_entry_t *skew_heap_merge(
     skew_heap_entry_t *a, skew_heap_entry_t *b,
     compare_fn comp);
static inline skew_heap_entry_t *skew_heap_insert(
     skew_heap_entry_t *a, skew_heap_entry_t *b,
     compare_fn comp) __attribute__((always_inline));
static inline skew_heap_entry_t *skew_heap_remove(
     skew_heap_entry_t *a, skew_heap_entry_t *b,
     compare_fn comp) __attribute__((always_inline));

static inline void skew_heap_init(skew_heap_entry_t *a){
    a->left = a->right = a->right = NULL;
}

static inline skew_heap_entry_t *
skew_heap_merge(skew_heap_entry_t *a, skew_heap_entry_t *b,
                compare_fn comp)
{
     if (a == NULL) return b;
     else if (b == NULL) return a;
     
     skew_heap_entry_t *l, *r;
     if (comp(a, b) == -1)
     {
          r = a->left;
          l = skew_heap_merge(a->right, b, comp);
          
          a->left = l;
          a->right = r;
          if (l) l->p = a;

          return a;
     }
     else
     {
          r = b->left;
          l = skew_heap_merge(a, b->right, comp);
          
          b->left = l;
          b->right = r;
          if (l) l->p = b;

          return b;
     }
}

static inline skew_heap_entry_t *
skew_heap_insert(skew_heap_entry_t *a, skew_heap_entry_t *b,
                 compare_fn comp)
{
     skew_heap_init(b);
     return skew_heap_merge(a, b, comp);
}

static inline skew_heap_entry_t *
skew_heap_remove(skew_heap_entry_t *a, skew_heap_entry_t *b,
                 compare_fn comp)
{
     skew_heap_entry_t *p   = b->p;
     skew_heap_entry_t *rep = skew_heap_merge(b->left, b->right, comp);
     if (rep) rep->p = p;
     
     if (p)
     {
          if (p->left == b)
               p->left = rep;
          else p->right = rep;
          return a;
     }
     else return rep;
}

#endif