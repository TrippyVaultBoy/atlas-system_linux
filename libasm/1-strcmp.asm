section .text
    global asm_strcmp

asm_strcmp:
    xor rax, rax

.loop:
    mov al, [rdi]
    mov bl, [rsi]

    cmp al, bl
    jne .not_equal

    test al, al
    je .equal

    inc rdi
    inc rsi
    jmp .loop

.not_equal:
    movzx eax, al
    movzx ebx, bl
    sub eax, ebx
    ret

.equal:
    xor rax, rax
    ret