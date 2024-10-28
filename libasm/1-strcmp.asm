section .text
    global asm_strcmp

    asm_strcmp:
    .loop:
        mov al, byte [rdi]
        mov bl, byte [rsi]

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
