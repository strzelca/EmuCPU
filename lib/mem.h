//
// Created by polina on 31/12/2023.
//

#ifndef MEM_H
#define MEM_H

#include <stdint.h>

typedef struct _mem {
    uint16_t *mem;
    uint8_t size;
} mem_t;

mem_t *new_mem(uint8_t SIZE);
void destroy_mem(mem_t *mem);
void check_mem(const mem_t *mem);

#endif //MEM_H
