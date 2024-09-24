#ifndef STRING_H
#define STRING_H
#include <typedefs.h>
void memcpy(void* dst, void *src, size_t length);
void memset(void* dst, uint8_t val, size_t length);
int strlen(const char* str);
#endif