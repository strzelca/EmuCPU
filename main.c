#include <string.h>

#include "lib/logicb.h"
#include "lib/cpu.h"
#include "lib/isa.h"

int main() {
    logic_b_t *logicb = new_logicb();

    const uint16_t prog[] = {
        ALIGN, SP,
        MOV, BP, SP,
        SUB, BP, BP, 0x0004,
        ADD, RA, RA, 0x0008, 
        DIV, RB, RA, 0x0004,
        MUL, RB, RB, 0x0002,
        PUSH, RB,
        SUB, RA, RA, RB,
        PUSH, RA,
        POP, RB,
        0xFAFB
    };

    memcpy(logicb->mem->mem, prog, sizeof(prog));

    start(logicb->cpu, logicb->mem);
    print_logicb(logicb);


    return destroy_logicb(logicb);
}
