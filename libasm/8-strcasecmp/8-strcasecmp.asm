section .text
    global asm_strcasecmp

asm_strcasecmp:
    xor rax, rax

.compare_loop:
    mov al, byte [rdi]
    mov bl, byte [rsi]

    cmp al, 'A'
    jl .skip_lower1
    cmp al, 'Z'
    jg .skip_lower1
    or al, 0x20

.skip_lower1:
    cmp bl, 'A'
    jl .skip_lower2
    cmp bl, 'Z'
    jg .skip_lower2
    or bl, 0x20

.skip_lower2:
    cmp al, bl
    jne .not_equal

    test al, al
    je .equal

    inc rdi
    inc rsi
    jmp .compare_loop

.not_equal:
    sub rax, rbx

.equal:
    ret