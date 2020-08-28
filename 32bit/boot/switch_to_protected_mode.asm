[bits 16]

switch_to_pm:
  ; clear interrupt to set-up the protected mode so we do not
  ; have problems with interrupt, but disabling the BIOS IVA
  cli


  ; load the global descriptor table (2byte size, 4byte start address)
  lgdt [gdt_descriptor] 


  ; to make the switch between modes we set the first bit of the
  ; control register (cr0) to 1
  mov eax, cr0
  or eax, 0x1
  mov cr0, eax


  ; here we make a far jump, it is more a concept jump used to
  ; flush all instructions in the CPU pipeline so none of the
  ; remaining instructions doesnt execute in the wrong mode
  jmp CODE_SEG:init_pm


[bits 32]

init_pm:

  ; in switching to protected mode the old segments are meaningless,
  ; so now they have to point to the new data segment previouly defined
  mov ax, DATA_SEG
  mov ds, ax
  mov ss, ax
  mov es, ax
  mov fs, ax
  mov gs, ax


  ; updating the stack top
  mov ebp, 0x90000
  mov esp, ebp

  ; begin protected mode instructions
  call BEGIN_PM
