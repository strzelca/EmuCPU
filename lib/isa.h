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
#define HLT 0xFAFB
#define NUL 0x0000


void _MOV(uint16_t* dst, uint16_t _n);
void _ADD(uint16_t* dst, const uint16_t *v1, const uint16_t *v2);

#endif //ISA_H
