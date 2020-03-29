BITS 64
	global asm_memcpy

	section .text
asm_memcpy:
	push rbp
	mov rbp, rsp
	push rdi
	xor rax, rax

copy_while:
	test rdx, rdx
	jz end
	dec rdx
	mov al, BYTE [rsi]
	mov BYTE [rdi], al
	inc rdi
	inc rsi
	jmp copy_while

end:
	pop rax
	mov rsp, rbp
	pop rbp
	ret
