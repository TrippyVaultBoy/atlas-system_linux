section .text
    global _asm_strcmp

_asm_strcmp:
    push rbp
    mov rbp, rsp
    sub rsp, 32

    cmp rdi, 0
    je .equal
    cmp rsi, 0
    je .equal
    jmp .not_equal

.equal:
    mov eax, 0
    jmp .epilogue

.not_equal:
    mov al, byte [rdi]
    mov bl, byte [rsi]

    test al, al
    jz .equal
    test bl, bl
    jz .equal

    cmp al, bl
    jl .less_than
    jg .greater_than

    inc rdi
    inc rsi
    jmp .not_equal

.less_than:
    mov eax, -1
    jmp .epilogue

.greater_than:
    mov eax, 1
    jmp .epilogue

.epilogue:
    leave
    ret