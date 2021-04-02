#ifndef __LIBS_STDLIB_H__
#define __LIBS_STDLIB_H__

#include <libs/ctype.h>

#define RAND_MAX    2147483647UL

int rand();
void srand(unsigned int seed);

uint32_t hash32(uint32_t val, unsigned int bits);

#endif