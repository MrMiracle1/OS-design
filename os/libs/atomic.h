#ifndef __LIBS_ATOMIC_H__
#define __LIBS_ATOMIC_H__


/* 对bit的原子操作 */
static inline void set_bit(int nr, volatile void *addr) __attribute__((always_inline));
static inline void clear_bit(int nr, volatile void *addr) __attribute__((always_inline));
static inline void change_bit(int nr, volatile void *addr) __attribute__((always_inline));
static inline void test_bit(int nr, volatile void *addr) __attribute__((always_inline));


static inline void set_bit(int nr, volatile void *addr){
    asm volatile("btsl %1, %0"
        : "=m" (*(volatile long *)addr)
        : "Ir" (nr)
    );
}

static inline void clear_bit(int nr, volatile void *addr){
    asm volatile ("btrl %1, %0"
        : "=m" (*(volatile long *)addr)
        : "Ir" (nr)
    );
}

static inline void change_bit(int nr, volatile void *addr){
    asm volatile ("btcl %1, %0" 
        : "=m" (*(volatile long *)addr) 
        : "Ir" (nr)
    );
}

static inline bool test_bit(int nr, volatile void *addr){
    int oldbit;
    asm volatile("btl %2, %1;
            sbbl %0, %0"
            : "=r" (oldbit)
            : "m" (*(volatile long *)addr),"Ir"(nr)
            );

    return oldbit!= 0;
}

#endif 