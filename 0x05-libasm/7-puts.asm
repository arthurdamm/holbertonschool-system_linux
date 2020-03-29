BITS 64
	global asm_puts

	section .text

asm_puts:
	push rbp
	mov rbp, rsp

	push r15
	push rdi
	xor r15, r15
	xor rcx, rcx

loop_strlen:
	cmp BYTE [rdi], 0
	jz call_write
	inc rcx
	inc rdi
	jmp loop_strlen

call_write:
	test rcx, rcx
	jz end
	mov r15, rcx
	mov rax, 1
	mov rdi, 1
	mov rsi, [rsp]
	mov rdx, rcx
	syscall

end:
	pop rdi
	mov rax, r15
	pop r15
	mov rsp, rbp
	pop rbp
	ret
