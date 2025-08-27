#ifndef KALLOC_H
#define KALLOC_H

#include <hyeo.h>
#include <pmm.h>

typedef struct KBlock {
    char free;
};

void kalloc_init(void);
void kalloc(size_t n);
void kfree(size_t n);

#endif