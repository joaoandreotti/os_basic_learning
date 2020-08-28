#include "../drivers/screen.c"
#include "../drivers/ports.c"
#include "../cpu/isr.c"
#include "../cpu/idt.c"

void main () {
  // memory address of the VGA
  isr_install ();
  set_cursor_position (0);
  clear_screen ();


  for (int i = 0; i < 1000; i++)
    if (i % 2)
      jprint ("CAROLINA\n\0");
    else
      jprint ("JAMES\n\0");

  __asm__ __volatile__("int $3");

  //for (int i = 0; i < (MAX_ROWS * MAX_COLUMNS * 2); i += 2)
    //jprint ("j\0", WHITE_ON_BLACK);
}
