#include "../cpu/types.h"

// parameter is a 16bit address
// and return the data in that i/o port address
u8 port_byte_in (u16 port) {
  // using inline assembly
  // this means we gonna read a port with address in dx
  // and store its result in al
  // also, "=a" (result) means that the value from al will be stored
  // the variable result
  // and the "d" (port) means that we gonna set the dx value to the
  // port variable
  u8 result;
  __asm__ ("in %%dx, %%al" : "=a" (result) : "d" (port));

  return result;
}

// parameter is the 16bit port address and the data that will
// be written to
void port_byte_out (u16 port, u8 data) {
  // write value in al to port address stored in dx
  __asm__ ("out %%al, %%dx" : : "a" (data), "d" (port));
}



// same thing but now is for 16bit data


// parameter is a 16bit address
u16 port_word_in (u16 port) {
  u16 result;
  __asm__ ("in %%dx, %%al" : "=a" (result) : "d" (port));
  return result;
}

// parameter is the 16bit port address and the data that will
// be written to
void port_word_out (u16 port, u16 data) {
  // write value in al to port address stored in dx
  __asm__ ("out %%al, %%dx" : : "a" (data), "d" (port));
}


