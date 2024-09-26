#ifndef TYPEDEFS_H
#define TYPEDEFS_H
typedef unsigned int uint32_t;
typedef uint32_t uintptr_t;
typedef int int32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int size_t;
typedef char byte;
typedef byte bool;

#define hlt() while(1)
#define cli() __asm__ __volatile__("cli");
#define sti() __asm__ __volatile__("sti");
#define LOW_16(address) (uint16_t)((address) & 0xFFFF)
#define HIGH_16(address) (uint16_t)((address) >> 16)
#define true 1 
#define false 0
#define null 0
#define KERNEL_IDLE() hlt()


#define HYEO_EXPORT extern
#define __FORCEINLINE__ inline __attribute__((always_inline))

#endif