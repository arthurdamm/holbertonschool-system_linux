BITS 64
	global asm_strchr
	section text
asm_strchr:
	push rbp
	mov rbp, rsp
	xor rax, rax

while:
	mov al, BYTE [rdi]
	cmp BYTE [rdi], sil
	jz found
	cmp BYTE [rdi], 0
	jz end
	inc rdi
	jmp while

found:
	mov rax, rdi

end:
	mov rsp, rbp
	pop rbp
	ret
