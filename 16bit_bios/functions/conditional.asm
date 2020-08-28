mov bx, 40

;just a normal if
cmp bx, 4
jle IF
cmp bx, 40
jl ELSE_IF_1
ELSE:
  mov al, 'C'
  jmp END
ELSE_IF_1:
  mov al, 'B'
  jmp END
IF:
  mov al, 'A'
  jmp END

END:
mov ah, 0xe
int 0x10

jmp $
times 510-($-$$) db 0
dw 0xaa55
