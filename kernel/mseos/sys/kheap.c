
#include "kheap.h"
#include "configure.h"

static uint32_t __attribute__((section(".kheap"))) _kheap[CONFIG_KHEAP_SIZE];

static uint32_t pos = 0;

void *kheap_alloc(uint32_t bytes)
{
	uint32_t words = (bytes >> 2) + (bytes & 0x03UL ? 1 : 0);
	uint32_t new = pos + words;
	if(new >= CONFIG_KHEAP_SIZE)
		return NULL;
	void *ret = &_kheap[pos];
	pos = new;
	return ret;
}

void kheap_free(void *ptr)
{
	// TODO
}
