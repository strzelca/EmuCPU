//
// Created by polina on 31/12/2023.
//

#ifndef CPU_H
#define CPU_H

#include <stdint.h>

#include "mem.h"

typedef struct _cpu {
      uint16_t A;
      uint16_t B;
      uint16_t PC;
} cpu_t;

cpu_t *new_cpu();
void destroy_cpu(cpu_t *cpu);
void print_cpu_status(const cpu_t *cpu);
void start(cpu_t *cpu, const mem_t *mem);

#endif //CPU_H
