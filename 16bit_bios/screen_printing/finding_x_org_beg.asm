[org 0x7c00]

mov ah, 0x0e

;does not print because it holds the number of the address
mov al, the_secret
int 0x10

;it does print the value X because the_secret is the right
;address of X
mov al, [the_secret]
int 0x10

;it does not print the value of X because the_secret already has
;the right address of X, thus when the add command is called the
;address is wrong
mov bx, the_secret
add bx, 0x7c00
mov al, [bx]
int 0x10

;continues to print the value X
mov al, [0x7c1d]
int 0x10

jmp $

the_secret:
  db "X"

times 510-($-$$) db 0

dw 0xaa55
