[bits 32]

; tell the linker that the 'main' symbol is a external one
[extern main]

call main

jmp $
