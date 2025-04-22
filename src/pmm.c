/*
 *  file: pmm.c
 *  author: egely1337
 *  purpose: physical memory management 
 */


#include <pmm.h>
#include <terminal.h>

struct {
	uint32_t MemoryStartAddress;
	uint8_t* BitmapAddress;
	uint32_t BitmapSizeInBytes;
	uint32_t MemorySize;
	uint32_t BlockSize;
} PhysicalMemoryManager;

/*
 *	author: egely1337
 *	purpose: initialize pmm
 *	params: start_of_address (void*)
 */
void 		initalize_pmm(
	uint32_t MemoryStartAddress,
	uint32_t MemorySize
) {
	PhysicalMemoryManager.BitmapAddress = (uint8_t*)MemoryStartAddress;
	PhysicalMemoryManager.MemorySize = (MemorySize * 1000); // KiB to bytes;
	PhysicalMemoryManager.BlockSize = DIV_ROUND_UP(PhysicalMemoryManager.MemorySize, BLOCK_SIZE);
	PhysicalMemoryManager.BitmapSizeInBytes = DIV_ROUND_UP(PhysicalMemoryManager.BlockSize, BLOCKS_PER_BYTE);
	PhysicalMemoryManager.MemoryStartAddress = ((uint32_t)PhysicalMemoryManager.BitmapAddress + PhysicalMemoryManager.BitmapSizeInBytes);

	// Mark of all with used flag.
	memset(PhysicalMemoryManager.BitmapAddress, 0x00, PhysicalMemoryManager.BitmapSizeInBytes);
}



/*
 *	author: egely1337
 *	purpose: Finds first free block.
 *	params: start_of_address (void*)
 */
uint32_t 	find_first_free_block(void) {
	int idx = 0;

	// Check for blocks.
	for(; idx < PhysicalMemoryManager.BlockSize; ++idx) {
		if(!ISSET(idx)) {
			terminal_print_string(itoa(idx));
			return idx;
		}
	}

	return (uint32_t)INVALID_BLOCK_HANDLE;
}


/*
 *	author: egely1337
 *	purpose: Allocates a block.
 */
uint32_t 	allocate_block() {
	uint32_t free_block = find_first_free_block();
	SETBIT(free_block);
	return free_block;
}


/*
 *	author: egely1337
 *	purpose: Frees a block.
 */
void 	free_block(uint32_t block) {
	CLEARBIT(block);
}