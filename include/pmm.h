#ifndef PMM_H
#define PMM_H
#include <typedefs.h>
#include <string.h>
#include <multiboot.h>

// 4 KiB block size
#define BLOCK_SIZE (uint32_t)4096 
// 8 (Eight bits in a byte)
#define BLOCKS_PER_BYTE (uint32_t)8

/* 
 *	n = number
 *	d = divisior
 */
#define DIV_ROUND_UP(n, d) (((n) + (d) - 1) / (d))

/* Get total buckets as bytes */
#define GET_BUCKET_BYTE (uint32_t)(PhysicalMemoryManager.MemorySize / BLOCK_SIZE / BLOCKS_PER_BYTE)

#define BLOCK_TO_PHYS(idx) \
	(void*)(PhysicalMemoryManager.BitmapAddress + GET_BUCKET_BYTE + (idx * BLOCK_SIZE))
#define INVALID_BLOCK_HANDLE 0xFFFFFFFF

// Sets a bit block with 1
#define SETBIT(i) \
	PhysicalMemoryManager.BitmapAddress[DIV_ROUND_UP(i, BLOCKS_PER_BYTE)] = PhysicalMemoryManager.BitmapAddress[DIV_ROUND_UP(i, BLOCKS_PER_BYTE)] | (1 << (i % BLOCKS_PER_BYTE))

// Clears a bit block with 0
#define CLEARBIT(i) \
	PhysicalMemoryManager.BitmapAddress[DIV_ROUND_UP(i, BLOCKS_PER_BYTE)] = PhysicalMemoryManager.BitmapAddress[DIV_ROUND_UP(i, BLOCKS_PER_BYTE)] | (1 << (~(i % BLOCKS_PER_BYTE)))

// Checks is block 1 or not.
#define ISSET(i) \
	((PhysicalMemoryManager.BitmapAddress[DIV_ROUND_UP(i, BLOCKS_PER_BYTE)] >> (i % BLOCKS_PER_BYTE)) & 0x1)


void parse_mmap(multiboot* multibootptr);
void initalize_pmm(uint32_t MemoryStartAddress, uint32_t MemorySize);
uint32_t alloc_block();
uint32_t find_first_free_block(void);
void free_block(uint32_t block);
uint32_t allocnblocks(uint32_t n);







#endif