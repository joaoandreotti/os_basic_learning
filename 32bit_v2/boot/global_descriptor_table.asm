; TODO understand this fcking shit!
gdt_start:

; 8 bytes from the mandatory null descriptor
gdt_null:
  ;dd == double word (4 bytes)
  dd 0x0
  dd 0x0

; these two descriptors for data and code only differences
; are some flag bits
; i still cant understand the use of this descriptors but
; i will update this later
gdt_code: 
  dw 0xffff
  dw 0x0
  db 0x0
  db 10011010b
  db 11001111b
  db 0x0  

gdt_data:
  dw 0xffff
  dw 0x0
  db 0x0
  db 10010010b
  db 11001111b
  db 0x0
  
gdt_end:

; gdt descritor is a 6byte descriptor (2 for size, 4 for start address)
gdt_descriptor:
  ; the size must be the original size -1
  dw gdt_end - gdt_start - 1
  dd gdt_start

; this two constants are for the GDT segment descriptor offset which
; i cant still understand :(
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start
