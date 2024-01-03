#include <string.h>

#include "lib/logicb.h"
#include "lib/cpu.h"

int main() {
    logic_b_t *logicb = new_logicb();

    print_logicb(logicb);


    const uint16_t prog[] = {0x0001, 0xAFFF, 0x0008, 0x0002, 0xBFFF, 0xAFFF, 0x0008, 0x0003, 0xAFFF, 0xAFFF, 0x0009, 0x0002, 0xAFFF, 0xAFFF, 0x0001, 0xFAFB};

    memcpy(logicb->mem->mem, prog, sizeof(prog));


    check_mem(logicb->mem);
    start(logicb->cpu, logicb->mem);
    print_logicb(logicb);


    return destroy_logicb(logicb);
}
