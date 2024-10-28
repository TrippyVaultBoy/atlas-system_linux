section .text
    global asm_strcmp

    asm_strcmp:
    .loop:
        movzx eax, byte [rdi]
        movzx ebx, byte [rsi]

        cmp al, bl
        jne .return

        test al, al
        je .return

        inc rdi
        inc rsi
        jmp .loop

    .return:
        sub eax, ebx
        ret
