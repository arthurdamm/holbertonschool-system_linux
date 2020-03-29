BITS 64
	global asm_puts
	extern asm_strlen

	section .text

asm_puts:
	push rbp
	mov rbp, rsp

	push r15
	push rdi
	call asm_strlen
	pop rdi
	push rdi

	mov r15, rax
	mov rax, 1
	mov rdi, 1
	mov rsi, [rsp]
	mov rdx, r15
	syscall

end:
	pop rdi
	mov rax, r15
	pop r15
	mov rsp, rbp
	pop rbp
	ret
