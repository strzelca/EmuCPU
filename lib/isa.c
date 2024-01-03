//
// Created by polina on 31/12/2023.
//

#include "isa.h"

#include <stdint.h>

void _MOV(uint16_t* dst, const uint16_t _n) {
    *dst = _n;
}

void _ADD(uint16_t* dst, const uint16_t *v1, const uint16_t *v2) {
    *dst = *v1 + *v2;
}