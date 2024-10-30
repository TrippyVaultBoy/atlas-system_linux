section .text
    global asm_strstr

asm_strstr:
    mov al , byte [rsi]
    test al, al
    je .return_haystack

.loop_haystack:
    mov rax, rdi
    mov rcx, rsi

.loop_needle:
    mov dl, byte [rcx]
    test dl, dl
    je .found

    mov bl, byte [rdi]
    test bl, bl
    je .not_found

    cmp dl, bl
    jne .next_haystack

    inc rdi
    inc rcx
    jmp .loop_needle

.next_haystack:
    inc rax
    mov rdi, rax
    mov rcx, rdi
    jmp .loop_haystack

.found:
    mov rax, rdi
    sub rax, rcx
    add rax, rsi
    ret

.not_found:
    xor rax, rax
    ret

.return_haystack:
    mov rax, rdi
    ret