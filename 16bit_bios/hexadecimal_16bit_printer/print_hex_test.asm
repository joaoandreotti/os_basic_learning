[org 0x7c00]

mov bp, 0x8000
mov sp, bp

mov dx, 0x1f4a
call print_hex

mov dx, 0xdbca
call print_hex

jmp $

%include "../screen_printing/print_string.asm"
%include "../hexadecimal_16bit_printer/print_hex.asm"

times 510-($-$$) db 0
dw 0xaa55
