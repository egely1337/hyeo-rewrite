#ifndef PMM_H
#define PMM_H
#include <typedefs.h>
#include <string.h>

// 4 KiB block size
#define BLOCK_SIZE (uint32_t)4096 
#define BLOCKS_PER_BUCKET (uint32_t)8

#define SETBIT(i) \
	MemoryBitmap[i / BLOCKS_PER_BUCKET] = MemoryBitmap[i / BLOCKS_PER_BUCKET] | (1 << (i % BLOCKS_PER_BUCKET))
#define CLEARBIT(i) \
	MemoryBitmap[i / BLOCKS_PER_BUCKET] = MemoryBitmap[i / BLOCKS_PER_BUCKET] | (1 << (~(i % BLOCKS_PER_BUCKET)))
#define ISSET()
// I want to kill myself.


void initalize_pmm(
	uint32_t MemoryStartAddress,
	uint32_t MemorySize
);
void* 	allocate_block(void);


/*
 *	Physical Memory Manager:
 *		There is a bitmap that manages the physical memory, the first 20 bits per byte of this bitmap indicate where it points in 1 MB pages.
 * That way, you manage the memory.
 */

#endif