mov bp, 0x8000
mov sp, 0x8000

mov bx, HELLO_WORLD
call print_string

mov bx, GOODBYE_WORLD
call print_string

HELLO_WORLD:
  db 'Hello World!', 0
GOODBYE_WORLD:
  db 'Goodbye World!', 0

;print_string parameter is the relative address of the string
jmp print_string_end
print_string:
  pusha
  mov ah, 0xe
  add bx, 0x7c00

  ;while (str [i] != 0) print (str [i]);
  WHILE:
    mov cl, [bx]
    cmp cl, 0x0
    je END
    mov al, [bx]
    int 0x10
    add bx, 0x1
    jmp WHILE


  END:
    popa
    ret
print_string_end:

jmp $
times 510-($-$$) db 0
dw 0xaa55
