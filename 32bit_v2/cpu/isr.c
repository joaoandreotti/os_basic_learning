#include "isr.h"
#include "idt.h"
#include "../drivers/screen.h"
#include "../drivers/ports.h"

// isr is the interrupt service routine
// this means that first, will load a specific function address
// to the interrupt array that will be loaded using a asm function
// lidtl (so every interrut will have is own offset address) e.g.
// when a interrupt occurs it will go to the array position of the
// interrupt number
isr_t interrupt_handlers[256];

/* Can't do this with a loop because we need the address
 * of the function names */
void isr_install() {
  set_idt_gate(0, (uint32_t)isr0);
  set_idt_gate(1, (uint32_t)isr1);
  set_idt_gate(2, (uint32_t)isr2);
  set_idt_gate(3, (uint32_t)isr3);
  set_idt_gate(4, (uint32_t)isr4);
  set_idt_gate(5, (uint32_t)isr5);
  set_idt_gate(6, (uint32_t)isr6);
  set_idt_gate(7, (uint32_t)isr7);
  set_idt_gate(8, (uint32_t)isr8);
  set_idt_gate(9, (uint32_t)isr9);
  set_idt_gate(10, (uint32_t)isr10);
  set_idt_gate(11, (uint32_t)isr11);
  set_idt_gate(12, (uint32_t)isr12);
  set_idt_gate(13, (uint32_t)isr13);
  set_idt_gate(14, (uint32_t)isr14);
  set_idt_gate(15, (uint32_t)isr15);
  set_idt_gate(16, (uint32_t)isr16);
  set_idt_gate(17, (uint32_t)isr17);
  set_idt_gate(18, (uint32_t)isr18);
  set_idt_gate(19, (uint32_t)isr19);
  set_idt_gate(20, (uint32_t)isr20);
  set_idt_gate(21, (uint32_t)isr21);
  set_idt_gate(22, (uint32_t)isr22);
  set_idt_gate(23, (uint32_t)isr23);
  set_idt_gate(24, (uint32_t)isr24);
  set_idt_gate(25, (uint32_t)isr25);
  set_idt_gate(26, (uint32_t)isr26);
  set_idt_gate(27, (uint32_t)isr27);
  set_idt_gate(28, (uint32_t)isr28);
  set_idt_gate(29, (uint32_t)isr29);
  set_idt_gate(30, (uint32_t)isr30);
  set_idt_gate(31, (uint32_t)isr31);

  // PIC is numbered as [0x8-0xf] and [0x70-0x77]
  // remap the PIC
  //            port  data
  // 0x11 command means initialize command (wait for 3 initialize words
  // on the data port)
  // write 0x11 at master command port
  port_byte_out(0x20, 0x11);
  // write 0x11 at slave command port
  port_byte_out(0xA0, 0x11);

  // first word is the vector offset this means that
  // the master port will begin at 0x20(32) and the
  // slave will begin at 0x28(40)
  // write 0x20 at master data port
  port_byte_out(0x21, 0x20);
  // write 0x28 at slave data port
  port_byte_out(0xA1, 0x28);

  // second word tells how the devices are wired to the pic
  // 0x04 tells the master that there is a slave at position 2
  // 0x04 (0000 0100)
  // write 0x04 at master data port
  port_byte_out(0x21, 0x04);
  // 0x02 tells the slave that it is chained to master (cascade)
  // 0x02 (0000 0010)
  // write 0x28 at slave data port
  port_byte_out(0xA1, 0x02);

  // third word gives information about the environment
  // 0x01 means 8086 mode
  // write 0x01 at master data port
  port_byte_out(0x21, 0x01);
  // write 0x01 at slave data port
  port_byte_out(0xA1, 0x01);

  // this is to restore the saved masks
  // masks are used to ignore a certain interrupt, it is a 8bit number
  // that if the 3 bit is set, it will ignore that request
  // 0000 0001
  // so all bits are set to 0 right here
  // write 0x00 at master data port
  port_byte_out(0x21, 0x0);
  // write 0x00 at slave data port
  port_byte_out(0xA1, 0x0);

  // install the IRQs
  set_idt_gate(32, (uint32_t)irq0);
  set_idt_gate(33, (uint32_t)irq1);
  set_idt_gate(34, (uint32_t)irq2);
  set_idt_gate(35, (uint32_t)irq3);
  set_idt_gate(36, (uint32_t)irq4);
  set_idt_gate(37, (uint32_t)irq5);
  set_idt_gate(38, (uint32_t)irq6);
  set_idt_gate(39, (uint32_t)irq7);
  set_idt_gate(40, (uint32_t)irq8);
  set_idt_gate(41, (uint32_t)irq9);
  set_idt_gate(42, (uint32_t)irq10);
  set_idt_gate(43, (uint32_t)irq11);
  set_idt_gate(44, (uint32_t)irq12);
  set_idt_gate(45, (uint32_t)irq13);
  set_idt_gate(46, (uint32_t)irq14);
  set_idt_gate(47, (uint32_t)irq15);

  set_idt(); // Load with ASM
}

/* To print the message which defines every exception */
char *exception_messages [] = {
  "Division By Zero\0",
  "Debug\0",
  "Non Maskable Interrupt\0",
  "Breakpoint\0",
  "Into Detected Overflow\0",
  "Out of Bounds\0",
  "Invalid Opcode\0",
  "No Coprocessor\0",

  "Double Fault",
  "Coprocessor Segment Overrun\0",
  "Bad TSS\0",
  "Segment Not Present\0",
  "Stack Fault\0",
  "General Protection Fault\0",
  "Page Fault\0",
  "Unknown Interrupt\0",

  "Coprocessor Fault\0",
  "Alignment Check\0",
  "Machine Check\0",
  "Reserved\0",
  "Reserved\0",
  "Reserved\0",
  "Reserved\0",
  "Reserved\0",

  "Reserved\0",
  "Reserved\0",
  "Reserved\0",
  "Reserved\0",
  "Reserved\0",
  "Reserved\0",
  "Reserved\0",
  "Reserved\0"
};

void isr_handler (registers_t* r) {
  jprint ("received interrupt: \0");
  char str [10];
  int_to_string (r->int_no, str);
  jprint (str);
  jprint ("(\0");
  jprint (exception_messages[r->int_no]);
  jprint (")\n\0");
}

// add a function to the interrupt_handler vector
void register_interrupt_handler(uint8_t n, isr_t handler) {
  interrupt_handlers [n] = handler;
}

// send a end of interrupt to the PIC and call the specific
// function to handle the interrupt
void irq_handler (registers_t* r) {
  /* After every interrupt we need to send an EOI (end of interrupt) to the PICs
   * or they will not send another interrupt again */
  if (r->int_no >= 40)
    port_byte_out(0xA0, 0x20); /* slave */
  port_byte_out(0x20, 0x20); /* master */

  /* Handle the interrupt in a more modular way */
  if (interrupt_handlers [r->int_no] != 0) {
    isr_t handler = interrupt_handlers [r->int_no];
    handler (r);
  }
}
