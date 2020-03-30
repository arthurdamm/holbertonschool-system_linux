BITS 64
	global asm_strcasecmp
	section .text

asm_strcasecmp:
	push rbp
	mov rbp, rsp
	push rdx

while:
	mov rax, rdi
	mov rdx, rsi
	movzx eax, BYTE [rax]
	movzx edx, BYTE [rdx]
	cmp al, 0x0
	je after
	; check case
	cmp al, 65
	jl case_a_done
	cmp al, 90
	jg case_a_done
	add ax, 32
	case_a_done:
	cmp dl, 65
	jl case_done
	cmp dl, 90
	jg case_done
	add dx, 32

case_done:
	cmp al, dl
	jne after
	inc rdi
	inc rsi
	jmp while

after:
	cmp al, dl
	je equal
	jl less
	sub al, dl
	jmp end
equal:
	mov rax, 0x0
	jmp end
less:
	sub al, dl
	neg al
	imul eax, -1
	jmp end

end:
	pop rdx

	mov rbp, rsp
	pop rbp
	ret
