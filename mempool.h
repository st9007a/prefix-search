#ifndef MEMPOOL_H
#define MEMPOOL_H

#include <stdlib.h>

typedef struct __MEM_POOL MemPool;

MemPool *new_mem_pool(size_t size);
char *poalloc(size_t size, MemPool *p);

char *get_pool_curr(MemPool *p);
void mv_pool_curr(int dist, MemPool *p);
#endif
