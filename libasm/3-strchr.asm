section .text
    global asm_strchr

asm_strchr:
    mov dl, sil

.loop:
    mov al, byte [rdi]

    test al, al
    je .not_found

    cmp al, dl
    je .found

    inc rdi
    jmp .loop

.found:
    mov rax, rdi
    ret

.not_found:
    xor rax, rax
    ret