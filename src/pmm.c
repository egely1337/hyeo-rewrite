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


extern int KERNEL_START, KERNEL_END;

/* 
	Normally, multiboot 1.0 specification does not contain kernel space in its given memory mappings
	So, we need to calculate kernel space and contain its memory mapping.

	Logic:
		1. Calculate kernel space in memory
		2. Iterate BIOS memory map, find the biggest memory area.
		3. Start Physical Memory Manager
*/
/* TODO: Combine parse_mmap() and initialize_pmm() together. */
void parse_mmap(multiboot* multibootptr) {
	uint32_t kernel_start = (uint32_t)&KERNEL_START;
	uint32_t kernel_end   = (uint32_t)&KERNEL_END;
	uint32_t lenght = (uint32_t)kernel_end - kernel_start;

	void* mmap_end = (void*)multibootptr->mmap_addr + multibootptr->mmap_length;
	mmap_t* entry = (mmap_t*)multibootptr->mmap_addr;

	while(entry < mmap_end) {
		if(entry->type == 1) {
			printf("[kern] Type: %u Usable size: %u bytes, start: %x\n", entry->type, entry->len_low + entry->len_high, entry->addr_low + entry->addr_high);
		}

		entry = (mmap_t*)((uint32_t)entry + entry->size + 4);
	}

	/* printf("[kern] found region Size %u bytes, Address: %x\n", start->size, start->addr_low); */
}

/*
 *	author: egely1337
 *	purpose: initialize pmm
 *	params: start_of_address (void*)
 */
void initalize_pmm(
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
uint32_t find_first_free_block(void) {
	int idx = 0;

	// Check for blocks.
	for(; idx < PhysicalMemoryManager.BlockSize; ++idx) {
		if(!ISSET(idx)) {
			#ifdef DEBUG
			terminal_print_string(itoa(idx));
			#endif
			
			return idx;
		}
	}

	return (uint32_t)INVALID_BLOCK_HANDLE;
}

/* TODO: Alloc N free blocks. */
uint32_t allocnblocks(uint32_t n) {
	uint32_t idx = 0;
	uint32_t found = INVALID_BLOCK_HANDLE;

	for(; idx < PhysicalMemoryManager.BlockSize; ++idx) {
		if(!ISSET(idx)) {
			for(int j = idx+1; j < (idx+n) - 1; ++j) {
				if(ISSET(j)) break;

				if(j >= (idx+n-1)) {
					found = idx;
				}
			} 
		}	
	}

	return found;
}

/*
 *	author: egely1337
 *	purpose: Allocates a block.
 */
uint32_t alloc_block() {
	uint32_t free_block = find_first_free_block();
	SETBIT(free_block);
	return free_block;
}


/*
 *	author: egely1337
 *	purpose: Frees a block.
 */
void free_block(uint32_t block) {
	CLEARBIT(block);
}