global CRC32

section .text

;----------------------------------------------
; Enrty: rdi -> data, rsi - size
; Return: CRC32 hash
;----------------------------------------------
CRC32:
    cld

    mov  rcx, rsi
    and  rsi, 0b11 ; rsi = size % 4
    mov  r8, rsi ; r8 = size % 4
    mov  rsi, rdi ; rsi -> data
    xor  rdx, rdx ; rdx holds the result

 
    shr  rcx, 2 ; rcx = size / 4
    jz   .skip4

    .loop4:
        lodsd
        crc32 edx, eax
        loop .loop4

    .skip4:
    mov  rcx, r8 ; process last bytes

    test rcx, rcx
    jz   .end

    .loop:
        lodsb
        crc32 edx, al
        loop .loop

    .end:
    mov  rax, rdx

    ret
