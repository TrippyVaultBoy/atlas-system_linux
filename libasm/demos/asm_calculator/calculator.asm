; int calulator(int arg1, int arg2, char op)
section .text
    global asm_calculator

asm_calculator:
    mov rcx, rdi
    mov r8, rsi
    mov r9b, byte [rdx]

    cmp r9b, '+'
    je .add

    cmp r9b, '-'
    je .sub

    cmp r9b, '*'
    je .mul

    cmp r9b, '/'
    je .div

    mov rax, 0
    ret

.add:
    mov rax, rcx
    add rax, r8
    ret

.sub:
    mov rax, rcx
    sub rax, r8
    ret

.mul:
    mov rax, rcx
    imul rax, r8
    ret

.div:
    cmp r8, 0
    je .div_zero

    mov rax, rcx
    xor rdx, rdx
    div r8

.div_zero:
    mov rax, 0
    ret