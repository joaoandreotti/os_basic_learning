#include "idt.h"

// the idt is basically an array that is composed by 256 position
// and each position is a struct type called by idt_gate_t and
// it is composed by a set of flags and function address.
// each function will be a resolution function to a specific interrupt
// and its control flags will be the same

// n == array pos, handler == function address
void set_idt_gate(int n, uint32_t handler) {
    idt[n].low_offset = low_16(handler);
    idt[n].sel = KERNEL_CS;
    idt[n].always0 = 0;
    idt[n].flags = 0b10001110; 
    idt[n].high_offset = high_16(handler);
}

void set_idt() {
    idt_reg.base = (uint32_t) &idt;
    idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;

    /* Don't make the mistake of loading &idt -- always load &idt_reg */
    __asm__ __volatile__("lidtl (%0)" : : "r" (&idt_reg));
}
