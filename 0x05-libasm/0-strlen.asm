BITS 64
	global asm_strlen

	section .text

asm_strlen:
	push rbp
	mov rbp, rsp
	mov rax, 0
	jmp loop_check

loop_body:
	inc rax
	inc rdi

loop_check:
	cmp byte [rdi], 0
	jne loop_body

	mov rsp, rbp
	pop rbp
	ret
