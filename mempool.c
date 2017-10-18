#include <stdio.h>
#include <stdlib.h>
#include "mempool.h"

typedef struct __MEM_POOL {
    size_t used;
    size_t size;
    char *pool;
} MemPool;

MemPool *new_mem_pool(size_t size)
{
    MemPool *p = calloc(size, sizeof(MemPool));
    if (p == NULL) {
        return NULL
    };

    p->pool = calloc(size, sizeof(char));
    if (p->pool == NULL) {
        free(p);
        return NULL;
    }

    p->size = size;
    p->used = 0;

    return p;
}

char *poalloc(size_t size, MemPool *p)
{
    if (p->size - p->used < size) {
        char *space = malloc(sizeof(char) * size);
        return space;
    }

    char *allocate = p->pool + p->used;
    p->used += size;

    return allocate;
}

char *get_pool_curr(MemPool *p)
{
    return p->pool + p->used;
}

void mv_pool_curr(int dist, MemPool *p)
{
    if (p->used + dist < 0 || p->used + dist > p->size) {
        printf("abort: move to a illegal position in memory pool.\n");
        abort();
    }

    p->used += dist;
}
