section .text
    global asm_strcmp

asm_strcmp:
    xor rax, rax
    xor rcx, rcx

.loop:
    mov al, byte [rdi + rcx]
    mov bl, byte [rsi + rcx]

    cmp al, 0
    je .check_end 

    cmp bl, 0
    je .check_end

    cmp al, bl
    jne .set_result

    inc rcx
    jmp .loop

.check_end:
    cmp al, bl
    jne .set_result
    ret

.set_result:
    mov rax, 1
    cmp al, bl
    jg .done
    mov rax, -1

.done:
    ret