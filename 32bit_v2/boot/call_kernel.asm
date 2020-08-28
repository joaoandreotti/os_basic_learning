global _start
[bits 32]

; tell the linker that the 'entry' symbol is a external one
_start:
  [extern entry]

  call entry

  jmp $
