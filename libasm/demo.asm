global _main
extern printf, scanf

section .text
main:
    push rbp
    mov rbp, rsp
    sub rsp, 16

    xor eax, eax
    lea rdi, [msg]
    call printf

    mov eax, 0
    lea rdi, [format]
    lea rsi, [number]
    call printf

    mov DWORD [rbp-4 ], 0

loop:
    mov edx, [number]
    mov rsi, [rbp - 4]
    lea rdi, [msg2]
    xor eax, eax
    call printf

    mov ecx, DWORD [number]
    add DWORD [rbp - 4], 1

    cmp [rbp - 4], ecx
    jle loop

    add rsp, 16
    leave
    ret

section .data
    msg: db "Enter a number: ",0
    msg2: db "Looping %d of %d",10,0
    format: db "%d",0

section .bss
    number resb 4