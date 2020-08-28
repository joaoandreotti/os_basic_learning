;nasm way to include files
;%include "file.asm"

call func

func:
  pusha ; push all registers to stack
  popa ; pop the values back
  ret

jmp $
times 510-($-$$) db 0
dw 0xaa55
