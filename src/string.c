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

uint8_t memcmp(void* src, void* b, int n) {
    char* _src = (char*)src;
    char* _b = (char*)b;
    int j = 0;

    while(j < n) {
        if(_src[j] != _b[j]) return 1;
        j++;
    }

    return 0;
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

char* itoa(uint32_t a) {
    char* result = (char*)'0';
    int i = 0;

    do {
        result[i] = a % 10 + '0';
        i++;
    } while((a /= 10) > 0);

    result[i] = 0;

    strrev(result);
    return result;
}

void strrev(char* str) {
    int l = strlen(str) - 1;
    int i, j;
    char tmp;
    for(i = 0, j = l; i > 0, i < j; i++, j--) {
        tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
    }
}


char* ithex(uint32_t a) {
    char* ascii_numbers = (char*)"0123456789ABCDEF";
    char* res;
    uint32_t i = 0;
    uint8_t nibble;

    do {
        nibble = (uint8_t)a & 0x0F;
        nibble = ascii_numbers[nibble];
        res[i] = nibble;
        a >>= 4;
        i++;
    } while(a > 0);

    res[i] = '\0';

    strrev(res);
    return res;
}