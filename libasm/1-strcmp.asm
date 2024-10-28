section .text
    global asm_strcmp

asm_strcmp:
    xor rax, rax

    .loop:
        mov r8b, byte [rdi]
        mov r9b, byte [rsi]

        cmp r8b, r9b
        jne .not_equal

        test r8b, r8b
        je .equal

        inc rdi
        inc rsi
        jmp .loop

    .not_equal:
        sub rax,
        ret

    .equal:
        xor rax, rax
        ret