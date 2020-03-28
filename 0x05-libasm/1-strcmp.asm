BITS 64
	global asm_strcmp
	section .text
asm_strcmp:
	push rbp
	mov rbp, rsp
	push rdx

	while:
	mov rax, rdi
	mov rdx, rsi
	cmp BYTE [rax], 0x0
	je after
	movzx eax, BYTE [rax]
	movzx edx, BYTE [rdx]
	cmp al, dl
	jne after
	inc rdi
	inc rsi
	jmp while

	after:
	mov rax, rdi
	mov rdx, rsi
	movzx eax, BYTE [rax]
	movzx edx, BYTE [rdx]

	cmp al, dl
	je equal
	jl less
	mov RAX, 0x1
	;mov RAX, [rdi]
	;sub RAX, [rsi]
	jmp end

	equal:
	mov RAX, 0x0
	jmp end
	less:
	mov RAX, -0x1
	jmp end	

	end:
	pop rdx

	mov rbp, rsp
	pop rbp
	ret