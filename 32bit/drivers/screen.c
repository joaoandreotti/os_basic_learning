#include "screen.h"
#include "ports.h"


int get_cursor_position () {
  int offset = 0;
  // we tell the device port to set its pointer to the
  // high order byte of the cursor offset (14)
  port_byte_out (SCREEN_PORT_CONTROL, 14);
  // shift 8 because its high order
  offset = (int)port_byte_in (SCREEN_PORT_DATA) << 8;

  // we tell the device port to set its pointer to the
  // low order byte of the cursor offset (15)
  port_byte_out (SCREEN_PORT_CONTROL, 15);
  offset += port_byte_in (SCREEN_PORT_DATA);

  return offset;
}

void set_cursor_position (int offset) {
  // basically the same thing as before
  port_byte_out (SCREEN_PORT_CONTROL, 14);
  // write the data of the high order cursor position
  // shift left to just get the high order bits
  port_byte_out (SCREEN_PORT_DATA, offset >> 8);

  // basically the same thing as before
  port_byte_out (SCREEN_PORT_CONTROL, 15);
  // write the data of the low order cursor position
  // here we set everthing else to 0 so no problem can occur
  port_byte_out (SCREEN_PORT_DATA, offset & 0xff);
}

void scroll_screen () {
  unsigned char* position = (unsigned char*) VGA_ADDRESS;

  for (int i = 0; i < MAX_ROWS - 1; i++) {
    for (int j = 0; j < MAX_COLUMNS; j++) {
      *position = *(position + (MAX_COLUMNS * 2));
      position += 2;
    }
  }

  position = (unsigned char*) (VGA_ADDRESS + (MAX_ROWS * MAX_COLUMNS * 2) - (MAX_COLUMNS * 2));
  set_cursor_position (((int)position - VGA_ADDRESS) / 2);
  for (int i = 0; i < MAX_COLUMNS; i++, position += 2)
    *position = ' ';
}

// returns the cursor position
void print_char (char c, int offset, char attr) {
  unsigned char* position = (unsigned char*) VGA_ADDRESS;


  // write on cursor position
  if (offset == -1) {
    position += get_cursor_position () * 2;
    offset = get_cursor_position ();
    set_cursor_position (offset + 1);
    offset++;
  }
  else {
    position += offset * 2;
  }


  if (c == '\n') {
    offset = ((offset / 80) + 1) * 80;
    set_cursor_position (offset);
  }
  else {
    *position = c;
    position++;
    *position = attr;
    position++;
  }

  // update cursor position
  if ((offset) >= (MAX_ROWS * MAX_COLUMNS)) {
    // scroll_screen will set the new_cursor position
    scroll_screen ();
  }

}

void jprint_string (char* str, char attr) {
  for (int i = 0; str [i] != '\0'; i++)
    print_char (str [i], -1, attr);
}

void jprint (char* str) {
  jprint_string (str, WHITE_ON_BLACK);
}

void clear_screen () {
  for (int i = 0; i < (MAX_ROWS * MAX_COLUMNS); i++)
    print_char (' ', i, WHITE_ON_BLACK);
}

