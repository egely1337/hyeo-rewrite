#ifndef TYPEDEFS_H
#define TYPEDEFS_H
typedef unsigned int uint32_t;
typedef int int32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int size_t;
typedef char byte;
#define hlt() for(;;)
#define cli() __asm__ __volatile__("cli");
#define sti() __asm__ __volatile__("sti");
#define LOW_16(address) (uint16_t)((address) & 0xFFFF)
#define HIGH_16(address) (uint16_t)((address) >> 16)



#define HYEO_EXPORT extern
#define __FORCEINLINE__ inline __attribute__((always_inline))

#endif