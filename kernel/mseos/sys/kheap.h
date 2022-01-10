
#ifndef MSEOS_KHEAP_H
#define MSEOS_KHEAP_H

#include "sys/types.h"

void *kheap_alloc(uint32_t bytes);
void kheap_free(void *ptr);

#endif //MSEOS_KHEAP_H
