#ifndef FAT_H
#define FAT_H

#include <typedefs.h>

typedef struct {
	uint8_t BootRecord[3]; // EB 3C 90
	uint8_t OemIdentifier[8];
	uint16_t BytesPerSector;
	uint8_t SectorsPerCluster;
	uint8_t ReservedSectors;
	uint8_t NumberOfFat;
	uint16_t NumberOfRootDirectory;
	uint16_t TotalSectors; // if 0, large sectors
	uint8_t Reserved[7];
	uint16_t LargeTotalSectors;
} boot_record_t;

typedef struct {

} directory_entry_t;

#endif