section .text
    global asm_memcpy

asm_memcpy:
    mov rax, rdi
    xor rbx, rbx

.copy_loop:
    mov r10b, byte [rsi]
    mov byte [rdi], r10b
    inc rsi
    inc rdi

    inc rbx
    cmp rbx, rdx
    jl .copy_loop

    ret