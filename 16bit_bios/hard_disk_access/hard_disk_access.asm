[org 0x7c00]

;BIOS store boot drive in dl
mov [BOOT_DRIVE], dl

mov bp, 0x8000
mov sp, bp

;mov from 0x0000:0x9000(es:bx)
mov bx, 0x9000

mov dh, 5
mov dl, [BOOT_DRIVE]

call disk_access_function

;to test the disk some random known stuff was written
;at memory on position 0x9000, then we will print then
;we are going to do the same to the first two sectors that
;as initialy written

mov dx, [0x9000]
call print_hex

mov dx, [0x9000 + 512]
call print_hex


jmp $

;global variables
DISK_ERROR_MSG_00:
  db '[-]00ERROR WHILE READING THE DISK!', 0

DISK_ERROR_MSG_01:
  db '[-]01ERROR WHILE READING THE DISK!', 0

BOOT_DRIVE:
  db 0

HEX_OUT:
  db '0x0000', 0


;FUNCTIONS

jmp disk_access_end
;LOAD DL SECTORS TO ES:BX FROM DRIVE DL
disk_access_function:
  ;using dx as parameter
  ;using bx and es as parameter

  ;in dl we store which drive to use

  push dx

  mov ah, 0x02 ; BIOS sector reading
  ;in ch we specify which cilinder we want to use
  mov ch, 0x00

  ;in al we tell the number of sectors to read
  mov al, dh

  ;in dh we specify which side of the floppy
  mov dh, 0x00

  ;in cl we specify which sector we want to use
  ;it is not 0-based
  mov cl, 0x02

  ;in es:bx we store which address we want the BIOS
  ;to read the sectors to (es:bx means that we will use
  ;segment es with bx offset) (0xa000:0x1234 => 0xa1234)
  ;(0xa000 * 16 + 0x1234)
  ;mov bx, 0xa000
  ;mov es, bx
  ;mov bx, 0x1234

  ;int 0x13 is a interrupt disk
  int 0x13

  ;to check if the disk as written successfully
  ;we need to check if the carry flag if on
  ;if carry flag on means that it got an error
  jc disk_error_00

  pop dx
  ;check if the number of specified sectors
  ;is the same as the loaded ones
  cmp dh, al
  jne disk_error_01
  ret

  disk_error_00:
  mov bx, DISK_ERROR_MSG_00
  call print_string
  jmp $

  disk_error_01:
  mov bx, DISK_ERROR_MSG_01
  call print_string
  jmp $

disk_access_end:


;print_hex parameter(dx) is the relative address of the string
jmp print_hex_end
jmp print_hex_end
jmp print_hex_end
jmp print_hex_end
print_hex:

  push ax
  push bx

  push bp
  push sp

  mov bp, HEX_OUT
  add bp, 0x6 ; move to last byte position
  mov sp, bp


  ;FIRST BYTE
  ; set registers to 0
  and ax, 0x0
  and bx, 0x0
  ; al holds the first digit
  ; after the shift op and 'and' op, we exclude the first 4 bits of the hex
  ; so if we always have a 0x0Y, Y can be [0-f]
  mov ah, dl
  and ah, 0x0f
  cmp ah, 0xa
  jl NUMBER_FIRST_DIGIT_FIRST_BYTE
  ; if letter
  add ah, -0x0a
  add ah, 0x41
  jmp END_FIRST_DIGIT_FIRST_BYTE
  NUMBER_FIRST_DIGIT_FIRST_BYTE:
  add ah, 0x30
  END_FIRST_DIGIT_FIRST_BYTE:
  ; ah holds the second digit
  ; the second digit works differently, it grows like 0xY0, Y can be [0-f]
  mov bl, dl
  and bl, 0xf0
  shr bl, 4
  mov al, bl
  cmp al, 0xa
  jl NUMBER_SECOND_DIGIT_FIRST_BYTE
  ; if letter
  add al, -0x0a
  add al, 0x41
  jmp END_SECOND_DIGIT_FIRST_BYTE
  NUMBER_SECOND_DIGIT_FIRST_BYTE:
  add al, 0x30
  END_SECOND_DIGIT_FIRST_BYTE:
  push ax
  ;END FIRST BYTE

  ;SECOND BYTE
  ; set registers to 0
  and ax, 0x0
  and bx, 0x0
  ; al holds the first digit
  ; after the shift op and 'and' op, we exclude the first 4 bits of the hex
  ; so if we always have a 0x0Y, Y can be [0-f]
  mov ah, dh
  and ah, 0x0f
  cmp ah, 0xa
  jl NUMBER_FIRST_DIGIT_SECOND_BYTE
  ; if letter
  add ah, -0x0a
  add ah, 0x41
  jmp END_FIRST_DIGIT_SECOND_BYTE
  NUMBER_FIRST_DIGIT_SECOND_BYTE:
  add ah, 0x30
  END_FIRST_DIGIT_SECOND_BYTE:
  ; ah holds the second digit
  ; the second digit works differently, it grows like 0xY0, Y can be [0-f]
  mov bl, dh
  and bl, 0xf0
  shr bl, 4
  mov al, bl
  cmp al, 0xa
  jl NUMBER_SECOND_DIGIT_SECOND_BYTE
  ; if letter
  add al, -0x0a
  add al, 0x41
  jmp END_SECOND_DIGIT_SECOND_BYTE
  NUMBER_SECOND_DIGIT_SECOND_BYTE:
  add al, 0x30
  END_SECOND_DIGIT_SECOND_BYTE:
  push ax
  ;END SECOND BYTE

  pop ax
  pop ax


  pop sp
  pop bp
  
  pop bx
  pop ax

  mov bx, HEX_OUT
  call print_string

  ret
print_hex_end:


;print_string parameter(bx) is the relative address of the string
jmp print_string_end
print_string:
  pusha
  mov ah, 0xe

  ;while (str [i] != 0) print (str [i]);
  WHILE_PRINT_STRING:
    mov cl, [bx]
    cmp cl, 0x0
    je END_PRINT_STRING
    mov al, [bx]
    int 0x10
    add bx, 0x1
    jmp WHILE_PRINT_STRING


  END_PRINT_STRING:
    popa
    ret
print_string_end:

times 510-($-$$) db 0
dw 0xaa55

times 256 dw 0xdada
times 256 dw 0xfafa
