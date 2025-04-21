/*
 *  file: pmm.c
 *  author: egely1337
 *  purpose: physical memory management 
 */


#include <pmm.h>
#include <terminal.h>

uint8_t* MemoryBitmap;
uint32_t BlockCount;
uint32_t MemorySize;
uint32_t BitmapSize;
uint32_t CurrentBlocks;

/*
 *	author: egely1337
 *	purpose: initialize pmm
 *	params: start_of_address (void*)
 */
void initalize_pmm(
	uint32_t MemoryStartAddress,
	uint32_t MemorySize
) {
	MemoryBitmap = (uint8_t*)MemoryStartAddress;
	MemorySize = MemorySize * 1000;
	BlockCount = MemorySize / BLOCK_SIZE;
	BitmapSize = BlockCount / BLOCKS_PER_BUCKET;

	if(BitmapSize * BLOCKS_PER_BUCKET < BlockCount) {
		BitmapSize = BitmapSize + 1;
	}

    void* block1 = allocate_block();
    void* block2 = allocate_block();

    terminal_print_string(ithex((uint32_t)block1));
    terminal_print_string("\n");
    terminal_print_string(ithex((uint32_t)block2));
    terminal_print_string("\n");

	memset(MemoryBitmap, 0xFF, MemorySize);
}

/*
 *	author: egely1337
 *	purpose: allocate block
 */
void* allocate_block(void) {
	CurrentBlocks++;
	return (void*)MemoryBitmap + (BLOCK_SIZE * CurrentBlocks);
}