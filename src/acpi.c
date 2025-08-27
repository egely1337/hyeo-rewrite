#include <acpi.h>
#include <string.h>
#include <terminal.h>

fadt_t* FADT;

struct RSDPHeader* find_rsdp() {
    for(uint32_t addr = ACPI_BIOS_MEMORY_START; addr < ACPI_BIOS_MEMORY_END; addr += 16) {
        struct RSDPHeader* header = (struct RSDPHeader*)addr;
        if(!memcmp(header->signature, "RSD PTR ", 8)) {
            return header;
        }
    }

    return null;
}

fadt_t* find_fadt(struct RSDPHeader* rsdp) {
    struct ACPISDTHeader* sdtp = (struct ACPISDTHeader*)rsdp->rsdt_address;
    int entries = (sdtp->Length - sizeof(struct ACPISDTHeader)) / 4;
    uint32_t* pointers = (uint32_t*)((uintptr_t)sdtp + sizeof(struct ACPISDTHeader));

    for(int i = 0; i < entries; i++) {
        struct ACPISDTHeader* header = (struct ACPISDTHeader*)(uintptr_t)pointers[i];
        if (!memcmp(header->Signature, "FACP", 4)) {
            return (fadt_t*)header;
        }
    }

    return null;
}

void acpi_init() {
    struct RSDPHeader* rsdp = find_rsdp();
    HYEO_ASSERT(rsdp && "RSDP address is zero.");
    FADT = find_fadt(rsdp);
    HYEO_ASSERT(FADT && "FADT address is zero.");
}