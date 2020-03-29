BITS 64
	global asm_strspn

	section .text

asm_strspn:
	push rbp
	mov rbp, rsp

	xor rcx, rcx

while_strspn:
	cmp BYTE [rdi], 0
	jz strspn_end
	xor rax, rax
	push rsi
	push rdi

	mov rdi, rsi
	mov rsi, [rsp]
	movzx rsi, BYTE [rsi]
	call asm_strchr
	pop rdi
	pop rsi
	test rax, rax
	jz strspn_end
	inc rcx
	inc rdi
	jmp while_strspn

strspn_end:
	mov rax, rcx
	mov rsp, rbp
	pop rbp
	ret

asm_strchr:
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
	ret
