/*
   This is an alternative for the old writeData that was made by HackJack & Razzile
*/

#include "writeData.hpp"
#include "MemoryPatch.hpp"
#include <libkern/_OSByteOrder.h>

static bool isWritableAddress(const char *fileName, uintptr_t offset, size_t size)
{
	uintptr_t address = KittyMemory::getAbsoluteAddress(fileName, offset);
	if (address == 0 || size == 0)
		return false;

	vm_region_submap_short_info_64 pageInfo;
	void *pageStart = reinterpret_cast<void *>(_PAGE_START_OF_(address));
	if (KittyMemory::getPageInfo(pageStart, &pageInfo) != KERN_SUCCESS)
		return false;

	return (pageInfo.protection & VM_PROT_WRITE) != 0;
}

bool writeData8(const char *fileName, uintptr_t offset, uint8_t data)
{
	return MemoryPatch(fileName, /* relative address */ offset, /* patch bytes */ &data, /* patch bytes length */ 1).Modify();
}

bool writeData16(const char *fileName, uintptr_t offset, uint16_t data)
{
	data = _OSSwapInt16(data);
	return MemoryPatch(fileName, /* relative address */ offset, /* patch bytes */ &data, /* patch bytes length */ 2).Modify();
}

bool writeData32(const char *fileName, uintptr_t offset, uint32_t data)
{
	if (!isWritableAddress(fileName, offset, sizeof(data)))
		return false;

	return MemoryPatch(fileName, /* relative address */ offset, /* patch bytes */ &data, /* patch bytes length */ 4).Modify();
}

bool writeData64(const char *fileName, uintptr_t offset, uint64_t data)
{
	data = _OSSwapInt64(data);
	return MemoryPatch(fileName, /* relative address */ offset, /* patch bytes */ &data, /* patch bytes length */ 8).Modify();
}
