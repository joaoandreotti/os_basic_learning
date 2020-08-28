#ifndef SCREEN_H
#define SCREEN_H
#define VGA_ADDRESS 0xb8000

#define MAX_COLUMNS 80
#define MAX_ROWS 25

#define WHITE_ON_BLACK 0x0f

// device ports address
#define SCREEN_PORT_CONTROL 0x3d4
#define SCREEN_PORT_DATA 0x3d5


void clear_screen ();
void jprint (char*);

#endif
