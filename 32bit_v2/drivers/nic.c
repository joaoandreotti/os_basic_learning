#include "nic.h"

static void nic_callback (registers_t *regs) {
  jprint ("pelo amor de deus\n");
}

void init_rtl8139 () {
  register_interrupt_handler (IRQ11, nic_callback); 

  pci_brute ();

  uint32_t data = pci_read_data (nic_bus, nic_device, 0);
  uint32_t tmp;

  print_hex (data, "found nic device: ");
  jprint ("\n");

  // set dma access
  data = pci_read_data (nic_bus, nic_device, 0x4);
  pci_write_data (pci_gen_address (nic_bus, nic_device, 0x4), data | 4);

  // set data to io base
  data = pci_read_data (nic_bus, nic_device, 0x10);

  jprint ("printing io base binary: ");
  for (int i = 31; i >= 0; i--)
    if ((data >> i) & 1)
      jprint ("1");
    else
      jprint ("0");
  jprint ("\n");

  jprint ("printing io base reverse int16_t: ");
  char hex_chars [16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
  tmp = (uint16_t) data;
  while (tmp)
  {
    char chr [2];
    chr [0] = hex_chars [tmp % 10];
    chr [1] = '\0';
    jprint (chr);
    tmp /= 10;
  }
  jprint ("\n");

  // turning on
  port_byte_out (((uint16_t)data & ~0x3) + 0x52, 0x0);

  // software reset
  port_byte_out (((uint16_t)data & ~0x3) + 0x37, 0x10);
  while ((port_byte_in (((uint16_t)data & ~0x3) + 0x37) & 0x10) != 0);

  //ioaddr is obtained from PCI configuration
  port_dword_out (((uint16_t)data & ~0x3) + 0x30, (uintptr_t)(8192 + 16));


  port_word_out (((uint16_t)data & ~0x3) + 0x3c, 0x5);

  port_byte_out (((uint16_t)data & ~0x3) + 0x44, 0xf | (1 << 7));

  port_word_out (((uint16_t)data & ~0x3) + 0x37, 0x0c);

  port_word_out (((uint16_t)data & ~0x3) + 0x3e, 0x1);

  //write_dword_port ()
}
