section .data           ; Data section
    hello db 'Hello, World!', 0x0A  ; The message, with a newline character (0xA)

section .text           ; Code section
    global _start       ; Entry point for the linker

_start:
    ; Write "Hello, World!" to stdout
    mov rax, 1          ; System call number 1 (sys_write)
    mov rdi, 1          ; File descriptor 1 (stdout)
    mov rsi, hello      ; Pointer to the hello message
    mov rdx, 14         ; Length of the message
    syscall             ; Invoke the system call

    ; Exit the program
    mov rax, 60         ; System call number 60 (sys_exit)
    xor rdi, rdi        ; Exit code 0
    syscall             ; Invoke the system call