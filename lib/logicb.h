//
// Created by polina on 31/12/2023.
//

#ifndef LOGICB_H
#define LOGICB_H

#include "mem.h"
#include "cpu.h"

typedef struct _logicb {
    cpu_t *cpu;
    mem_t *mem;
} logic_b_t;

logic_b_t *new_logicb();
uint8_t destroy_logicb(logic_b_t *logicb);
void print_logicb(const logic_b_t *logicb);

#endif //LOGICB_H
