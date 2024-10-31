section .text
    global asm_puts
    extern asm_strlen

asm_puts:
    mov rdi, rdi
    call asm_strlen

    mov rsi, rdi
    mov rdi, 1
    mov rdx, rax
    mov rax, 1

    syscall

    ret