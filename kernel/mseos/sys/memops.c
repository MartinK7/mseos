
#include "memops.h"

void *memcpy(void *dest, const void *src, uint32_t n)
{
	// Typecast src and dest addresses to (char *)
	char *csrc = (char *)src;
	char *cdest = (char *)dest;

	// Copy contents of src[] to dest[]
	for (int i=0; i<n; i++)
		cdest[i] = csrc[i];

	return dest;
}

void *memset(void *ptr, int value, uint32_t num)
{
	char *cdest = (char *)ptr;

	for (int i=0; i<num; i++)
		cdest[i] = value;

	return ptr;
}
