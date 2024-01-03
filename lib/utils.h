//
// Created by polina on 31/12/2023.
//

#ifndef UTILS_H
#define UTILS_H

#include "memory.h"

#define DESIGNATE(T, ...)  \
    memcpy(malloc(sizeof(T)),  \
    &(T const){ __VA_ARGS__ }, \
    sizeof(T))

#endif //UTILS_H
