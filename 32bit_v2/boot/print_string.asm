[bits 16]
print_string:
  push ax
  push bx
  push cx
  mov ah, 0xe

  WHILE_PRINT_STRING:
    mov cl, [bx]
    cmp cl, 0x0
    je END_PRINT_STRING
    mov al, [bx]
    int 0x10
    add bx, 0x1
    jmp WHILE_PRINT_STRING


  END_PRINT_STRING:
    pop cx
    pop bx
    pop ax
    ret
