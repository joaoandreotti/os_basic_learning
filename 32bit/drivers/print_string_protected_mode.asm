[bits 32]

; constants
; memory position of VGA
VIDEO_MEMORY equ 0xb8000
; second byte as configuration flags
WHITE_ON_BLACK equ 0x0f

; prints a null terminated string
; ebx as parameter
print_string_pm:
  pusha
  mov edx, VIDEO_MEMORY

print_string_pm_loop:
  mov al, [ebx]
  mov ah, WHITE_ON_BLACK

  ; while
  cmp al, 0
  je print_string_pm_end
  mov [edx], ax
  ; next string char
  add ebx, 1
  ; next memory position
  add edx, 2

  jmp print_string_pm_loop

print_string_pm_end:
  popa
  ret
