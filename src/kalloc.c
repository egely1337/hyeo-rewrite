#include <kalloc.h>

struct KBlock* start = nullptr;

void kalloc_init(void) {
    start = (struct KBlock*)alloc_block();
}

void kalloc(size_t n) {

}

void kfree(size_t n) {

}