#ifndef PMM_H
#define PMM_H
#include <typedefs.h>
#include <string.h>

// 4 KiB block size
#define BLOCK_SIZE (uint32_t)4096 
// 8 (Eight bits in a byte)
#define BLOCKS_PER_BYTE (uint32_t)8



#define BLOCK_TO_PHYS(idx) \
	(void*)(PhysicalMemoryManager.BitmapAddress + (idx * BLOCK_SIZE))
#define INVALID_BLOCK_HANDLE 0xFFFFFFFF

/* 
 *	n = number
 *	d = divisior
 */
#define DIV_ROUND_UP(n, d) (((n) + (d) - 1) / (d))

// Sets a bit block with 1
#define SETBIT(i) \
	PhysicalMemoryManager.BitmapAddress[DIV_ROUND_UP(i, BLOCKS_PER_BYTE)] = PhysicalMemoryManager.BitmapAddress[DIV_ROUND_UP(i, BLOCKS_PER_BYTE)] | (1 << (i % BLOCKS_PER_BYTE))

// Clears a bit block with 0
#define CLEARBIT(i) \
	PhysicalMemoryManager.BitmapAddress[DIV_ROUND_UP(i, BLOCKS_PER_BYTE)] = PhysicalMemoryManager.BitmapAddress[DIV_ROUND_UP(i, BLOCKS_PER_BYTE)] | (1 << (~(i % BLOCKS_PER_BYTE)))

// Checks is block 1 or not.
#define ISSET(i) \
	((PhysicalMemoryManager.BitmapAddress[DIV_ROUND_UP(i, BLOCKS_PER_BYTE)] >> (i % BLOCKS_PER_BYTE)) & 0x1)


void initalize_pmm(
	uint32_t MemoryStartAddress,
	uint32_t MemorySize
);
uint32_t 	allocate_block();
uint32_t 	find_first_free_block(void);
void 	free_block(uint32_t block);


/*
 *	Physical Memory Manager:
 *		There is a bitmap that manages the physical memory, the first 20 bits per byte of this bitmap indicate where it points in 1 MB pages.
 * 		That way, you manage the memory.
 */

#endif