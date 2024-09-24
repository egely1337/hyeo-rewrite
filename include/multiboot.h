#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include <typedefs.h>


typedef struct {
    uint32_t magic;
    uint32_t header_lenght;
    uint32_t checksum;
} multiboot_t;

#endif