
#ifndef MSEOS_MEMOPS_H
#define MSEOS_MEMOPS_H

#include "sys/types.h"

void memcpy(void *dest, const void *src, uint32_t n);
void *memset(void *ptr, int value, uint32_t num);

#endif //MSEOS_MEMOPS_H
