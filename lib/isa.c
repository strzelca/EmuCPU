//
// Created by polina on 31/12/2023.
//

#include "isa.h"

#include <stdint.h>
#include <stdio.h>

void _MOV(uint16_t* dst, const uint16_t _n) {
    *dst = _n;
}

void _ADD(uint16_t* dst, const uint16_t *v1, const uint16_t *v2, uint32_t *flags) {
    *flags = 0;
    *flags = *v1 & *v2;
    *dst = *v1 ^ *v2;


    while (*flags != 0){
        uint32_t carry = *flags << 1;
        *flags = *dst & carry;
        *dst = *dst ^ carry;
    }

    if (*dst <= *v2 && ~*v2 < *v2 ) *flags ^= 1 << 0x8;

    if (*dst >> 15 == 1) *flags ^= 1 << 0x10;

    if (*dst == 0) *flags ^= 1 << 0x100;
    
}

void _SUB(uint16_t* dst, const uint16_t *v1, uint16_t *v2, uint32_t *flags) {
    *v2 = ~*v2 + 1;
    _ADD(dst, v1, v2, flags);
}