global CRC32

section .text

;----------------------------------------------
; Enrty: rdi -> data, rsi - size
; Return: CRC32 hash
;----------------------------------------------
CRC32:
    cld

    mov  rcx, rsi ; rcx = size
    mov  rsi, rdi ; rsi -> data
    xor  rdx, rdx ; rdx holds the result

    .loop:
        lodsb
        crc32 edx, al
        loop .loop

    .end:
    mov  rax, rdx

    ret
