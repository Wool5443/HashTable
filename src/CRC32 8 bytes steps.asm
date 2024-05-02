global CRC32

section .text

;----------------------------------------------
; Enrty: rdi -> data, rsi - size
; Return: CRC32 hash
;----------------------------------------------
CRC32:
    cld

    mov  rcx, rsi ; rcx = size
    mov  r8, rsi
    and  r8, 0b111 ; r8 = size % 8

    mov  rsi, rdi ; rsi -> data
    xor  rdx, rdx ; rdx holds the result
 
    shr  rcx, 3 ; rcx = size / 8
    jz   .skip8

    .loop8:
        lodsq
        crc32 rdx, rax
        loop .loop8

    .skip8:

    test r8, r8
    jz   .end

    mov  rcx, r8 ; rcx = size % 8

    .loop1:
        lodsb
        crc32 rdx, al
        loop .loop1

    .end:
    mov  rax, rdx

    ret
