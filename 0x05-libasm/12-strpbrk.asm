BITS 64
	global asm_strpbrk
	section text

asm_strpbrk:
	push rbp
	mov rbp, rsp
	xor rax, rax

	mov r10, rdi
	mov r11, rsi
while:
	movzx r8, BYTE [r10]
	cmp r8b, 0
	jz end
	mov rdi, r11
	mov rsi, r8
	jmp strchr
	strchr_return:
	cmp rax, 0
	jnz found
	inc r10
	jmp while

found:
	mov rax, r10

end:
	mov rsp, rbp
	pop rbp
	ret

strchr:
	push rbp
	mov rbp, rsp
	xor rax, rax

strchr_while:
	mov al, BYTE [rdi]
	cmp BYTE [rdi], sil
	jz strchr_found
	cmp BYTE [rdi], 0
	jz strchr_end
	inc rdi
	jmp strchr_while

strchr_found:
	mov rax, rdi

strchr_end:
	mov rsp, rbp
	pop rbp
	jmp strchr_return
