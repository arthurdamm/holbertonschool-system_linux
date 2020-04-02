BITS 64
	global asm_puti
	extern asm_putc
	section .text

asm_puti:
	push rbp
	mov rbp, rsp
	push r15
 	push r14
	push r13

	xor r15, r15
	xor r14, r14	; r14 is our char counter
	movsx r15, edi	; r15 holds our integer n
	xor rax, rax

	cmp r15, 0
	jge test_zero
	imul r15, -1
	mov r13, 1
	mov rdi, 45
	call asm_putc

test_zero:
	test r15, r15
	jnz while_n
	mov rdi, 48
	call asm_putc
	mov r13, 1

while_n:
	; RAX starts as dividend becomes quotient
	; RDX receives remainder
	xor rdx, rdx
	test r15, r15
	jz done_while_n
	mov rax, r15
	mov rbx, 10
	div rbx
	; print remainder in RDX
	mov r15, rax
	after_div:
	push rdx
	after_push:
	inc r14
	jmp while_n
done_while_n:

	mov r15, r14;	move counter
print_loop:
	test r15, r15
	jz done_print_loop
	pop rdi
	after_pop:
	add rdi, 48
	call asm_putc
	dec r15
	jmp print_loop

done_print_loop:

	cmp r13, 1
	jne end
	inc r14

end:
	mov rax, r14
	pop r13
	pop r14
	pop r15
	mov rsp, rbp
	pop rbp
	ret
