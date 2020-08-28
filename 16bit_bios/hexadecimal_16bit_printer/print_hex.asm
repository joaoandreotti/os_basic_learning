HEX_OUT:
  db ' 0x0000', 0

BP_REGISTER_PRINT_HEX:
  db 0
SP_REGISTER_PRINT_HEX:
  db 0

print_hex:
  push ax
  push cx

  mov [BP_REGISTER_PRINT_HEX], bp
  mov [SP_REGISTER_PRINT_HEX], sp

  mov bp, HEX_OUT
  add bp, 0x07 ; end of string HEX_OUT
  mov sp, bp

  ;first/second digit
  mov ax, dx
  mov ah, al

  ;FIRST ONE
  ; check if number or letter
  and al, 0x000f
  cmp al, 0xa
  jl NUMBER_PRINT_HEX_00
  DIGIT_PRINT_HEX_00:
    add al, 0x37
    jmp NUMBER_PRINT_HEX_END_00
  NUMBER_PRINT_HEX_00:
    add al, 0x30
  NUMBER_PRINT_HEX_END_00:

  ;SECOND ONE
  ; check if number or letter
  and ah, 0x00f0
  shr ah, 4
  cmp ah, 0xa
  jl NUMBER_PRINT_HEX_01
  DIGIT_PRINT_HEX_01:
    add ah, 0x37
    jmp NUMBER_PRINT_HEX_END_01
  NUMBER_PRINT_HEX_01:
    add ah, 0x30
  NUMBER_PRINT_HEX_END_01:

  mov cx, ax
  mov ah, cl
  mov al, ch
  push ax

  ;third/fourth digit
  mov ax, dx
  mov al, ah

  ;THIRD ONE
  ; check if number or letter
  and al, 0x000f
  cmp al, 0xa
  jl NUMBER_PRINT_HEX_02
  DIGIT_PRINT_HEX_02:
    add al, 0x37
    jmp NUMBER_PRINT_HEX_END_02
  NUMBER_PRINT_HEX_02:
    add al, 0x30
  NUMBER_PRINT_HEX_END_02:

  ;FOURTH ONE
  ; check if number or letter
  and ah, 0x00f0
  shr ah, 4
  cmp ah, 0xa
  jl NUMBER_PRINT_HEX_03
  DIGIT_PRINT_HEX_03:
    add ah, 0x37
    jmp NUMBER_PRINT_HEX_END_03
  NUMBER_PRINT_HEX_03:
    add ah, 0x30
  NUMBER_PRINT_HEX_END_03:

  mov cx, ax
  mov ah, cl
  mov al, ch
  push ax

  pop ax
  pop ax

  mov bp, [BP_REGISTER_PRINT_HEX]
  mov sp, [SP_REGISTER_PRINT_HEX]

  pop cx
  pop ax

  mov bx, HEX_OUT
  call print_string

  ret
