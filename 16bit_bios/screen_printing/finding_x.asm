mov ah, 0x0e

;does not print X because it prints the label address value char (1d)
mov al, the_secret
int 0x10

;does no print X because it prints the address of the begining of the
;memory plus the value of the label, not the address of the begining of the program
mov al, [the_secret]
int 0x10

;it prints value X because al holds the exactly memomry value where
;X is stored, the [] tells that the value in the memory address bx
;is stored in al
mov bx, the_secret
add bx, 0x7c00
mov al, [bx]
int 0x10

;it has the hardcoded memory address, so it should print the value X
mov al, [0x7c1d]
int 0x10

jmp $

the_secret:
  db "X"

times 510-($-$$) db 0

dw 0xaa55
