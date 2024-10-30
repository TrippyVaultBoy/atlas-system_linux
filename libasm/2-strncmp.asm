section .text
    global asm_strncmp

asm_strncmp:
    test rdx, rdx
    jz .equal

.loop:
    mov al, byte [rdi]
    mov bl, byte [rsi]

    cmp al, bl
    jne .not_equal

    test al, al
    jz .equal

    dec rdx
    jz .equal

    inc rdi
    inc rsi
    jmp .loop

.equal:
    xor eax, eax
    ret

.not_equal:
    movsx rax, al
    movsx rcx, bl
    sub rax, rcx
    ret

