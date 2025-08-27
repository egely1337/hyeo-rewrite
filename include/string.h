#ifndef STRING_H
#define STRING_H
#include <typedefs.h>
void memcpy(void* dst, void *src, size_t length);
void memset(void* dst, uint8_t val, size_t length);
uint8_t memcmp(void* src, void* b, int n);
int strlen(const char* str);
void strcpy(char* dest, char* src);
void strncpy(char* dest, char* src, int n);
void strrev(char* str);
char* itoa(uint32_t a);
char* ithex(uint32_t a);
#define MAX_STRING_LENGHT 512
#endif