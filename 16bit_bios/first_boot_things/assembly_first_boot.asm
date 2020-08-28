loop:
  jmp loop ; jump to label loop (2 byte instruction)
           ; first one is the 'jmp' second one is the label

times 510-($-$$) db 0 ; write zeroed bytes until the 510th byte

dw 0xaa55 ; aa55 is the magic number (dw is a word of two bytes)
