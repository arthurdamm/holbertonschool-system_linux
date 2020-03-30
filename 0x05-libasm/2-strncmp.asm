BITS 64
	global asm_strncmp
	section .text

asm_strncmp:
	push rbp
	mov rbp, rsp
	push rcx

while:
	mov rax, rdi
	mov rcx, rsi
	movzx eax, BYTE [rax]
	movzx ecx, BYTE [rcx]
	cmp al, 0x0
	je after
	cmp al, cl
	jne after
	inc rdi
	inc rsi
	dec edx
	jz equal
	jmp while

after:
	cmp al, cl
	je equal
	jl less
	mov RAX, 0x1
	jmp end
equal:
	mov RAX, 0x0
	jmp end
less:
	mov RAX, -0x1
	jmp end

end:
	pop rcx

	mov rbp, rsp
	pop rbp
	ret
