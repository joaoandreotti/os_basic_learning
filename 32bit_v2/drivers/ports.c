#include "ports.h"

// parameter is a 16bit address
// and return the data in that i/o port address
uint8_t port_byte_in (uint16_t port) {
  // using inline assembly
  // this means we gonna read a port with address in dx
  // and store its result in al
  // also, "=a" (result) means that the value from al will be stored
  // the variable result
  // and the "d" (port) means that we gonna set the dx value to the
  // port variable
  uint8_t result;
  __asm__ ("in %%dx, %%al" : "=a" (result) : "d" (port));

  return result;
}

// parameter is the 16bit port address and the data that will
// be written to
void port_byte_out (uint16_t port, uint8_t data) {
  // write value in al to port address stored in dx
  __asm__  __volatile__ ("out %%al, %%dx" : : "a" (data), "d" (port));
}



// same thing but now is for 16bit data


// parameter is a 16bit address
uint16_t port_word_in (uint16_t port) {
  uint16_t result;
  __asm__ ("in %%dx, %%al" : "=a" (result) : "d" (port));
  return result;
}

// parameter is the 16bit port address and the data that will
// be written to
void port_word_out (uint16_t port, uint16_t data) {
  // write value in al to port address stored in dx
  __asm__ __volatile__ ("out %%al, %%dx" : : "a" (data), "d" (port));
}


// parameter is a 16bit address
uint32_t port_dword_in (uint16_t port) {
  uint32_t result;
  __asm__ ("in %%dx, %%eax" : "=a" (result) : "d" (port));
  return result;
}

// parameter is the 16bit port address and the data that will
// be written to
void port_dword_out (uint16_t port, uint32_t data) {
  // write value in al to port address stored in dx
  __asm__ __volatile__ ("out %%eax, %%dx" : : "a" (data), "d" (port));
}
