#include <string.h>

#include "lib/logicb.h"
#include "lib/cpu.h"
#include "lib/isa.h"

int main() {
    logic_b_t *logicb = new_logicb();

    print_logicb(logicb);


    const uint16_t prog[] = {
        ADD, REGA, REGA, 0x0008, 
        DIV, REGB, REGA, 0x0004, 
        SUB, REGA, REGA, 0x0004, 
        ADD, REGA, REGA, 0x0008,
        0xFAFB
    };

    memcpy(logicb->mem->mem, prog, sizeof(prog));


    check_mem(logicb->mem);
    start(logicb->cpu, logicb->mem);
    print_logicb(logicb);


    return destroy_logicb(logicb);
}
