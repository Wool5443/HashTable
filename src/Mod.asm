global Mod2

section .text

;---------------------------------------------------------
; Returns n % m where m is a power of 2
; Entry: rdi - n, rsi - m
; Return: rax - n % m
;---------------------------------------------------------
Mod2:
    mov  rcx, rsi ; cl - power of 2
    mov  rax, rdi ; rax = rdi
    shr  rdi, cl  ; rdi /= 2 ** m
    shl  rdi, cl  ; rdi *= 2 ** m
    sub  rax, rdi ; rax = n % m
    ret
