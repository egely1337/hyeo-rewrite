#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include <typedefs.h>

#define MULTIBOOT_PAGE_ALIGN    (1 << 0)
#define MULTIBOOT_MEMORY_INFO   (1 << 1)
#define MULTIBOOT_HEADER_MAGIC  0x1BADB002
#define MULTIBOOT_HEADER_FLAGS  (MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO)
#define MULTIBOOT_CHECKSUM      -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

struct multiboot_header {
    uint32_t magic;
    uint32_t flags;
    uint32_t checksum;
} __attribute__((packed));

#endif