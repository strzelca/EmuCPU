//
// Created by polina on 31/12/2023.
//

#include "mem.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

mem_t *new_mem(const uint8_t SIZE) {
    mem_t *mem = malloc(sizeof(mem_t));
    mem->mem = malloc(SIZE*sizeof(uint16_t));
    mem->size = SIZE;

    memset(mem->mem, 0, SIZE*sizeof(uint16_t));

    return mem;
}

void destroy_mem(mem_t *mem) {
    free(mem->mem);
    mem->mem = NULL;

    free(mem);
    mem = NULL;
}

void check_mem(const mem_t *mem) {
    printf("CHECK MEMORY\n");
    for (int i = 0; i < mem->size; i++)
        if (*(mem->mem+i) != 0) printf("Found 0x%04x at %p\n", *(mem->mem+i), mem->mem+i);

    printf("OK\n");
}