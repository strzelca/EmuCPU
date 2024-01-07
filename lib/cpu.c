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
    printf("CPU STATUS\n");
    printf("A  -> 0x%04x (%hi)\n", cpu->a, cpu->a);
    printf("B  -> 0x%04x (%hi)\n", cpu->b, cpu->b);
    printf("pc -> 0x%04x\n", cpu->pc);
    printf("SP -> 0x%04x\n", cpu->sp);
    printf("BP -> 0x%04x\n", cpu->bp);
    printf("FLAGS -> 0x%08x\n", cpu->flags.flags);
}

void illegal_instruction(const cpu_t *cpu, const mem_t *mem) {
    printf("Illegal instruction format\n");
    printf("DUMP\n");
    printf("--------------------------\n");
    print_cpu_status(cpu);
    printf("--------------------------\n");
    for(int i = -2; i <= 2; i++)
        if(cpu->pc-1+i >= 0) {
            if(i == 0) printf("0x%04x : 0x%04x <--\n", cpu->pc-1+i, mem->mem[cpu->pc-1+i]);
            else printf("0x%04x : 0x%04x\n", cpu->pc-1+i, mem->mem[cpu->pc-1+i]);
        }

    exit(1);
}

void fde(cpu_t *cpu, mem_t *mem) {
    uint16_t *R1 = NULL;
    uint16_t *R2 = NULL;
    uint16_t *R3 = NULL;
    uint16_t V1 = 0;
    uint16_t V2 = 0;
    if (cpu->pc > mem->size) illegal_instruction(cpu, mem);
    switch(mem->mem[cpu->pc++]) {
        case MOV:
            switch (mem->mem[cpu->pc++]) {
                case RA:
                    R1 = &cpu->a;
                break;
                case RB:
                    R1 = &cpu->b;
                break;
                case SP:
                    R1 = &cpu->sp;
                break;
                case BP:
                    R1 = &cpu->bp;
                break;
                default:
                    illegal_instruction(cpu, mem);
                break;
            }
            switch (mem->mem[cpu->pc++]) {
                case RA:
                    V1 = cpu->a;
                break;
                case RB:
                    V1 = cpu->b;
                break;
                case SP:
                    V1 = cpu->sp;
                break;
                case BP:
                    V1 = cpu->bp;
                break;
                default:
                    V1 = mem->mem[cpu->pc-1];
                break;
            }
            _MOV(R1, V1);
        break;
        case ADD:
            // reg, v1, v2
            switch (mem->mem[cpu->pc++]) {
                case RA:
                    R1 = &cpu->a;
                break;
                case RB:
                    R1 = &cpu->b;
                break;
                case SP:
                    R1 = &cpu->sp;
                break;
                case BP:
                    R1 = &cpu->bp;
                break;
                default:
                    illegal_instruction(cpu, mem);
                break;
            }
            switch (mem->mem[cpu->pc++]) {
                case RA:
                    R2 = &cpu->a;
                break;
                case RB:
                    R2 = &cpu->b;
                break;
                case SP:
                    R2 = &cpu->sp;
                break;
                case BP:
                    R2 = &cpu->bp;
                break;
                default:
                    V1 = mem->mem[cpu->pc-1];
                    R2 = &V1;
                break;
            }
            switch (mem->mem[cpu->pc++]) {
                case RA:
                    R3 = &cpu->a;
                break;
                case RB:
                    R3 = &cpu->b;
                break;
                case SP:
                    R3 = &cpu->sp;
                break;
                case BP:
                    R3 = &cpu->bp;
                break;
                default:
                    V2 = mem->mem[cpu->pc-1];
                    R3 = &V2;
                break;
            }
            _ADD(R1, R2, R3, (uint32_t*) &cpu->flags);
        break;
        case SUB:
            // reg, v1, v2
            switch (mem->mem[cpu->pc++]) {
                case RA:
                    R1 = &cpu->a;
                break;
                case RB:
                    R1 = &cpu->b;
                break;
                case SP:
                    R1 = &cpu->sp;
                break;
                case BP:
                    R1 = &cpu->bp;
                break;
                default:
                    illegal_instruction(cpu, mem);
                break;
            }
            switch (mem->mem[cpu->pc++]) {
                case RA:
                    R2 = &cpu->a;
                break;
                case RB:
                    R2 = &cpu->b;
                break;
                case SP:
                    R2 = &cpu->sp;
                break;
                case BP:
                    R2 = &cpu->bp;
                break;
                default:
                    V1 = mem->mem[cpu->pc-1];
                    R2 = &V1;
                break;
            }
            switch (mem->mem[cpu->pc++]) {
                case RA:
                    R3 = &cpu->a;
                break;
                case RB:
                    R3 = &cpu->b;
                break;
                case SP:
                    R3 = &cpu->sp;
                break;
                case BP:
                    R3 = &cpu->bp;
                break;
                default:
                    V2 = mem->mem[cpu->pc-1];
                    R3 = &V2;
                break;
            }
            _SUB(R1, R2, R3, (uint32_t*) &cpu->flags);
        break;
        case MUL:
            // reg, v1, v2
            switch (mem->mem[cpu->pc++]) {
                case RA:
                    R1 = &cpu->a;
                break;
                case RB:
                    R1 = &cpu->b;
                break;
                case SP:
                    R1 = &cpu->sp;
                break;
                case BP:
                    R1 = &cpu->bp;
                break;
                default:
                    illegal_instruction(cpu, mem);
                break;
            }
            switch (mem->mem[cpu->pc++]) {
                case RA:
                    R2 = &cpu->a;
                break;
                case RB:
                    R2 = &cpu->b;
                break;
                case SP:
                    R2 = &cpu->sp;
                break;
                case BP:
                    R2 = &cpu->bp;
                break;
                default:
                    V1 = mem->mem[cpu->pc-1];
                    R2 = &V1;
                break;
            }
            switch (mem->mem[cpu->pc++]) {
                case RA:
                    R3 = &cpu->a;
                break;
                case RB:
                    R3 = &cpu->b;
                break;
                case SP:
                    R3 = &cpu->sp;
                break;
                case BP:
                    R3 = &cpu->bp;
                break;
                default:
                    V2 = mem->mem[cpu->pc-1];
                    R3 = &V2;
                break;
            }
            _MUL(R1, R2, R3, (uint32_t*) &cpu->flags);
        break;
        case DIV:
            // reg, v1, v2
            switch (mem->mem[cpu->pc++]) {
                case RA:
                    R1 = &cpu->a;
                break;
                case RB:
                    R1 = &cpu->b;
                break;
                case SP:
                    R1 = &cpu->sp;
                break;
                case BP:
                    R1 = &cpu->bp;
                break;
                default:
                    illegal_instruction(cpu, mem);
                break;
            }
            switch (mem->mem[cpu->pc++]) {
                case RA:
                    R2 = &cpu->a;
                break;
                case RB:
                    R2 = &cpu->b;
                break;
                case SP:
                    R2 = &cpu->sp;
                break;
                case BP:
                    R2 = &cpu->bp;
                break;
                default:
                    V1 = mem->mem[cpu->pc-1];
                    R2 = &V1;
                break;
            }
            switch (mem->mem[cpu->pc++]) {
                case RA:
                    R3 = &cpu->a;
                break;
                case RB:
                    R3 = &cpu->b;
                break;
                case SP:
                    R3 = &cpu->sp;
                break;
                case BP:
                    R3 = &cpu->bp;
                break;
                default:
                    V2 = mem->mem[cpu->pc-1];
                    R3 = &V2;
                break;
            }
            _DIV(R1, R2, R3, (uint32_t*) &cpu->flags);
        break;
        case PUSH:
            // push r1
            switch (mem->mem[cpu->pc++]) {
                case RA:
                    R1 = &cpu->a;
                break;
                case RB:
                    R1 = &cpu->b;
                break;
                case SP:
                    R1 = &cpu->sp;
                break;
                case BP:
                    R1 = &cpu->bp;
                break;
                default:
                    illegal_instruction(cpu, mem);
                break;
            }
            switch (_PUSH(R1, &cpu->bp, mem)) {
            case 0:
                break;
            default:
                illegal_instruction(cpu, mem);
                break;
            }
        break;
        case POP:
            // push r1
            switch (mem->mem[cpu->pc++]) {
                case RA:
                    R1 = &cpu->a;
                break;
                case RB:
                    R1 = &cpu->b;
                break;
                case SP:
                    R1 = &cpu->sp;
                break;
                case BP:
                    R1 = &cpu->bp;
                break;
                default:
                    illegal_instruction(cpu, mem);
                break;
            }
            switch (_POP(R1, &cpu->bp, mem)){
            case 0:
                break;
            default:
                    illegal_instruction(cpu, mem);
                break;
            }
        break;
        case ALIGN:
            // push r1
            switch (mem->mem[cpu->pc++]) {
                case RA:
                    R1 = &cpu->a;
                break;
                case RB:
                    R1 = &cpu->b;
                break;
                case SP:
                    R1 = &cpu->sp;
                break;
                case BP:
                    R1 = &cpu->bp;
                break;
                default:
                    illegal_instruction(cpu, mem);
                break;
            }
            _ALIGN(R1, mem);
        break;
        case NUL:
            illegal_instruction(cpu, mem);
            break;
        default:
            illegal_instruction(cpu, mem);
            break;
    }
}



void start(cpu_t *cpu, const mem_t *mem) {
    while (mem->mem[cpu->pc] != HLT || mem->mem[cpu->pc] == NUL) {
        fde(cpu, mem);
    }
}