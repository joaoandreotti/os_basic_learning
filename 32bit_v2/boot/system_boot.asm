[org 0x7c00]

; where the kernel is
KERNEL_OFFSET equ 0x1000

; stores the boot drive ID
mov [BOOT_DRIVE], dl

mov bp, 0x9000
mov sp, bp

; test message
mov bx, REAL_MODE_MSG
call print_string

; load kernel from the disk with the BIOS help
; and then we switch to 32bit protected mode so our kernel can
; run without any problem
call load_kernel

; switch to 32bit protected mode
call switch_to_pm

jmp $

%include "boot/global_descriptor_table.asm"
%include "boot/switch_to_protected_mode.asm"
%include "boot/print_string.asm"
%include "boot/print_string_protected_mode.asm"
%include "boot/disk_load.asm"


[bits 16]

; load kernel form disk
; which is basically call the disk access function with the right
; parameters
load_kernel:
  mov bx, LOADING_KERNEL_MSG
  call print_string

  mov bx, KERNEL_OFFSET
  mov dh, 32
  mov dl, [BOOT_DRIVE]
  call disk_load

  ret
 
[bits 32]


BEGIN_PM:
  mov ebx, PROTECTED_MODE_MSG
  call print_string_pm

  ; go to the address where the kernel is
  call KERNEL_OFFSET

  mov ebx, LEAVING_KERNEL_MSG
  call print_string_pm

  jmp $


; global variables
REAL_MODE_MSG:
  db "[+]The same old real-mode! :)", 0

PROTECTED_MODE_MSG:
  db "[+]The protected mode! :D", 0

LOADING_KERNEL_MSG:
  db "[+]Loading kernel into main memory!", 0

LEAVING_KERNEL_MSG:
  db "[+]Leaving kernel! (bye bye)", 0

times 510-($-$$) db 0
dw 0xaa55
