//
// Created by polina on 31/12/2023.
//

#ifndef ISA_H
#define ISA_H

#include <stdint.h>

#define REGA 0xAFFF
#define REGB 0xBFFF

#define MOV 0x0001
#define ADD 0x0002
#define SUB 0x0003
#define MUL 0x0004
#define DIV 0x0005
#define INC 0x0006

#define HLT 0xFAFB
#define NUL 0x0000


void _MOV(uint16_t *restrict dst, uint16_t _n);
void _ADD(uint16_t *restrict dst, const uint16_t *restrict v1, const uint16_t *restrict v2, uint32_t *restrict flags);
void _SUB(uint16_t *restrict dst, const uint16_t *restrict v1, uint16_t *restrict v2, uint32_t *restrict flags);
void _MUL(uint16_t *restrict dst, const uint16_t *restrict v1, uint16_t *restrict v2, uint32_t *restrict flags);
void _DIV(uint16_t *restrict dst, uint16_t *restrict v1, uint16_t *restrict v2, uint32_t *restrict flags);
void _INC(uint16_t *restrict dst, uint32_t *restrict flags);


#endif //ISA_H
