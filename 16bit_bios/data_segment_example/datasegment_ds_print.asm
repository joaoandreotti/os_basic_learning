mov ah, 0xe

;first two use the register ds and the last ones
;uses the register es

mov al, [the_secret]
int 0x10

;the correct base address is 0x7c00, but the data segment
;register ds is multiplied by 16 when applying the offset
mov bx, 0x7c0
mov ds, bx
mov al, [the_secret]
int 0x10

;using the register es instead ds to apply the offset
;es is a general propose segment register
mov al, [es:the_secret]
int 0x10

;the correct base address is 0x7c00, but the data segment
;register es is multiplied by 16 when applying the offset
mov bx, 0x7c0
mov es, bx
mov al, [es:the_secret]
int 0x10

the_secret:
  db 'X'

jmp $

times 510-($-$$) db 0
dw 0xaa55
