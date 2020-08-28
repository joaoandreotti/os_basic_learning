;global variables
DISK_ERROR_MSG_00:
  db '[-](00)ERROR WHILE READING THE DISK!', 0

DISK_ERROR_MSG_01:
  db '[-](01)ERROR WHILE READING THE DISK!', 0

BOOT_DRIVE:
  db 0

disk_load:
  push dx
  mov ah, 0x02
  mov al, dh
  mov ch, 0x00
  mov dh, 0x00
  mov cl, 0x02
  int 0x13

  jc disk_error_00

  pop dx
  cmp dh, al
  jne disk_error_01
  ret

  jmp $
  disk_error_00:
  mov bx, DISK_ERROR_MSG_00
  call print_string
  jmp $

  disk_error_01:
  mov bx, DISK_ERROR_MSG_01
  call print_string
  jmp $

