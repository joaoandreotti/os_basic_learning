#include "pci.h"

uint32_t pci_read_data (uint8_t bus, uint8_t device, uint8_t offset)
{
  uint32_t address = pci_gen_address (bus, device, offset);

  /* write out the address */
  port_dword_out ((uint16_t)0xCF8, address);

  /* read in the data */
  /* (offset & 2) * 8) = 0 will choose the first word of the 32 bits register */
  uint32_t tmp = (uint32_t)(port_dword_in ((uint16_t)0xCFC));
  return tmp;
}

void pci_write_data (uint32_t address, uint32_t data)
{
  // where to write
  port_dword_out ((uint16_t)0xCF8, address);
  // write
  port_dword_out ((uint16_t)0xCFC, data);
}

uint32_t pci_gen_address (uint8_t bus, uint8_t device, uint8_t offset)
{ uint32_t address;
  uint32_t lbus  = (uint32_t)bus;
  uint32_t ldevice = (uint32_t)device;
  uint32_t lfunc = 0;
  uint32_t tmp = 0;

  address = (uint32_t)((lbus << 16) | (ldevice << 11) |
      (lfunc << 8) | (offset & 0xfc) | ((uint32_t)0x80000000));

  return address;
}


void pci_brute () {
  jprint ("BRUTING PCI DEVICES\n");
  uint16_t i, j;
  for (i = 0; i < 256; i++) {
    for (j = 0; j < 32; j++) {
      uint32_t data = pci_read_data (i, j, 0);
      if (data == 0x813910ec) {
        char str [40];
        data = pci_read_data (i, j, 0);
        nic_bus = i;
        nic_device = j;
        print_hex (data, "(");
        jprint (")");
        jprint ("\n");
      }
    }
  }
  jprint ("DONE\n");
}
