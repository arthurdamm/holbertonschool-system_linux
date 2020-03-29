BITS 64
	global asm_putc

	section .text

asm_putc:
	push rbp
	mov rbp, rsp

	push rdi
	mov rax, 1
	mov rdi, 1
	mov rsi, rsp
	mov rdx, 1
	syscall

	mov rsp, rbp
	pop rbp
	ret
