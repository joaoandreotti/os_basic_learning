mov bp, 0x8000
mov sp, 0x8000

push 'A'
push 'B'
push 'C'

mov ah, 0xe

pop bx
mov al, bl
int 0x10

pop bx
mov al, bl
int 0x10

mov al, [0x07ffe]
int 0x10

jmp $

times 510-($-$$) db 0

dw 0xaa55
