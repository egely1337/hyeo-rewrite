/*
 *  file: string.c
 *  author: egely1337
 *  purpose: string manipulator 
 */

#include <string.h>

void memcpy(void *dst, void *src, size_t length)
{   
    byte* _dst = (byte*)dst;
    byte* _src = (byte*)src;

    for(int i = 0; i < length; i++) {
        _dst[i] = _src[i];
    }
}

void memset(void *dst, uint8_t val, size_t length)
{
    byte* _dst = (byte*)dst;
    for(int i = 0; i < length; i++) _dst[i] = val;
}

int strlen(const char *str)
{
    int i = 0;
    uint8_t* ptr = (uint8_t*)str;

    while(*ptr != '\0' && i < MAX_STRING_LENGHT) {
        i++;
        ptr++;
    }

    return i;
}
