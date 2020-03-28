BITS 64
GLOBAL asm_strlen

SECTION .text

asm_strlen:
    ; function prologue
    PUSH RBP
    MOV RBP, RSP
    ; save registers

    MOV RAX, 0
    JMP loop_check
    loop_body:
        INC RAX
        INC RDI
    loop_check:
        CMP BYTE [RDI], 0
        JNE loop_body
    ; restore registers

    ; function epilogue
    MOV RSP, RBP
    POP RBP
    RET
