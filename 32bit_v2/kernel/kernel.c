#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "../cpu/idt.h"
#include "../cpu/isr.h"
#include "../libc/memory_manager.h"
#include "../drivers/pci.h"
#include "../drivers/nic.h"

typedef struct ether_frame {
  uint8_t src_mac_addr [6];
  uint8_t dst_mac_addr [6];
  uint16_t type;
  uint8_t data [8];
} __attribute__ ((packed)) ether_frame;

void entry () {
  // memory address of the VGA
  clear_screen ();
  set_cursor_position (0);
  isr_install ();
  init_keyboard ();
  memory_manager_init ();
  //init_timer (10);
  jprint ("JAMES OS is ready to go\n");
  asm volatile ("sti");
  init_rtl8139 ();

  uint32_t data = pci_read_data (nic_bus, nic_device, 0x3c);
  //uint32_t mac = port_dword_in (((uint16_t)data & ~0x3) + 0x4);
  char str [10];
  int_to_string (data, str);
  jprint ("AAAAAAAAAAAAAAAAa: ");
  jprint (str);
  jprint ("\n");

  asm ("int $14");

  // try to send a message
  /*
  while (1) {
    jprint ("sending\n");
    ether_frame frame;

    frame.dst_mac_addr [0] = 0xff;
    frame.dst_mac_addr [1] = 0xff;
    frame.dst_mac_addr [2] = 0xff;
    frame.dst_mac_addr [3] = 0xff;
    frame.dst_mac_addr [4] = 0xff;
    frame.dst_mac_addr [5] = 0xff;

    frame.src_mac_addr [0] = 0x52;
    frame.src_mac_addr [1] = 0x54;
    frame.src_mac_addr [2] = 0x00;
    frame.src_mac_addr [3] = 0x12;
    frame.src_mac_addr [4] = 0x34;
    frame.src_mac_addr [5] = 0x56;

    frame.type = 0x0800;

    frame.data [0] = (uint8_t) 'j';
    frame.data [1] = (uint8_t) 'j';
    frame.data [2] = (uint8_t) 'j';
    frame.data [3] = (uint8_t) 'j';
    frame.data [4] = (uint8_t) 'j';
    frame.data [5] = (uint8_t) 'j';
    frame.data [6] = (uint8_t) 'j';
    frame.data [7] = (uint8_t) 'j';

    uint32_t data = pci_read_data (nic_bus, nic_device, 0x10);
    port_dword_out (((uint16_t)data & ~0x3) + 0x20, &frame);
    port_dword_out (((uint16_t)data & ~0x3) + 0x10, 22);
  }
  */
}
