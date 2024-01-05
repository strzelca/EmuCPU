//
// Created by polina on 31/12/2023.
//

#include "isa.h"

#include <stdint.h>
#include <stdio.h>

void _MOV(uint16_t *restrict dst, const uint16_t _n) {
    *dst = _n;
}

void _ADD(uint16_t *restrict dst, const uint16_t *restrict v1, const uint16_t *restrict v2, uint32_t *restrict flags) {
    uint16_t _v1 = *v1;
    *flags = 0;
    *flags = *v1 & *v2;
    *dst = *v1 ^ *v2;

    while (*flags != 0){
        uint32_t carry = *flags << 1;
        *flags = *dst & carry;
        *dst = *dst ^ carry;
    }

    if(*dst > 0 && *dst < 0x7FFF && _v1 > 0x7FFF) *flags ^= 1 << 0x8;
    
    if (*dst == 0) *flags ^= 1 << 0x18;
    
}

void _INC(uint16_t *restrict dst, uint32_t *restrict flags) {
    uint16_t _d = *dst;
    *flags = 0;
    *flags = *dst & 1;
    *dst = *dst ^ 1;

    while (*flags != 0){
        uint32_t carry = *flags << 1;
        *flags = *dst & carry;
        *dst = *dst ^ carry;
    }

    if (*dst > 0 && *dst < 0x7FFF && _d > 0x7FFF) *flags ^= 1 << 0x8;
    if (*dst >> 15) *flags ^= 1 << 0x10;
    if (!*dst) *flags ^= 1 << 0x18;
}

void _SUB(uint16_t *restrict dst, const uint16_t *restrict v1, uint16_t *restrict v2, uint32_t *restrict flags) {
    uint16_t _v2 = ~*v2 + 1;
    _ADD(dst, v1, &_v2, flags);
}

void _MUL(uint16_t *restrict dst, const uint16_t *restrict v1, uint16_t *restrict v2, uint32_t *restrict flags) {
    while((*v2)--) _ADD(dst, dst, v1, flags);
}

void _DIV(uint16_t *restrict dst, uint16_t *restrict v1, uint16_t *restrict v2, uint32_t *restrict flags) {
    uint32_t _save_flags;
    while(*v1 > 0 && *v1 < 0x7FFF || ((*flags >> 0x10) & 0x001) == 1 && (*flags >> 0x18) == 1) {
        _SUB(v1, v1, v2, flags);
        _save_flags = *flags;
        _INC(dst, flags);
        *flags = _save_flags;
    }
}