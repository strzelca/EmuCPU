//
// Created by polina on 31/12/2023.
//

#include "logicb.h"

#include <stdlib.h>

#include "cpu.h"
#include "mem.h"

logic_b_t *new_logicb() {
    logic_b_t *logicb = malloc(sizeof(logic_b_t));
    logicb->cpu = new_cpu();
    logicb->mem = new_mem(64);

    return logicb;
}

uint8_t destroy_logicb(logic_b_t *logicb) {
    destroy_cpu(logicb->cpu);
    destroy_mem(logicb->mem);
    free(logicb);
    logicb = NULL;

    return 0;
}

void print_logicb(const logic_b_t *logicb) {
    print_cpu_status(logicb->cpu);
    check_mem(logicb->mem);
}