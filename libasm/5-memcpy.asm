section .text
    global asm_memcpy

asm_memcpy:
    mov rax, rdi
    xor rbx, rbx
    xor r10b, r10b

.copy_loop:
    mov r10b, byte [rsi]
    mov byte [rdi], r10b

    inc rsi
    inc rdi

    cmp rbx, rdx
    jne .increment

    ret

.increment:
    inc rbx
    jmp .copy_loop
    