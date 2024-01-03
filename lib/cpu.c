//
// Created by polina on 31/12/2023.
//

#include "cpu.h"

#include <stdlib.h>
#include <stdio.h>

#include "isa.h"
#include "logicb.h"
#include "utils.h"

cpu_t *new_cpu() {
    cpu_t *cpu = malloc(sizeof(cpu_t));
    memset(cpu, 0, sizeof(cpu_t));
    return cpu;
}

void destroy_cpu(cpu_t *cpu) {
    free(cpu);
    cpu = NULL;
}


void print_cpu_status(const cpu_t *cpu) {
    printf_s("CPU STATUS\n");
    printf_s("A  -> 0x%04x\n", cpu->A);
    printf_s("B  -> 0x%04x\n", cpu->B);
    printf_s("PC -> 0x%04x\n", cpu->PC);
}

void illegal_instruction(const cpu_t *cpu, const mem_t *mem) {
    printf_s("Illegal instruction format\n");
    printf_s("DUMP\n");
    printf_s("--------------------------\n");
    print_cpu_status(cpu);
    printf_s("--------------------------\n");
    for(int i = -2; i <= 2; i++)
        if(cpu->PC-1+i >= 0) {
            if(i == 0) printf_s("0x%04x : 0x%04x <--\n", cpu->PC-1+i, mem->mem[cpu->PC-1+i]);
            else printf_s("0x%04x : 0x%04x\n", cpu->PC-1+i, mem->mem[cpu->PC-1+i]);
        }

    exit(1);
}

void fde(cpu_t *cpu, const mem_t *mem) {
    uint16_t *R1 = malloc(sizeof(uint16_t));
    uint16_t *R2 = malloc(sizeof(uint16_t));
    uint16_t *R3 = malloc(sizeof(uint16_t));
    uint16_t V1 = 0;
    if (cpu->PC > mem->size) illegal_instruction(cpu, mem);
    switch(mem->mem[cpu->PC++]) {
        case MOV:
            switch (mem->mem[cpu->PC++]) {
                case REGA:
                    R1 = &cpu->A;
                break;
                case REGB:
                    R1 = &cpu->B;
                break;
                default:
                    illegal_instruction(cpu, mem);
                break;
            }
            switch (mem->mem[cpu->PC++]) {
                case REGA:
                    V1 = cpu->A;
                break;
                case REGB:
                    V1 = cpu->B;
                break;
                default:
                    V1 = cpu->PC-1;
                break;
            }
            _MOV(R1, V1);
        break;
        case ADD:
            // reg, v1, v2
            switch (mem->mem[cpu->PC++]) {
                case REGA:
                    R1 = &cpu->A;
                break;
                case REGB:
                    R1 = &cpu->B;
                break;
                default:
                    illegal_instruction(cpu, mem);
                break;
            }
            switch (mem->mem[cpu->PC++]) {
                case REGA:
                    R2 = &cpu->A;
                break;
                case REGB:
                    R2 = &cpu->B;
                break;
                default:
                    *R2 = cpu->PC-1;
                break;
            }
            switch (mem->mem[cpu->PC++]) {
                case REGA:
                    R3 = &cpu->A;
                break;
                case REGB:
                    R3 = &cpu->B;
                break;
                default:
                    *R3 = cpu->PC-1;
                break;
            }
            _ADD(R1, R2, R3);
        break;
        case NUL:
            illegal_instruction(cpu, mem);
            break;
        default:
            illegal_instruction(cpu, mem);
            break;
    }

    free(R1);
    free(R2);
    free(R3);
}



void start(cpu_t *cpu, const mem_t *mem) {
    while (mem->mem[cpu->PC] != HLT || mem->mem[cpu->PC] == NUL) {
        fde(cpu, mem);
    }
}