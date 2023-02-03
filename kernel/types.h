#ifndef KERNEL_TYPES_H
#define KERNEL_TYPES_H

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;

struct gdt {
    uint32_t address;
    uint16_t size;
} __attribute__((packed));

#endif /* KERNEL_TYPES_H */
