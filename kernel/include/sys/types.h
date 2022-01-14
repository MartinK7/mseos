#ifndef TYPES_H
#define TYPES_H

typedef __UINT8_TYPE__ uint8_t;
typedef __UINT16_TYPE__ uint16_t;
typedef __UINT32_TYPE__ uint32_t;
typedef __UINT64_TYPE__ uint64_t;
typedef __INT8_TYPE__ int8_t;
typedef __INT16_TYPE__ int16_t;
typedef __INT32_TYPE__ int32_t;
typedef __INT64_TYPE__ int64_t;

#ifndef NULL
#define NULL ((void*)(0))
#endif // NULL

typedef int8_t error_t;
#define ERROR_NO_ERROR      ( 0)
#define ERROR_OUT_OF_MEMORY (-1)

#endif // TYPES_H

