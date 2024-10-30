section .text
    global asm_memcpy

asm_memcpy:
    test rdx, rdx
    jz .done

.copy_loop:
    mov al, [rsi]
    mov [rdi], al
    inc rsi
    inc rdi
    dec rdx
    jnz .copy_loop

.done:
    mov rax, rdi
    ret