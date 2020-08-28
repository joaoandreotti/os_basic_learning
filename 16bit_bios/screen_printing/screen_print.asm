mov ah, 0x0e ; set the high byte of ax register (BIOS print routine)

mov al, 'h' ; set the lower byte of ax register (character to be printed)
int 0x10 ; screen-related interrupt (BIOS)
mov al, 'e'
int 0x10
mov al, 'l'
int 0x10
mov al, 'l'
int 0x10
mov al, 'o'
int 0x10




loop: jmp loop ; jump to same address
        ; first one is the 'jmp' second one is the label

times 510-($-$$) db 0 ; write zeroed bytes until the 510th byte

dw 0xaa55 ; aa55 is the magic number (dw is a word of two bytes)

;dw 0x65b0 ; writing the raw bytes to machine code insted 'mov al(b0), 65'
;dw 0x10cd ; same thing but for the instruction 'int(cd) 0x10'
