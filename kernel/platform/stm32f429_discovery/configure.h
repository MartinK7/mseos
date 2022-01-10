
#ifndef CONFIGURE_H
#define CONFIGURE_H

// Minimum stack size for kernelspace (in words)
#define CONFIG_KSTACK_SIZE (64*1024/4)

// Minimum heap size for kernelspace (in words)
#define CONFIG_KHEAP_SIZE  (64*1024/4)

// Maximum kernel allocations
#define CONFIG_KHEAP_MAX_ALLOCS 64

// Minimum heap size for userspace (in words)
// There will be placed all executables and allocated data
#define CONFIG_UHEAP_SIZE  (8*1024*1024/4)

#endif // CONFIGURE_H

