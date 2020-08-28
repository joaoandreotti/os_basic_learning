#include "keyboard.h"

static void keyboard_callback (registers_t* regs) {
  /* The PIC leaves us the scancode in port 0x60 */
  uint8_t scancode = port_byte_in (0x60);
  char sc_ascii [10];
  int_to_string ((int)scancode, sc_ascii);
  jprint ("Keyboard interrupt: \0");
  jprint (sc_ascii);
  jprint (", \0");
  print_letter (scancode);
  jprint ("\n\0");
}

void init_keyboard() {
  // set the function to the interrupt vector handler
  jprint ("INITIALIZING THE KEYBOARD DRIVER\n");
  register_interrupt_handler (IRQ1, keyboard_callback); 
}

void print_letter(uint8_t scancode) {
  switch (scancode) {
    case 0x0:
      jprint("ERROR\0");
      break;
    case 0x1:
      jprint("ESC\0");
      break;
    case 0x2:
      jprint("1\0");
      break;
    case 0x3:
      jprint("2\0");
      break;
    case 0x4:
      jprint("3\0");
      break;
    case 0x5:
      jprint("4\0");
      break;
    case 0x6:
      jprint("5\0");
      break;
    case 0x7:
      jprint("6\0");
      break;
    case 0x8:
      jprint("7\0");
      break;
    case 0x9:
      jprint("8\0");
      break;
    case 0x0A:
      jprint("9\0");
      break;
    case 0x0B:
      jprint("0\0");
      break;
    case 0x0C:
      jprint("-\0");
      break;
    case 0x0D:
      jprint("+\0");
      break;
    case 0x0E:
      jprint("Backspace\0");
      break;
    case 0x0F:
      jprint("Tab\0");
      break;
    case 0x10:
      jprint("Q\0");
      break;
    case 0x11:
      jprint("W\0");
      break;
    case 0x12:
      jprint("E\0");
      break;
    case 0x13:
      jprint("R\0");
      break;
    case 0x14:
      jprint("T\0");
      break;
    case 0x15:
      jprint("Y\0");
      break;
    case 0x16:
      jprint("U\0");
      break;
    case 0x17:
      jprint("I\0");
      break;
    case 0x18:
      jprint("O\0");
      break;
    case 0x19:
      jprint("P\0");
      break;
    case 0x1A:
      jprint("[\0");
      break;
    case 0x1B:
      jprint("]\0");
      break;
    case 0x1C:
      jprint("ENTER\0");
      break;
    case 0x1D:
      jprint("LCtrl\0");
      break;
    case 0x1E:
      jprint("A\0");
      break;
    case 0x1F:
      jprint("S\0");
      break;
    case 0x20:
      jprint("D\0");
      break;
    case 0x21:
      jprint("F\0");
      break;
    case 0x22:
      jprint("G\0");
      break;
    case 0x23:
      jprint("H\0");
      break;
    case 0x24:
      jprint("J\0");
      break;
    case 0x25:
      jprint("K\0");
      break;
    case 0x26:
      jprint("L\0");
      break;
    case 0x27:
      jprint(";\0");
      break;
    case 0x28:
      jprint("'\0");
      break;
    case 0x29:
      jprint("`\0");
      break;
    case 0x2A:
      jprint("LShift\0");
      break;
    case 0x2B:
      jprint("\\\0");
      break;
    case 0x2C:
      jprint("Z\0");
      break;
    case 0x2D:
      jprint("X\0");
      break;
    case 0x2E:
      jprint("C\0");
      break;
    case 0x2F:
      jprint("V\0");
      break;
    case 0x30:
      jprint("B\0");
      break;
    case 0x31:
      jprint("N\0");
      break;
    case 0x32:
      jprint("M\0");
      break;
    case 0x33:
      jprint(",\0");
      break;
    case 0x34:
      jprint(".\0");
      break;
    case 0x35:
      jprint("/\0");
      break;
    case 0x36:
      jprint("Rshift\0");
      break;
    case 0x37:
      jprint("Keypad *\0");
      break;
    case 0x38:
      jprint("LAlt\0");
      break;
    case 0x39:
      jprint("Spc\0");
      break;
    default:
      /* 'keuyp' event corresponds to the 'keydown' + 0x80 
       * it may still be a scancode we haven't implemented yet, or
       * maybe a control/escape sequence */
      if (scancode <= 0x7f) {
        //jprint("Unknown key down\0");
      } else if (scancode <= 0x39 + 0x80) {
        //jprint("key up \0");
        //print_letter(scancode - 0x80);
      } else; //jprint("Unknown key up\0");
      break;
  }
}
