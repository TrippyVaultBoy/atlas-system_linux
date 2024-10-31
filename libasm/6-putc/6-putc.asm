section .text
    global asm_putc

asm_putc:
    mov byte [rsp-1], dil

    mov rax, 1
    mov rdi, 1
    lea rsi, [rsp-1]
    mov rdx, 1

    syscall
    ret